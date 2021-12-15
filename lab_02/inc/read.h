#ifndef READ_H
#define READ_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "structures.h"

#define LEFT_LIMIT 0
#define RIGHT_LIMIT 13

#define INCORRECT_INPUT -1
#define CASE_ONE_ERR -2
#define SELECT_ERR -3

#define INCORRECT_FIELD_PLAYBILL 1
#define INCORRECT_FIELD_CHILD 2
#define INCORRECT_FIELD_ADULT 3
#define INCORRECT_FIELD_MUS 4
#define CONDITION_ERR 5
#define NO_INPUT 6
#define AGE_ERR 7
#define DUR_ERR 8

int input_str(char *string);
int input_num(int *number);

int input_command(int *command);
//int input_age_and_dur(int *age, int *dur);
int check_three_condition(int a, int b, int c);
int read_field_child(FILE *f, table_r *table, int i);
int read_field_adult(FILE *f, table_r *table, int i);
int read_field_mus(FILE *f, table_r *table, int i);
int read_field(FILE *f, table_r *table, int i);


#endif
