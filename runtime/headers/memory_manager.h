#ifndef _BMSTU_REFC_ALLOCATOR_H_
#define _BMSTU_REFC_ALLOCATOR_H_

#include <stdint.h>

#include <vterm.h>
#include <lterm.h>

#define DEFAULT_HEAP_SIZE UINT64_C(1024 * 1024 * 1024)

/// Коэффциенты распределения памяти по кучам.
#define VTERMS_HEAP_SIZE_FACTOR     0.4f
#define DATA_HEAP_SIZE_FACTOR       0.6f

struct memory_manager
{
    /// Указатель на начало vterm'ов
	struct vterm_t* vterms;
    uint64_t vtActiveOffset;
    uint64_t vtInactiveOffset;

    /// Указатели на данные
    uint8_t* data;
    uint64_t dtActiveOffset;
    uint64_t dtInactiveOffset;

    /// Текущие сдвиги
    uint64_t vtermsOffset;
    uint64_t dataOffset;    

    /// Начиная с какого vterm'а начинаются не литеральные vterm'ы в массиве vterms
    uint64_t vtermsBeginOffset;

    /// Максимальный размер массива vterm'ов.
    uint64_t vtermsMaxOffset;	

    /// Максимальный размер данных.
    uint64_t dataMaxOffset;

    /// Размер выделенного участка
    uint64_t totalSize;

    /// Поле зрения
    struct lterm_t* fieldOfView;
};

struct memory_manager _memMngr;

/// Выделяет память размера size
/// и сохраняет указатель на выделенный участок
/// в переменной mainHeap.
void initAllocator(uint64_t size);

/// Распределеяет память для типов данных
/// т.е. инциализирует поля activeTermsHeap, inactiveTermsHeap и т.д.
void initHeaps(uint64_t literalsNumber);

/// Выводит общую информацию об использовании памяти.
void printMemoryInfo();

#endif
