#ifndef __V_TERM_H__
#define __V_TERM_H__

#define V_CHAR_TAG          0
#define V_IDENT_TAG         1
#define V_INT_NUM_TAG       2
#define V_FLOAT_NUM_TAG     3
#define V_CLOSURE_TAG       4
#define V_BRACKET_OPEN_TAG	5
#define V_BRACKET_CLOSE_TAG	6

#include <stdint.h>

#include "lterm.h"
#include "func_call.h"
#include "vmachine.h"

struct v_closure
{
	RefalFunc funcPtr;
	struct lterm_t* env;
	const char* ident;
};

struct v_string
{
    uint32_t* head;
    uint64_t length;
};

struct v_int
{
    uint8_t* bytes;
    uint8_t sign;
    uint64_t length;
};

struct v_term
{
	int tag;

	union
	{
		uint32_t ch;
		float floatNum;
        struct v_string* str;
		struct v_closure* closure;
        struct v_int* intNum;

		// Хранит длину всей скобочной последовательности. Для () равна 2, для (1 2) равна 4 и т.д.
        uint64_t inBracketLength;
	};
};

#endif
