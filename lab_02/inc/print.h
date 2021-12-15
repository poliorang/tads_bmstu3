#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>
#include "sort.h"
#include "read.h"
#include "structures.h"

#define MAX_TABLE_SIZE 500

#define EMPTY_TABLE_ERR 1
#define INPUT_AGE_DUR_ERR 2

#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_RESET "\x1b[0m"

void welcome_print();
int print_table(table_r *table);
void print_hat();
void print_sort_hat(int type);
int print_select(table_r *table);
int print_by_keys(table_r *table);
void print_res_comp(table_r *table, double time, int type_sort, int type_table);
void print_keys(table_r *table);

#endif
