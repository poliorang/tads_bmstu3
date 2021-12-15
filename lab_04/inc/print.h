#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors_structures.h"

void welcome_print();
int input_number(int *number, int left, int right);
int check_two_stacks_array(array_stack_r *one, array_stack_r *two);
void print_hat();

#endif
