#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include <func_call.h>
#include <vmachine.h>
#include <memory_manager.h>
#include <allocators/vterm_alloc.h>
#include <allocators/data_alloc.h>
#include <builtins/builtins.h>
#include <gc/gc.h>

static void printChainOfCalls(struct lterm_t* callTerm);
static struct lterm_t* updateFieldOfView(struct lterm_t* currNode, struct func_result_t* funcResult, struct lterm_t** lastCallFuncFOV);
static struct lterm_t* addFuncCallFiledOfView(struct lterm_t* currNode, struct func_result_t* funcResult);
static uint64_t gcAssemblyChain(struct lterm_t* chain, uint64_t* length, allocate_result* res);
static struct lterm_t* createFieldOfViewForReCall(struct lterm_t* funcCall);
static RefalFunc getFuncPointer(struct lterm_t* callTerm);
static void onFuncFail(struct lterm_t** callTerm, int failResult);

uint64_t getHeapSize(int argc, char** argv)
{
    uint64_t heapSize = 0;
    int i = 0;

    for (i = 0; i < argc; ++i)
    {
        if (argv[i][0] == '-')
        {
            if (sscanf(argv[i], "-heapSize=%" PRIu64 , &heapSize) == 1)
            {
                printf("Heap size: %" PRIu64 "\n", heapSize);
                return heapSize;
            }
        }
    }

    return DEFAULT_HEAP_SIZE;
}

static struct vstring_t* constructVStringFromASCIIName(const char* name)
{
    struct vstring_t* ptr = (struct vstring_t*)malloc(sizeof(struct vstring_t));
    ptr->length = strlen(name);
    ptr->head = (uint32_t*)malloc(ptr->length * sizeof(uint32_t));

    // USE MEMSET
    uint64_t i = 0;
    for (i = 0; i < ptr->length; ++i)
        ptr->head[i] = name[i];

    return ptr;
}

static struct lterm_t* ConstructStartFunc(const char* funcName, RefalFunc entryFuncPointer)
{
    struct lterm_t* gofuncCallTerm = allocateFuncCallLTerm();
    gofuncCallTerm->funcCall->fieldOfView = allocateSimpleChain();

    struct lterm_t* fragTerm = allocateFragmentLTerm(1);
    fragTerm->fragment->offset = allocateClosureVTerm();
    fragTerm->fragment->length = 1;

    struct vstring_t* ident = constructVStringFromASCIIName(funcName);
    _memMngr.vterms[fragTerm->fragment->offset].closure = gcAllocateClosureStruct(entryFuncPointer, 0, ident, 0);

    ADD_TO_CHAIN(gofuncCallTerm->funcCall->fieldOfView, fragTerm);

    return gofuncCallTerm;
}

static struct lterm_t* ConstructStartFieldOfView(const char* funcName, RefalFunc entryFuncPointer)
{
    struct lterm_t* fieldOfView = allocateSimpleChain();
    struct lterm_t* gofuncCallTerm = ConstructStartFunc(funcName, entryFuncPointer);

    ADD_TO_CHAIN(fieldOfView, gofuncCallTerm);

    return fieldOfView;
}

int eqFragment(uint64_t a, uint64_t b, uint64_t length)
{
    uint64_t i = 0;
    for (i = 0; i < length; i++)
    {
        if (_memMngr.vterms[a + i].tag == V_BRACKETS_TAG)
        {
            if ((VTERM_BRACKETS(a + i)->length != VTERM_BRACKETS(b + i)->length)
             || !eqFragment(VTERM_BRACKETS(a + i)->offset, VTERM_BRACKETS(b + i)->offset, VTERM_BRACKETS(b + i)->length))
            return 0;
        }
        else if (!eqSymbol(a + i, b + i))
            return 0;
    }

    return 1;
}

int eqSymbol(uint64_t a, uint64_t b)
{
//    if (memMngr.vtActiveOffset <= a && a < memMngr.vtActiveOffset + memMngr.vtermsMaxOffset)
  //      PRINT_AND_EXIT("BEDA!!!\n");

    return
        (_memMngr.vterms[a].tag == _memMngr.vterms[b].tag)
        &&
        (
            (_memMngr.vterms[a].tag == V_CHAR_TAG
                && _memMngr.vterms[a].ch == _memMngr.vterms[b].ch)

            || (_memMngr.vterms[a].tag == V_IDENT_TAG
                && ustrEq(_memMngr.vterms[a].str, _memMngr.vterms[b].str))

            || (_memMngr.vterms[a].tag == V_INT_NUM_TAG
                && !intCmp(_memMngr.vterms[a].intNum, _memMngr.vterms[b].intNum))

            || (_memMngr.vterms[a].tag == V_DOUBLE_NUM_TAG
                && !doubleCmp(_memMngr.vterms[a].doubleNum, _memMngr.vterms[b].doubleNum))

            || (_memMngr.vterms[a].tag == V_CLOSURE_TAG
                && ustrEq(_memMngr.vterms[a].closure->ident, _memMngr.vterms[b].closure->ident))
        );

}

void mainLoop(const char* entryFuncName, RefalFunc entryFuncPointer)
{
    _memMngr.fieldOfView = ConstructStartFieldOfView(entryFuncName, entryFuncPointer);

	struct func_result_t funcRes;    
    struct lterm_t* parentCall = 0;
    int entryStatus = 0;
    struct lterm_t* lastCallFuncFOV = 0;

    _currCallTerm = _memMngr.fieldOfView->next;

    while (_currCallTerm)
	{
        // Указатель на функцию проставлен --> функция вызывается повторно.
        if (_currCallTerm->funcCall->funcPtr)
        {
            // Предыдущий результат успешен --> все скобки активации обработаны, можно передавать функции-потребителю.
            if (funcRes.status != FAIL_RESULT)
            {                
                if (!_currCallTerm->funcCall->fieldOfView)
                {
                    if (lastCallFuncFOV == 0)
                        PRINT_AND_EXIT("BEDA!!!\n");

                    _currCallTerm->funcCall->fieldOfView = lastCallFuncFOV;
                }
                _currCallTerm->funcCall->env->workFieldOfView = _currCallTerm->funcCall->subCall;
                _currCallTerm->funcCall->subCall = 0;
                entryStatus = NEXT_ENTRYPOINT;
            }
            else // Обработка скобок активаций завершилась неудачно --> откат.
            {
                entryStatus = ROLL_BACK;
            }
        }
        else // Указатель на функцию не проставлен --> первый вызов.
        {
            entryStatus = FIRST_CALL;
            _currCallTerm->funcCall->funcPtr = getFuncPointer(_currCallTerm);

            // Первый терм в скобках аткивации не является функциональным --> откат.
            if (_currCallTerm->funcCall->funcPtr == 0)
            {
                onFuncFail(&_currCallTerm, 0);
                entryStatus = ROLL_BACK;
            }
        }

        funcRes = CURR_FUNC_CALL->funcPtr(entryStatus);

        switch (funcRes.status)
        {
            case OK_RESULT:                
                _currCallTerm = updateFieldOfView(_currCallTerm, &funcRes, &lastCallFuncFOV);                
                break;

            case CALL_RESULT:
                parentCall = _currCallTerm;
                _currCallTerm = addFuncCallFiledOfView(_currCallTerm, &funcRes);
                _currCallTerm->funcCall->parentCall = parentCall;
                break;
            case FAIL_RESULT:
                onFuncFail(&_currCallTerm, 1);
                break;
        }
	}
}

static void onFuncFail(struct lterm_t** callTerm, int failResult)
{
    if ((failResult && !(*callTerm)->funcCall->rollback) || !(*callTerm)->funcCall->parentCall || (*callTerm)->funcCall->failEntryPoint == -1)
    {        
        PRINT_AND_EXIT( FUNC_CALL_FAILED);
    }
    else
    {
        (*callTerm)->funcCall->parentCall->funcCall->entryPoint = (*callTerm)->funcCall->failEntryPoint;

        if ((*callTerm)->funcCall->parentCall->funcCall->fieldOfView == 0)
            (*callTerm)->funcCall->parentCall->funcCall->fieldOfView = (*callTerm)->funcCall->fieldOfView;

        (*callTerm) = (*callTerm)->funcCall->parentCall;
    }
}

static RefalFunc getFuncPointer(struct lterm_t* callTerm)
{
    struct lterm_t* fieldOfView = callTerm->funcCall->fieldOfView;

    //Fatal error!
    if (fieldOfView == 0)
    {
        printf("%s\n", BAD_EVAL_EXPR);
        exit(0);
    }

    if (fieldOfView->next == fieldOfView)
        return 0;

    //Fatal error!
    if (fieldOfView->next->tag != L_TERM_FRAGMENT_TAG)
    {
        printf("%s\n", BAD_EVAL_EXPR);
        exit(0);
    }

    if (fieldOfView->next->fragment->length == 0)
        return 0;

    //Fatal error!
    if (_memMngr.vterms[fieldOfView->next->fragment->offset].tag != V_CLOSURE_TAG)
    {
        printf("%s\n", BAD_EVAL_EXPR);
        exit(0);
    }

    struct vclosure_t* closure = _memMngr.vterms[fieldOfView->next->fragment->offset].closure;

    RefalFunc newFuncPointer = closure->funcPtr;
    callTerm->funcCall->env->params = closure->params;
    callTerm->funcCall->env->paramsCount = closure->paramsCount;
    callTerm->funcCall->rollback = closure->rollback;

    // Remove fragment with closure => lost closure => GC will clean it.
    fieldOfView->next = fieldOfView->next->next;
    fieldOfView->next->prev = fieldOfView;

	return newFuncPointer;
}

static struct lterm_t* addFuncCallFiledOfView(struct lterm_t* currNode, struct func_result_t* funcResult)
{
    currNode->funcCall->subCall = funcResult->fieldChain;
	struct lterm_t* newCallNode = funcResult->callChain->next;
	funcResult->callChain->prev->funcCall->next = currNode;

	return newCallNode;
}

static struct lterm_t* updateFieldOfView(struct lterm_t* currNode, struct func_result_t* funcResult, struct lterm_t** lastCallFuncFOV)
{
	struct lterm_t* newCurrNode = currNode->funcCall->next;

    *lastCallFuncFOV = currNode->funcCall->fieldOfView;

    if (funcResult->fieldChain)  // Insertn chain in the middle
	{		
		struct lterm_t* insertChain = funcResult->fieldChain;

		currNode->prev->next = insertChain->next;
		insertChain->next->prev = currNode->prev;

		currNode->next->prev = insertChain->prev;
		insertChain->prev->next = currNode->next;

		//Обновляем цепочку вызовов
		if (funcResult->callChain)
		{
			newCurrNode = funcResult->callChain->next;
			funcResult->callChain->prev->funcCall->next = currNode->funcCall->next;
		}
    }
    else
    {
        // Just exclude call node from fieldOfView
        currNode->prev->next = currNode->next;
        currNode->next->prev = currNode->prev;
    }

	return newCurrNode;
}

uint64_t gcGetAssembliedChain(struct lterm_t* chain, allocate_result *res)
{    
    uint64_t assembledVtermOffset = 0;
    uint64_t length = 0;
    uint64_t offset = 0;

    if (chain != 0)
    {
        if (chain->tag != L_TERM_CHAIN_TAG)
            PRINT_AND_EXIT(ASSEMBLY_NOT_CHAIN);

        CHECK_ALLOCATION_RETURN(assembledVtermOffset, chAllocateBracketVterm(res), *res);

        CHECK_ALLOCATION_RETURN(offset, gcAssemblyChain(chain, &length, res), *res);

        VTERM_BRACKETS(assembledVtermOffset)->offset = offset;
        VTERM_BRACKETS(assembledVtermOffset)->length = length;
    }

    return assembledVtermOffset;
}

static uint64_t assemblyTopVTerms(struct lterm_t* chain, uint64_t* length, allocate_result* res)
{
    uint64_t resOffset = _memMngr.vtermsOffset;
    struct lterm_t* currTerm = chain->next;
    *length= 0;

    while (currTerm != chain)
    {
        switch (currTerm->tag)
        {
            case L_TERM_FRAGMENT_TAG :
            {
                uint64_t offset = 0;
                CHECK_ALLOCATION_RETURN(offset, allocateVTerms(currTerm->fragment, res), *res);
                *length += currTerm->fragment->length;
                break;
            }
            case L_TERM_CHAIN_KEEPER_TAG:
            {
                GC_VTERM_HEAP_CHECK_RETURN(1, *res);
                GC_DATA_HEAP_CHECK_RETURN(FRAGMENT_STRUCT_SIZE(1), *res);

                allocateBracketsVTerm();
                ++*length;
                break;
            }

            case L_TERM_FUNC_CALL:
                PRINT_AND_EXIT(FUNC_CALL_AT_ASSEMBLY);
                break;

            case L_TERM_CHAIN_TAG:
                PRINT_AND_EXIT(SIMPLE_CHAIN_AT_ASSEMBLY);
                break;

            default:
                PRINT_AND_EXIT(BAD_TAG_AT_ASSEMBLY);
        }

        currTerm = currTerm->next;
    }

    return resOffset;
}

static uint64_t gcAssemblyChain(struct lterm_t* chain, uint64_t* length, allocate_result* res)
{
    *res = GC_OK;
    uint64_t resOffset = _memMngr.vtermsOffset;
    struct lterm_t* currTerm = chain->next;
    uint64_t topVTermsOffset = 0;

    CHECK_ALLOCATION_RETURN(topVTermsOffset, assemblyTopVTerms(chain, length, res), *res);

    while (currTerm != chain)
    {
        switch (currTerm->tag)
        {
            case L_TERM_FRAGMENT_TAG :
            {                
                topVTermsOffset += currTerm->fragment->length;
                break;
            }
            case L_TERM_CHAIN_KEEPER_TAG:
            {
                GC_VTERM_HEAP_CHECK_RETURN(1, *res);
                GC_DATA_HEAP_CHECK_RETURN(FRAGMENT_STRUCT_SIZE(1), *res);

                uint64_t offset = 0;
                uint64_t tmpLength = 0;

                CHECK_ALLOCATION_RETURN(offset, gcAssemblyChain(currTerm->chain, &tmpLength, res), *res);

                setBracketsData(topVTermsOffset, offset, tmpLength);

                ++topVTermsOffset;
                break;
            }

        }

        currTerm = currTerm->next;
    }

    return resOffset;
}
