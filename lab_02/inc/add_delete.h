#ifndef DISPLAY_H
#define DISPLAY_H

#include <string.h>

#include "read.h"
#include "structures.h"

#define EMPTY_TABLE_ERR 1
#define NO_INPUT 6
#define ENTER_ERR 3

int add_entry(table_r *table);
int delete_entry(table_r *table);

int input_yes_no(int *ans);
int check_type(table_r *table, int ind);
int check_type_adult(table_r *table, int ind);

#endif
