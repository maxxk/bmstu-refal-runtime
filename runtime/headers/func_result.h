#ifndef _BMSTU_REFC_FUNC_RESULT_H_
#define _BMSTU_REFC_FUNC_RESULT_H_

#include <lterm.h>

#define OK_RESULT			0
#define CALL_RESULT			1
#define FAIL_RESULT			2

/*
	Структура хранит результат вызова функции:
	OK_RESULT: работа функции завершилась успешно, и что-то еще ...
	FAIL_RESULT: работа функции заврешилась неудачно, и что-то еще ...
	CALL_RESULT: работа функции была приостоновлена, необходимо еше раз вызывать функцию и т.д.
*/
struct func_result_t
{
    /// Статус завершения.
	int status;

    /// Результат работы - цепочка l_term'ов
	struct lterm_t* fieldChain;

    /// Если результом является вызов функции, то
    /// в этом поле хранится цепочка вызовов функций.
	struct lterm_t* callChain;
};

#endif
