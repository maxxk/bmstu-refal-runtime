#ifndef __V_TERM_H__
#define __V_TERM_H__

#define V_CHAR_TAG          0
#define V_IDENT_TAG         1
#define V_INT_NUM_TAG       2
#define V_DOUBLE_NUM_TAG    3
#define V_CLOSURE_TAG       4
#define V_BRACKET_OPEN_TAG	5
#define V_BRACKET_CLOSE_TAG	6

#include <stdint.h>

#include "lterm.h"
#include "func_call.h"
#include "vmachine.h"

/// vterm функций.
struct v_closure
{
	RefalFunc funcPtr;
    struct lterm_t* params;
    struct v_string* ident;
    uint32_t paramsCount;
    int rollback;
};

/// vterm строк Юникода.
struct v_string
{
    /// Для хранения кодовых точек Юникода.
    uint32_t* head;

    /// Длина Юникод строки
    uint64_t length;
};

/// vterm целочисленных чисел.
struct v_int
{
    /// Байты для хранения большого числа.
    uint8_t* bytes;

    /// Знак числа. 0 - число положительное, в противном случае отрицательное.
    uint8_t sign;

    /// Сколько байтов занимает число.
    uint64_t length;
};

struct v_term
{
	int tag;

	union
	{
		uint32_t ch;
        double doubleNum;
        struct v_string* str;
		struct v_closure* closure;
        struct v_int* intNum;

		// Хранит длину всей скобочной последовательности. Для () равна 2, для (1 2) равна 4 и т.д.
        uint64_t inBracketLength;
	};
};

#endif
