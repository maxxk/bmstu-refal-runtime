#include <stdio.h>
#include <time.h>
#include <string.h>

#include <memory_manager.h>
#include <allocators/data_alloc.h>
#include <builtins/builtins.h>
#include <helpers.h>

static void copyVTerms();
static void processVTermsInChain(struct lterm_t* expr);
static void processVTermsInFragment(struct fragment_t* frag);
static void processVTermsInFuncCall(struct func_call_t* funcCall);
static void processClosureVTerms(struct v_closure* closure);
static void processEnvVTerms(struct env_t* env);
static void copyClosureVTerm(uint64_t to, struct v_closure* closure);
static void copyIntVTerm(uint64_t to, struct v_int* intNum);

#define MARK_STAGE                  0
#define POINTER_CORRECTING_STAGE    1

static int stage;

void collectVTermGarbage(struct lterm_t* fieldOfView)
{
    memset(memMngr.gcInUseVTerms, 0, memMngr.vtermsMaxOffset * sizeof(uint8_t));

    stage = MARK_STAGE;
    processVTermsInChain(fieldOfView);

    //TO FIX: Правильно обрабатывать _currFuncCall.
    //TO FIX: Будет обрабатываться в рамках _currFuncCall
    processVTermsInFragment(assembledFragInBuiltins->fragment);

    copyVTerms();

    stage = POINTER_CORRECTING_STAGE;    
    processVTermsInChain(fieldOfView);

    //TO FIX: Правильно обрабатывать _currFuncCall.
    //TO FIX: Будет обрабатываться в рамках _currFuncCall
    processVTermsInFragment(assembledFragInBuiltins->fragment);
}

static void processVTermsInChain(struct lterm_t* chain)
{
    struct lterm_t* currTerm = chain->next;

    while (currTerm != chain)
    {
        switch (currTerm->tag)
        {
            case L_TERM_FRAGMENT_TAG:
                processVTermsInFragment(currTerm->fragment);
                break;

            case L_TERM_CHAIN_TAG:
                processVTermsInChain(currTerm);
                break;
            case L_TERM_FUNC_CALL:
                processVTermsInFuncCall(currTerm->funcCall);
                break;
        }

        currTerm = currTerm->next;
    }
}

static void processVTermsInFragment(struct fragment_t* frag)
{
    uint64_t i = 0;
    uint64_t end = frag->offset + frag->length;

    if (stage == MARK_STAGE)
    {
        for (i = frag->offset; i < end; ++i)
        {
            memMngr.gcInUseVTerms[i - memMngr.vtActiveOffset] = 1;

            if (memMngr.vterms[i].tag == V_CLOSURE_TAG)
                processClosureVTerms(memMngr.vterms[i].closure);
        }
    }
    else
    {
        // Ставим новый offset.
        frag->offset = memMngr.vterms[frag->offset].inBracketLength;
    }
}

static void processVTermsInFuncCall(struct func_call_t* funcCall)
{
    if (funcCall->fieldOfView)
        processVTermsInChain(funcCall->fieldOfView);

    if (funcCall->subCall)
        processVTermsInChain(funcCall->subCall);

    processEnvVTerms(funcCall->env);
}

static void processEnvVTerms(struct env_t* env)
{
    uint32_t i = 0;
    for (i = 0; i < env->fovsCount; ++i)
    {
        processVTermsInChain(env->fovs[i]);
        processVTermsInFragment(env->assembledFOVs[i]->fragment);
    }

    for (i = 0; i < env->paramsCount; ++i)
        processVTermsInFragment((env->params + i)->fragment);
}

static void processClosureVTerms(struct v_closure* closure)
{
    uint64_t i = 0;

    for (i  = 0; i < closure->paramsCount; ++i)
        processVTermsInFragment((closure->params + i)->fragment);
}

static void copyVTerms()
{
    uint64_t i = 0;

    memMngr.vtermsOffset = memMngr.vtInactiveOffset;
    memMngr.dataOffset = memMngr.dtInactiveOffset;

    for (i = 0; i < memMngr.vtermsMaxOffset; ++i)
    {
        if (memMngr.gcInUseVTerms[i])
        {
            GC_VTERM_HEAP_CHECK_EXIT(1);

            uint64_t to = memMngr.vtermsOffset;
            uint64_t from = memMngr.vtActiveOffset + i;

            memMngr.vterms[to] = memMngr.vterms[from];
            memMngr.vterms[to].inBracketLength = memMngr.vtermsOffset;

            switch (memMngr.vterms[to].tag)
            {
                case V_INT_NUM_TAG:
                    copyIntVTerm(to, memMngr.vterms[from].intNum);
                    break;
                case V_CLOSURE_TAG:
                    copyClosureVTerm(to, memMngr.vterms[from].closure);
                    break;
            }

            memMngr.vtermsOffset++;
        }
    }
}

// TO FIX: Должно копироваться только один раз.
static void copyClosureVTerm(uint64_t to, struct v_closure* closure)
{    
    GC_DATA_HEAP_CHECK_EXIT(VCLOSURE_SIZE(closure->paramsCount));

    memMngr.vterms[memMngr.vtermsOffset].closure =
            allocateClosureStruct(closure->funcPtr, closure->paramsCount, closure->ident, closure->rollback);
}

// TO FIX: Должно копироваться только один раз.
static void copyIntVTerm(uint64_t to, struct v_int* intNum)
{
    GC_DATA_HEAP_CHECK_EXIT(VINT_STRUCT_SIZE(intNum->length));

    struct v_int* newIntNum = allocateIntStruct(intNum->length);
    memcpy(newIntNum, intNum, sizeof(struct v_int) + intNum->length);
    memMngr.vterms[memMngr.vtermsOffset].intNum = newIntNum;
}



