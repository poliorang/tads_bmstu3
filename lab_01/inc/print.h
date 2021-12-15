#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>
#include "errors_structures.h"

void welcome_print();
void print_sign(number_r *f, number_r *s);
void no_sign_output();
void input(char *num);
void zero_result_output();
void incorrect_output();
void letters_output();
void overflow_output();
void result_output();

#endif
