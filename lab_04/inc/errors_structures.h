#ifndef ERRORS_STRUCTURES_H
#define ERRORS_STRUCTURES_H

#include <stdio.h>
#include <limits.h>
#include <time.h>

#define INPUT_ERR 1
#define FULL_ERR 2
#define PUSH_ERR 3
#define POP_ERR 4
#define OUT_ERR 5
#define INCORRECT_INPUT 6
#define ALLOCATE_ERR 7
#define EMPTY_ERR 8
#define ADD_ERR 9
#define CHECK_ERR 10

#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_RESET "\x1b[0m"

// стек в виде массива
typedef struct
{
    int top; // голова стека
    int cap; // количество элементов стека
    int *arr; // указатель на массив элементов стека
} array_stack_r;


// стек в виде линейного односвязного списка
typedef struct list_stack list_stack_r;
struct list_stack
{
    int data; // элемент стека
    int ind; // индекс узла списка
    list_stack_r *next; // указатель на следующий элемент
};

// массив освобожденных адресов
typedef struct
{
    size_t *arr; // указатель на массив
    int cap; // количество элементов
    int ind; // индекс текущего элемента списка
} addresses_r;

#endif
