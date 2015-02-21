#include <stdio.h>
#include <gmp.h>
#include <stdint.h>
#include <stdlib.h>

#include "vmachine.h"
#include "builtins.h"

#define ARITHM_BASE "4294967296"

static uint32_t readOperand(mpz_t num, uint32_t currOffset, uint32_t maxOffset, int all);
static uint32_t writeOperand(mpz_t num);

static void numParseFailed()
{
	printf("Failed: Can't parse int num!\n");
	exit(0);
}

static struct lterm_t* constructNumLTerm(mpz_t num)
{
	uint32_t offset = memMngr.vtermsOffset;
	uint32_t length = writeOperand(num);

	return constructLterm(offset, length);
}

static uint32_t readOperand(mpz_t num, uint32_t currOffset, uint32_t maxOffset, int all)
{
	uint32_t i = 0;
	uint32_t sign = 0;

	mpz_t accm;
	mpz_t base;

	mpz_init_set_ui(num, 0);
	mpz_init_set_ui(accm, 0);
	mpz_init_set_str(base, ARITHM_BASE, 10);

	if (memMngr.vterms[currOffset].tag == V_CHAR_TAG)
	{
		currOffset++;
		sign = 1;
	}

	if (currOffset >= maxOffset)
		numParseFailed();

	do
	{
		if (memMngr.vterms[currOffset].tag != V_INT_NUM_TAG)
			numParseFailed();

		mpz_mul(accm, num, base);
		mpz_add_ui(num, accm, memMngr.vterms[currOffset].intNum);
		currOffset++;
	}
	while (currOffset < maxOffset && all);

	if (sign)
	{
		mpz_mul_si(accm, num, -1);
		mpz_swap(accm, num);
	}

	mpz_clear(accm);
	mpz_clear(base);

	return currOffset;
}

static uint32_t getNumsCount(mpz_t num)
{
	uint32_t count = 0;
	mpz_t tmp;
	mpz_t tmpAccm;
	mpz_t base;

	mpz_init_set_str(base, ARITHM_BASE, 10);
	mpz_init_set(tmp, num);
	mpz_init(tmpAccm);

	if (!mpz_cmp_ui(tmp, 0))
	{
		count = 1;
	}
	else
	{
		while (mpz_cmp_ui(tmp, 0) > 0)
		{
			mpz_div(tmpAccm, tmp, base);
			mpz_swap(tmpAccm, tmp);
			count++;
		}
	}

	mpz_clear(base);
	mpz_clear(tmp);
	mpz_clear(tmpAccm);

	return count;
}

static uint32_t writeOperand(mpz_t num)
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
		sign = 1;
		allocateSymbol('-');
		mpz_t tmp;
		mpz_init_set(tmp, num);
		mpz_neg(num, tmp);
		mpz_clear(tmp);
	}

	uint32_t count = getNumsCount(num);
	uint32_t offset = allocateIntNum(count);

	for (i = offset + count - 1; i >= offset; --i)
	{
		mpz_divmod(quotient, remainder, num, base);
		memMngr.vterms[i].intNum = mpz_get_ui(remainder);
		mpz_set(num, quotient);
	}

	mpz_clear(remainder);
	mpz_clear(quotient);
	mpz_clear(base);

	return count + sign;
}

static void readOperands(mpz_t x, mpz_t y, struct fragment_t* frag)
{
	uint32_t currOffset = frag->offset;
	uint32_t maxOffset = frag->offset + frag->length;

	if (memMngr.vterms[currOffset].tag == V_BRACKET_TAG)
	{
		currOffset = readOperand(x, currOffset + 1, currOffset + memMngr.vterms[currOffset].inBracketLength - 1, 1);

		if (memMngr.vterms[currOffset].tag != V_BRACKET_TAG || memMngr.vterms[currOffset].inBracketLength != 0)
			numParseFailed();

		currOffset = readOperand(y, currOffset + 1, maxOffset, 1);
	}
	else
	{
		currOffset = readOperand(x, currOffset, maxOffset, 0);
		currOffset = readOperand(y, currOffset, maxOffset, 1);
	}

	if (currOffset < maxOffset)
		numParseFailed();
}

struct func_result_t Add(int* entryPoint, struct env_t* env, struct lterm_t* fieldOfView)
{
	struct lterm_t* currExpr = getAssembliedChain(fieldOfView);

	mpz_t x;
	mpz_t y;
	mpz_t res;

	mpz_init(res);

	readOperands(x, y, currExpr->fragment);

	mpz_add(res, x, y);

	struct lterm_t* resChain = constructNumLTerm(res);

	mpz_clear(x);
	mpz_clear(y);
	mpz_clear(res);

	return (struct func_result_t){.status = OK_RESULT, .fieldChain = resChain, .callChain = 0};
}
