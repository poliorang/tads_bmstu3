#ifndef NORMAL_H
#define NORMAL_H

#include "errors_structures.h"

void delete_sign(char *num);
void delete_point(int *len_mantissa, char *mantissa, number_r *num);
int delete_zeros(char *mantissa, int len_mantissa);
void mantissa_formation(char *num, int arr[], int *len);
void power_formation(char *num, int *int_num);
int normalization(number_r *pars_num, number_r *normal_num);

#endif
