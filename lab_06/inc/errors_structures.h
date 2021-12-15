#ifndef ERRORS_H
#define ERRORS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define LIMIT 15
#define SIZE 15

#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_RESET "\x1b[0m"

// узел дерева
typedef struct node
{
	int data; // данные, хранящие в узлах
	int height; // высота дерева в узле
    struct node* left; // указатель на левую ветку
	struct node* right; // указатель на правую ветку
} node_t;

// ячейка хэш-таблицы
typedef struct
{
	int flag; // показатель, что ячецка занята
	int value; // данные ячейки
}  cell_t;

// хэш-таблица
typedef struct 
{
	cell_t *data; // ячейка
	int limit; // количество коллизий
	int size; // текущий размер таблицы
	int max_size; // максимальный размер таблицы
} hash_t;

#endif
