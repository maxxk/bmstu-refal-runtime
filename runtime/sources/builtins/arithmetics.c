#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <gmp.h>

#include <vint.h>
#include <helpers.h>
#include <vmachine.h>
#include <defines/checkers.h>
#include <builtins/builtins.h>
#include <allocators/data_alloc.h>
#include <allocators/vterm_alloc.h>
#include <defines/data_struct_sizes.h>

typedef void (*ArithOp) (mpz_ptr, mpz_srcptr, mpz_srcptr);

#define EPS 1e-6
#define ARITHM_BASE "4294967296"

#define ADD     1
#define SUB     2
#define MUL     3
#define DIV     4
#define MOD     5
#define COMPARE 6

static ArithOp opToFunc(int op);
struct func_result_t r7Compare();
static const char* opToStr(int op);
static void readIntOperands(mpz_t x, mpz_t y);
static struct func_result_t gcApplyOp(int op);
static struct lterm_t* gcApplyOpToInt(int op);
static void readOperand(mpz_t num, struct vint_t* vnum);
static struct lterm_t* gcConstructDoubleNumLTerm(double val);
static struct lterm_t* gcApplyOpToDouble(int op, double a, double b);
struct lterm_t* chCmpResToLTerm(int res);

struct func_result_t Add(int entryStatus)
{
    return  gcApplyOp(ADD);
}

struct func_result_t Sub(int entryStatus)
{
    return  gcApplyOp(SUB);
}

struct func_result_t Mul(int entryStatus)
{
    return  gcApplyOp(MUL);
}

struct func_result_t Div(int entryStatus)
{    
    return  gcApplyOp(DIV);
}

struct func_result_t Mod(int entryStatus)
{
    return  gcApplyOp(MOD);
}

struct func_result_t Compare(int entryStatus)
{
    #ifdef R5_ARITHM
        return gcApplyOp(COMPARE);
    #else
        return r7Compare();
    #endif
}

#ifdef R5_ARITHM
static struct lterm_t* writeOperand(mpz_t num);
static void r5ReadOperand(mpz_t num, uint32_t offset, uint32_t maxOffset);
static uint32_t getInfoForAllocation(mpz_t num, uint64_t* dataSizeForNums);
static struct lterm_t* gcApplyToInt(int op, uint64_t aOffset, uint64_t aLength, uint64_t bOffset, uint64_t bLength);
static struct func_result_t r5GCApplyOp(int op, uint64_t aOffset, uint64_t aLength, uint64_t bOffset, uint64_t bLength);

static struct func_result_t gcApplyOp(int op)
{
    gcInitBuiltinEnv();

    uint64_t offset = BUILTIN_FRAG->offset;
    uint64_t length = BUILTIN_FRAG->length;

    if (_memMngr.vterms[offset].tag == V_BRACKETS_TAG)
    {
        uint64_t argOffset = _memMngr.vterms[offset].brackets->offset;
        uint64_t argLength = _memMngr.vterms[offset].brackets->length;

        return r5GCApplyOp(op, argOffset, argLength, offset + 1, length - 1);
    }
    else
    {
        uint64_t argLength = 1;

        if (_memMngr.vterms[offset].tag == V_CHAR_TAG)
        {
            if (_memMngr.vterms[offset].ch != '-')
                FMT_PRINT_AND_EXIT(OPERAND_BAD_TYPE, opToStr(op));
            else
                ++argLength;
        }

        return r5GCApplyOp(op, offset, argLength, offset + argLength, length - argLength);
    }
}

static int getOperandType(uint64_t offset, uint64_t length)
{
    if (length == 1)
        return _memMngr.vterms[offset].tag;

    if (_memMngr.vterms[offset].tag == V_DOUBLE_NUM_TAG)
        return V_DOUBLE_NUM_TAG;

    if (_memMngr.vterms[offset].tag == V_CHAR_TAG && _memMngr.vterms[offset].ch == '-')
        return _memMngr.vterms[offset + 1].tag;

    return _memMngr.vterms[offset].tag;
}

static double getDouble(uint64_t offset, uint64_t length)
{
    int sign = 0;

    if (_memMngr.vterms[offset].tag == V_CHAR_TAG && _memMngr.vterms[offset].ch == '-')
        sign = 1;

    if (length - sign != 1)
        FMT_PRINT_AND_EXIT(OPERAND_BAD_TYPE, "Double op");

    if (!sign)
        return _memMngr.vterms[offset].doubleNum;

    return -_memMngr.vterms[offset + 1].doubleNum;
}


static struct func_result_t r5GCApplyOp(int op, uint64_t aOffset, uint64_t aLength, uint64_t bOffset, uint64_t bLength)
{
    struct lterm_t* resChain;

    if (aLength == 0 || bLength == 0)
         FMT_PRINT_AND_EXIT(WRONG_OPERANDS_NUMBER, opToStr(op));

    int aOpType = getOperandType(aOffset, aLength);
    int bOpType = getOperandType(bOffset, bLength);

    if (aOpType != bOpType)
        FMT_PRINT_AND_EXIT(OPERANDS_TYPES_MISMATCH, opToStr(op));

    if (aOpType == V_INT_NUM_TAG)
    {
        resChain = gcApplyToInt(op, aOffset, aLength, bOffset, bLength);
    }
    else if (aOpType == V_DOUBLE_NUM_TAG)
    {
        resChain = gcApplyOpToDouble(op,
                getDouble(aOffset, aLength),
                getDouble(bOffset, bLength));
    }
    else
    {
        FMT_PRINT_AND_EXIT(OPERAND_BAD_TYPE, opToStr(op));
    }

    return (struct func_result_t){.status = OK_RESULT, .fieldChain = resChain, .callChain = 0};
}

static struct lterm_t* gcApplyToInt(int op, uint64_t aOffset, uint64_t aLength, uint64_t bOffset, uint64_t bLength)
{
    struct lterm_t* resChain = 0;

    mpz_t x;
    mpz_t y;

    r5ReadOperand(x, aOffset, aOffset + aLength);
    r5ReadOperand(y, bOffset, bOffset + bLength);

    switch (op)
    {
    case COMPARE:
        resChain = chCmpResToLTerm(mpz_cmp(x, y));
        break;

    default:
        opToFunc(op)(x, x, y);
        resChain = writeOperand(x);
    }

    mpz_clear(x);
    mpz_clear(y);

    return resChain;
}

static void r5ReadOperand(mpz_t num, uint32_t offset, uint32_t maxOffset)
{
    uint32_t sign = 0;

    mpz_t base;
    mpz_t tmpNum;

    mpz_init_set_ui(tmpNum, 0);
    mpz_init_set_ui(num, 0);
    mpz_init_set_str(base, ARITHM_BASE, 10);

    if (_memMngr.vterms[offset].tag == V_CHAR_TAG)
    {
        offset++;
        sign = 1;
    }

    if (offset >= maxOffset)
        FMT_PRINT_AND_EXIT(OPERAND_BAD_TYPE, "Refal-5 read int operand");

    do
    {
        if (_memMngr.vterms[offset].tag != V_INT_NUM_TAG)
            FMT_PRINT_AND_EXIT(OPERAND_BAD_TYPE, "Refal-5 read int operand");

        mpz_mul(num, num, base);
        readOperand(tmpNum, _memMngr.vterms[offset].intNum);
        mpz_add(num, num, tmpNum);
        offset++;
    }
    while (offset < maxOffset);

    if (sign)
        mpz_neg(num, num);

    mpz_clear(base);
    mpz_clear(tmpNum);
}

static struct lterm_t* writeOperand(mpz_t num)
{
    uint32_t i = 0;
    uint32_t sign = 0;
    mpz_t remainder;
    mpz_t quotient;
    mpz_t base;

    mpz_init_set_ui(remainder, 0);
    mpz_init_set_ui(quotient, 0);
    mpz_init_set_str(base, ARITHM_BASE, 10);

    if (mpz_cmp_ui(num, 0) < 0)
    {
        mpz_neg(num, num);
        sign = 1;
    }

    uint64_t dataSizeForNums = 0;
    uint32_t count = getInfoForAllocation(num, &dataSizeForNums);

    checkAndCleanHeaps(count + sign + 1, dataSizeForNums + BUILTINS_RESULT_SIZE);

    uint64_t offset = _memMngr.vtermsOffset;

    if (sign)
        allocateSymbolVTerm('-');

    for (i = 0; i < count; ++i)
        allocateIntNumVTerm(0);

    for (i = _memMngr.vtermsOffset - 1; i >= _memMngr.vtermsOffset - count; --i)
    {
        mpz_divmod(quotient, remainder, num, base);

        uint32_t numb = 8 * sizeof(uint8_t);
        uint64_t length = (mpz_sizeinbase (remainder, 2) + numb - 1) / numb;

        struct vint_t* vnum = allocateIntStruct(length);
        mpz_export(vnum->bytes, &length, 1, sizeof(uint8_t), 1, 0, remainder);

        _memMngr.vterms[i].intNum = vnum;

        mpz_set(num, quotient);
    }

    mpz_clear(remainder);
    mpz_clear(quotient);
    mpz_clear(base);

    return allocateBuiltinsResult(offset, sign + count);
}

static uint32_t getInfoForAllocation(mpz_t num, uint64_t* dataSizeForNums)
{
    uint32_t count = 0;
    mpz_t tmp;
    mpz_t base;
    mpz_t remainder;

    *dataSizeForNums = 0;

    mpz_init(remainder);
    mpz_init_set_str(base, ARITHM_BASE, 10);
    mpz_init_set(tmp, num);

    if (!mpz_cmp_ui(tmp, 0))
    {
        count = 1;
        *dataSizeForNums += VINT_STRUCT_SIZE(0);
    }
    else
    {
        while (mpz_cmp_ui(tmp, 0) > 0)
        {
            mpz_mod(remainder, tmp, base);
            uint32_t numb = 8 * sizeof(uint8_t);
            uint64_t length = (mpz_sizeinbase (num, 2) + numb - 1) / numb;

            *dataSizeForNums += VINT_STRUCT_SIZE(length);

            mpz_div(tmp, tmp, base);
            count++;
        }
    }

    mpz_clear(base);
    mpz_clear(tmp);
    mpz_clear(remainder);

    return count;
}

#else

static struct func_result_t gcApplyOp(int op)
{
    gcInitBuiltinEnv();
    struct lterm_t* resChain = 0;

    if (BUILTIN_FRAG->length != 2)    
        FMT_PRINT_AND_EXIT(WRONG_OPERANDS_NUMBER, opToStr(op));

    if (_memMngr.vterms[BUILTIN_FRAG->offset].tag != _memMngr.vterms[BUILTIN_FRAG->offset + 1].tag )
        FMT_PRINT_AND_EXIT(OPERANDS_TYPES_MISMATCH, opToStr(op));

    if (_memMngr.vterms[BUILTIN_FRAG->offset].tag == V_INT_NUM_TAG)
    {
        resChain = gcApplyOpToInt(op);
    }
    else if (_memMngr.vterms[BUILTIN_FRAG->offset].tag == V_DOUBLE_NUM_TAG)
    {

        resChain = gcApplyOpToDouble(op,
            _memMngr.vterms[BUILTIN_FRAG->offset].doubleNum,
            _memMngr.vterms[BUILTIN_FRAG->offset+1].doubleNum);
    }
    else
        FMT_PRINT_AND_EXIT(OPERAND_BAD_TYPE, opToStr(op));

    return (struct func_result_t){.status = OK_RESULT, .fieldChain = resChain, .callChain = 0};
}

static struct lterm_t* gcApplyOpToInt(int op)
{
    mpz_t x;
    mpz_t y;

    mpz_init(x);
    mpz_init(y);

    readIntOperands(x, y);

    opToFunc(op)(x, x, y);
    struct lterm_t* resChain = gcConstructSingleIntNumBuiltinResult(x);

    mpz_clear(x);
    mpz_clear(y);

    return resChain;
}

static void readIntOperands(mpz_t x, mpz_t y)
{
    struct vterm_t* term = _memMngr.vterms + BUILTIN_FRAG->offset;

    readOperand(x, term->intNum);
    term++;
    readOperand(y, term->intNum);
}

#endif

static void readOperand(mpz_t num, struct vint_t* vnum)
{
    mpz_import(num, GET_INT_LENGTH(vnum), 1, sizeof(uint8_t), 1, 0, vnum->bytes);

    if (GET_INT_SIGN(vnum))
        mpz_mul_si(num, num, -1);
}

static struct lterm_t* gcApplyOpToDouble(int op, double a, double b)
{
    switch (op)
    {
    case ADD:
        return gcConstructDoubleNumLTerm(a + b);

    case SUB:
        return gcConstructDoubleNumLTerm(a - b);

    case MUL :
        return gcConstructDoubleNumLTerm(a * b);

    case DIV:
        return gcConstructDoubleNumLTerm(a / b);

    case MOD:
        FMT_PRINT_AND_EXIT(MOD_TO_DOUBLE_ERROR, opToStr(op));
    }


    FMT_PRINT_AND_EXIT(BAD_BINARY_OPERATION, "Double arithmetic");
}

struct lterm_t* gcConstructSingleIntNumBuiltinResult(mpz_t num)
{      
    uint32_t numb = 8 * sizeof(uint8_t);
    uint64_t length = (mpz_sizeinbase (num, 2) + numb - 1) / numb;

    checkAndCleanHeaps(1, VINT_STRUCT_SIZE(length) + BUILTINS_RESULT_SIZE);

    struct vint_t* intNum = allocateIntStruct(length);

    mpz_export(intNum->bytes, &length, 1, sizeof(uint8_t), 1, 0, num);

    if (mpz_sgn(num) < 0)
        SET_INT_SIGN(intNum);

    uint64_t offset = allocateIntNumVTerm(intNum);

    return allocateBuiltinsResult(offset, 1);
}

static struct lterm_t* gcConstructDoubleNumLTerm(double val)
{    
#ifdef R5_ARITHM
    int sign = 0;
    if (val < EPS)
        sign = 1;

    checkAndCleanHeaps(1 + sign, BUILTINS_RESULT_SIZE);

    if (sign)
        allocateSymbolVTerm('-');

    return allocateBuiltinsResult(allocateDoubleNumVTerm(val) - sign, 2);
#else
    checkAndCleanHeaps(1, BUILTINS_RESULT_SIZE);
    return allocateBuiltinsResult(allocateDoubleNumVTerm(val), 1);
#endif
}

struct func_result_t r7Compare()
{
    gcInitBuiltinEnv();

    if (BUILTIN_FRAG->length != 2)
        FMT_PRINT_AND_EXIT(WRONG_OPERANDS_NUMBER, "Compare");

    if (_memMngr.vterms[BUILTIN_FRAG->offset].tag != _memMngr.vterms[BUILTIN_FRAG->offset + 1].tag )
        FMT_PRINT_AND_EXIT(OPERANDS_TYPES_MISMATCH, "Compare");

    int cmpRes = 0;    

    if (_memMngr.vterms[BUILTIN_FRAG->offset].tag == V_INT_NUM_TAG)
        cmpRes = intCmp(_memMngr.vterms[BUILTIN_FRAG->offset].intNum, _memMngr.vterms[BUILTIN_FRAG->offset + 1].intNum);
    else if (_memMngr.vterms[BUILTIN_FRAG->offset].tag == V_DOUBLE_NUM_TAG)
        cmpRes = doubleCmp(_memMngr.vterms[BUILTIN_FRAG->offset].doubleNum, _memMngr.vterms[BUILTIN_FRAG->offset + 1].doubleNum);
    else
        FMT_PRINT_AND_EXIT(OPERAND_BAD_TYPE, "Compare");

    return (struct func_result_t){.status = OK_RESULT, .fieldChain = chCmpResToLTerm(cmpRes), .callChain = 0};
}

struct lterm_t* chCmpResToLTerm(int res)
{
    char resChar = '0';

    if (res > 0)
        resChar = '+';
    else if (res < 0)
        resChar = '-';
    else
        resChar = '0';

    checkAndCleanHeaps(1, BUILTINS_RESULT_SIZE);

    return allocateBuiltinsResult(allocateSymbolVTerm(resChar), 1);
}

/// Проверка на равенство двух чисел. 1 - успех, 0 - неудача.
int intCmp(struct vint_t* a, struct vint_t* b)
{
    if (GET_INT_LENGTH(a) == 1 && GET_INT_LENGTH(b) == 1 &&
        a->bytes[0] == 0 && b->bytes[0] == 0)
        return 0;

    int invert = 1;

    if (GET_INT_SIGN(a) > GET_INT_SIGN(b))
        return -1;

    if (GET_INT_SIGN(a) < GET_INT_SIGN(b))
        return 1;

    if (GET_INT_SIGN(a))
        invert = -1;

    if (GET_INT_LENGTH(a) > GET_INT_LENGTH(b))
        return 1 * invert;

    if (GET_INT_LENGTH(a) < GET_INT_LENGTH(b))
        return -1 * invert;

    uint64_t i = 0;
    for (i = 0; i < GET_INT_LENGTH(a); ++i)
    {
        if (a->bytes[i] > b->bytes[i])
            return 1 * invert;

        if (a->bytes[i] < b->bytes[i])
            return -1 * invert;
    }

    return 0;
}

int doubleCmp(double a, double b)
{
    if (b + EPS < a)
        return 1;

    if (a + EPS < b)
        return -1;

    return 0;
}

int ConvertToInt(struct vint_t* numData)
{
    mpz_t num;

    mpz_init(num);

    mpz_import(num, GET_INT_LENGTH(numData), 1, sizeof(uint8_t), 1, 0, numData->bytes);

    if (GET_INT_SIGN(numData))
        mpz_neg(num, num);



    int res = mpz_get_si(num);

    mpz_clear(num);

    return res;
}

static const char* opToStr(int op)
{
    switch (op)
    {
    case ADD:
        return "Add";

    case SUB:
        return "Sub";

    case MUL :
        return "Mul";

    case DIV:
        return "Div";

    case MOD:
        return "Mod";

    case COMPARE:
        return "Compare";
    }

    return 0;
}


static ArithOp opToFunc(int op)
{
    switch (op)
    {
    case ADD:
        return mpz_add;

    case SUB:
        return mpz_sub;

    case MUL :
        return mpz_mul;

    case DIV:
        return mpz_tdiv_q;

    case MOD:
        return mpz_mod;
    }
}

