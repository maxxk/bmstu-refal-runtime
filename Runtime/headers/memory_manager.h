#ifndef __ALLOCATOR_H__
#define __ALLOCATOR_H__

#include <stdint.h>

#include "vterm.h"
#include "lterm.h"
#include "segment_tree.h"

//Сколько процентов памяти выдялется тому или иному типу данных
//Память для дерева отрезков берется из памяти для v_term'ов.
#define V_TERMS_HEAP_SIZE_FACTOR 		0.3f
#define DATA_HEAP_SIZE_FACTOR 			0.4f
#define L_TERMS_HEAP_SIZE_FACTOR		0.3f

struct memory_manager
{
	// Указатель на начало vterm'ов
	struct v_term* vterms;

	/// Размер выделенного участка
    uint64_t totalSize;

    uint64_t activeOffset;
    uint64_t inactiveOffset;

	struct segment_tree* segmentTree;

	// Указатели на данные
	uint8_t* dataHeap;
	uint8_t* activeDataHeap;
	uint8_t* inactiveDataHeap;

    struct lterm_t* lterms;

    uint64_t vtermsOffset;
    uint64_t dataOffset;
    uint64_t ltermsOffset;

    uint64_t literalsNumber;

	//Количество элементов в листе дерева отрезков.
    uint64_t segmentLen;

	//Максимальный размер массива vterm'ов.
    uint64_t vtermsMaxOffset;
	//Максимальный размер массива lterm'ов.
    uint64_t ltermsMaxOffset;
	//Максимальный размр массива данных.
    uint64_t dataMaxOffset;
};

struct memory_manager memMngr;

/// Выделяет память размера size
/// и сохраняет указатель на выделенный участок
/// в переменной mainHeap.
void initAllocator(uint64_t size);

/// Распределеяет память для типов данных
/// т.е. инциализирует поля activeTermsHeap, inactiveTermsHeap и т.д.
void initHeaps(uint64_t segmentLen, uint64_t literalsNumber);

/// Собирает мусор.
void collectGarbage(struct lterm_t* expr);

/// Дебажный вывод vterm
void debugLiteralsPrint();


#endif
