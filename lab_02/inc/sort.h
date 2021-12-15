#ifndef SORT_H
#define SORT_H

#include <time.h>

#include "add_delete.h"
#include "print.h"
#include "form_table.h"
#include "add_delete.h"
#include "structures.h"

#define SORT_ERR 1

int compare_key(const void *a, const void *b);
int compare_table(const void *a, const void *b);


int choose_sort_and_param(table_r *table);
int perform_sorting(table_r *table, int bub, int key, int tab);
void bubble_sort(table_r *table, int tabl_or_key);
void sort_qsort_vs_bub(table_r *table);

#endif
