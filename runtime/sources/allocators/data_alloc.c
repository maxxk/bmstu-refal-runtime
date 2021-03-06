#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

#include <vmachine.h>
#include <memory_manager.h>
#include <defines/gc_macros.h>
#include <allocators/data_alloc.h>
#include <defines/data_struct_sizes.h>

static struct lterm_t* chCopyChainKeeperLTerm(struct lterm_t* term, allocate_result* res);
static struct lterm_t* chCopyFragmentLTerm(struct lterm_t* term, allocate_result* res);

struct vstring_t* chAllocateVStringFromASCIIName(const char* name, allocate_result* res)
{
    uint64_t length = strlen(name);

    GC_DATA_HEAP_CHECK_RETURN(VSTRING_SIZE(length), *res);

    struct vstring_t* ptr = (struct vstring_t*)(_memMngr.data + _memMngr.dataOffset);
    _memMngr.dataOffset +=  sizeof(struct vstring_t);

    SET_VSTRING_LENGTH(ptr, length);
    ptr->head = (uint32_t*)(_memMngr.data + _memMngr.dataOffset);
    _memMngr.dataOffset += length * sizeof(uint32_t);

    uint64_t i = 0;
    for (i = 0; i < length; ++i)
        ptr->head[i] = name[i];

    return ptr;
}

struct lterm_t* chAllocateFuncCallLTerm(allocate_result* res)
{
    GC_DATA_HEAP_CHECK_RETURN(FUNC_CALL_LTERM_SIZE, *res);

    return allocateFuncCallLTerm();
}

struct lterm_t* chAllocateChainKeeperLTerm(uint32_t count, allocate_result* res)
{
    GC_DATA_HEAP_CHECK_RETURN(CHAIN_KEEPER_LTERM_SIZE(count), *res);

    return allocateChainKeeperLTerm(count);
}

struct lterm_t* chAllocateSimpleChainLTerm(allocate_result* res)
{
    GC_DATA_HEAP_CHECK_RETURN(CHAIN_LTERM_SIZE, *res);

    return allocateSimpleChain();
}

struct lterm_t* chAllocateFragmentLTerm(uint32_t count, allocate_result *res)
{
    GC_DATA_HEAP_CHECK_RETURN(FRAGMENT_LTERM_SIZE_N(count), *res);

    return allocateFragmentLTerm(count);
}

struct vclosure_t* chAllocateClosureStruct(RefalFunc funcPtr, uint32_t paramsCount, struct vstring_t* ident, int rollback, allocate_result *res)
{
    GC_DATA_HEAP_CHECK_RETURN(VCLOSURE_SIZE(paramsCount), *res);

    return allocateClosureStruct(funcPtr, paramsCount, ident, rollback);
}

struct vint_t* chAllocateIntStruct(uint64_t length, allocate_result* res)
{
    GC_DATA_HEAP_CHECK_RETURN(VINT_STRUCT_SIZE(length), *res);

    return allocateIntStruct(length);
}

struct lterm_t* chCopyFieldOfView(struct lterm_t* chain, allocate_result* result)
{
    struct lterm_t* newChain = 0;
    struct lterm_t* newTerm = 0;
    struct lterm_t* currTerm = chain->next;

    CHECK_ALLOCATION_RETURN(newChain, chAllocateSimpleChainLTerm(result), *result);

    while (currTerm != chain)
    {
        newTerm = 0;

        switch (currTerm->tag)
        {
            case L_TERM_FRAGMENT_TAG:
                CHECK_ALLOCATION_RETURN(newTerm, chCopyFragmentLTerm(currTerm, result), *result);
                break;

            case L_TERM_CHAIN_KEEPER_TAG:
                CHECK_ALLOCATION_RETURN(newTerm, chCopyChainKeeperLTerm(currTerm, result), *result);
                break;

            case L_TERM_FUNC_CALL:
                PRINT_AND_EXIT(FOV_CONTAINS_FUNC_CALL);
                break;

            case L_TERM_CHAIN_TAG:
                PRINT_AND_EXIT(FOV_CONTAINS_SIMPLE_CHAIN);
                break;
        }

        if (newTerm)
            ADD_TO_CHAIN(newChain, newTerm);
        else
            PRINT_AND_EXIT(GC_CANT_COPY_TERM);

        currTerm = currTerm->next;
    }

    return newChain;
}

// Параметры инициализируются перед первым вызовом на основе данных из зымакания в vterm'е.
struct env_t* initEnvData(struct env_t* env, uint32_t localsCount, uint32_t patternsCount, uint32_t bracketsCount)
{
    env->locals = allocateFragment(localsCount);

    env->assembled = (uint64_t*)(_memMngr.data + _memMngr.dataOffset);
    _memMngr.dataOffset += patternsCount * sizeof(uint64_t);

    env->stretchVarsNumber = (int*)(_memMngr.data + _memMngr.dataOffset);
    _memMngr.dataOffset += patternsCount * sizeof(int);

    env->bracketsOffset = (uint64_t*)(_memMngr.data + _memMngr.dataOffset);
    _memMngr.dataOffset += bracketsCount * sizeof(uint64_t);

    env->brLeftOffset = (uint64_t*)(_memMngr.data + _memMngr.dataOffset);
    _memMngr.dataOffset += bracketsCount * sizeof(uint64_t);

    env->brRightOffset = (uint64_t*)(_memMngr.data + _memMngr.dataOffset);
    _memMngr.dataOffset += bracketsCount * sizeof(uint64_t);

    env->localsCount = localsCount;
    env->fovsCount = patternsCount;
    env->bracketsCount = bracketsCount;

    uint32_t i = 0;
    for (i = 0; i < patternsCount; ++i)
        env->stretchVarsNumber[i] = -1;

    memset(env->locals, 0, localsCount * sizeof(struct fragment_t));    
    memset(env->assembled, 0, patternsCount * sizeof(uint64_t));    
    memset(env->bracketsOffset, 0, bracketsCount * sizeof(uint64_t));
    memset(env->brLeftOffset, 0, bracketsCount * sizeof(uint64_t));
    memset(env->brRightOffset, 0, bracketsCount * sizeof(uint64_t));

    return env;
}

struct vclosure_t* allocateClosureStruct(RefalFunc funcPtr, uint32_t paramsCount, struct vstring_t* ident, int rollback)
{
    struct vclosure_t* closure = (struct vclosure_t*)(_memMngr.data + _memMngr.dataOffset);
    _memMngr.dataOffset += sizeof(struct vclosure_t);

    closure->params = allocateFragment(paramsCount);

    closure->funcPtr = funcPtr;
    closure->ident = ident;
    closure->paramsCount = paramsCount;
    closure->rollback = rollback;

    return closure;
}

struct vint_t* allocateIntStruct(uint64_t length)
{
    struct vint_t* pointer = (struct vint_t*)(_memMngr.data + _memMngr.dataOffset);
    _memMngr.dataOffset += sizeof(struct vint_t);

    pointer->bytes = (uint8_t*)(_memMngr.data + _memMngr.dataOffset);
    SET_INT_LENGTH(pointer, length);

    memset(pointer->bytes, 0, length);

    _memMngr.dataOffset += length;

    return pointer;
}

struct lterm_t* allocateBuiltinsResult(uint64_t offset, uint64_t length)
{
    struct lterm_t* fragmentLTerm = allocateFragmentLTerm(1);
    fragmentLTerm->fragment->offset = offset;
    fragmentLTerm->fragment->length = length;

    struct lterm_t* chain = allocateSimpleChain();

    ADD_TO_CHAIN(chain, fragmentLTerm);

    return chain;
}

struct lterm_t* allocateFragmentLTerm(uint32_t count)
{
    struct lterm_t* lterm = (struct lterm_t*)(_memMngr.data + _memMngr.dataOffset);
    _memMngr.dataOffset += count * sizeof(struct lterm_t);

    struct fragment_t* fragment = (struct fragment_t*)(_memMngr.data + _memMngr.dataOffset);
    _memMngr.dataOffset += count * sizeof(struct fragment_t);

    struct lterm_t* head = lterm;

    uint32_t i = 0;
    for (i = 0; i < count; ++i)
    {
        lterm->tag = L_TERM_FRAGMENT_TAG;
        lterm->fragment = fragment;
        lterm++;
        fragment++;
    }

    return head;
}

struct fragment_t* allocateFragment(uint32_t count)
{
    struct fragment_t* fragment = (struct fragment_t*)(_memMngr.data + _memMngr.dataOffset);
    _memMngr.dataOffset += count * sizeof(struct fragment_t);

    return fragment;
}

struct vstring_t*  allocateVString(uint64_t length)
{
    struct vstring_t* str = (struct vstring_t*)(_memMngr.data + _memMngr.dataOffset);
    _memMngr.dataOffset += sizeof(struct vstring_t);

    SET_VSTRING_LENGTH(str, length);
    str->head = (uint32_t*)(_memMngr.data + _memMngr.dataOffset);

    _memMngr.dataOffset += length * sizeof(uint32_t);

    return str;
}

struct lterm_t* allocateFuncCallLTerm()
{
    struct lterm_t* lterm = (struct lterm_t*)(_memMngr.data + _memMngr.dataOffset);
    _memMngr.dataOffset +=  sizeof(struct lterm_t);

    lterm->funcCall = (struct func_call_t*)(_memMngr.data + _memMngr.dataOffset);
    _memMngr.dataOffset += sizeof(struct func_call_t);

    memset(lterm->funcCall, 0, sizeof(struct func_call_t));

    lterm->funcCall->env = (struct env_t*)(_memMngr.data + _memMngr.dataOffset);
    _memMngr.dataOffset += sizeof(struct env_t);

    memset(lterm->funcCall->env, 0, sizeof(struct env_t));

    lterm->tag = L_TERM_FUNC_CALL;

    return lterm;
}

struct lterm_t* allocateChainKeeperLTerm(uint32_t count)
{
    struct lterm_t* chainKeeperTerm = (struct lterm_t*)(_memMngr.data + _memMngr.dataOffset);
    _memMngr.dataOffset += count * sizeof(struct lterm_t);

    struct lterm_t* head = chainKeeperTerm;

    uint32_t i = 0;

    for (i = 0; i < count; ++i)
    {
        chainKeeperTerm->tag = L_TERM_CHAIN_KEEPER_TAG;
        chainKeeperTerm->chain = allocateSimpleChain();
        chainKeeperTerm++;
    }

    return head;
}

struct lterm_t* allocateSimpleChain()
{
    struct lterm_t* chain = (struct lterm_t*)(_memMngr.data + _memMngr.dataOffset);
    _memMngr.dataOffset += sizeof(struct lterm_t);

    chain->tag = L_TERM_CHAIN_TAG;
    chain->prev = chain;
    chain->next = chain;

    return chain;
}

static struct lterm_t* chCopyChainKeeperLTerm(struct lterm_t* term, allocate_result* res)
{
    GC_DATA_HEAP_CHECK_RETURN(CHAIN_KEEPER_LTERM_SIZE(1), *res);

    struct lterm_t* chainKeeperTerm = allocateChainKeeperLTerm(1);

    CHECK_ALLOCATION_RETURN(chainKeeperTerm->chain, chCopyFieldOfView(term->chain, res), *res);

    return chainKeeperTerm;
}

static struct lterm_t* chCopyFragmentLTerm(struct lterm_t* term, allocate_result* res)
{
    GC_DATA_HEAP_CHECK_RETURN(FRAGMENT_LTERM_SIZE, *res);

    struct lterm_t* newTerm = allocateFragmentLTerm(1);
    memcpy(newTerm->fragment, term->fragment, sizeof(struct fragment_t));

    return newTerm;
}
