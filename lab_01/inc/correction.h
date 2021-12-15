#ifndef CORRECT_H
#define CORRECT_H

#include "errors_structures.h"

int correct_letters(number_r *pars_num);
int plus_minus_check(char first_num[], char second_num[]);
int correct_answer(int res_multi[], int len);
int delete_end_zeroes_with_power(int res_multi[], int *power);
int delete_end_zeroes(int res_multi[]);
int rouding_and_len(int res_multi[], int *power, number_r *first, number_r *second, int *l);

#endif
