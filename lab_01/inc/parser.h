#ifndef PARSER_H
#define PARSER_H

#include "errors_structures.h"

int num_sign_parser(char *num, number_r *parser_num);
int point_parser(char *num, number_r *parser_num);
int e_sign_parser(char *num, number_r *parser_num);
int mantissa_parser(char *num, number_r *parser_num);
int power_parser(char *num, number_r *parser_num);

#endif
