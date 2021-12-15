#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include "errors_structures.h"

list_stack_r *create_list_stack(const int data);
int push_list(list_stack_r **stack, int data, int lim);
int input_stack_list(list_stack_r **stack, int count, int lim, int type, int elem);
int null_list(list_stack_r *stack);
int empty_list_(list_stack_r *stack);
int empty_list(list_stack_r *stack);
int full_list_(list_stack_r *stack, int lim);
int full_list(list_stack_r *stack, int lim);
list_stack_r *pop_elem_list(list_stack_r *stack, int *elem, addresses_r *arr);
int pop_elem_list_without_arr(list_stack_r **stack);
int output_list_stack(list_stack_r *stack);
int free_list_stack(list_stack_r **stack, addresses_r *arr);
addresses_r *create_array_addresses(int capacity);
void check_top_list(list_stack_r *stack, addresses_r *arr, addresses_r *arr_two);
void output_array_addresses(addresses_r arr);
list_stack_r *sort_one_list(list_stack_r **one, int capacity);
list_stack_r *sort_list_stacks(list_stack_r *one, list_stack_r *two, int capacity);

#endif
