#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include "errors_structures.h"

array_stack_r *create_array_stack(const int capacity);
int input_array_stack(array_stack_r *stack, int count, int type_input, int elem);
int push_elem_array(array_stack_r *stack, int elem);
int null_array(array_stack_r *stack);
int full_array(array_stack_r *stack);
int full_array_(array_stack_r *stack);
int empty_array(array_stack_r *stack);
int empty_array_(array_stack_r *stack);
int pop_elem_array(array_stack_r *stack);
int output_array_stack(array_stack_r *stack);
void sort_one_array(array_stack_r *one, int capacity);
array_stack_r *sort_array_stacks(array_stack_r *one, array_stack_r *two);

#endif
