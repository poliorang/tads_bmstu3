#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_MANTISSA 32
#define MAX_POWER 8
#define MAX 59

#define INCORRECT_INPUT -1
#define PARSER_ERR -2
#define ERR_CORRECT_NUM -3
#define ERR_LETTERS -4
#define ERR_MULTIPLICATION -5
#define ERR_OVERFLOW -6
#define ERR_ZERO -7
#define SIGN_ERR -8

#define PLUS '+'
#define MINUS '-'

#define OK 0

#define MAX_LEN_NUM 39

#define MAX_MEANING_POWER_PLUS 99999
#define MAX_MEANING_POWER_MINUS -99999

typedef struct
{
    char sing_num;
    char mantissa[MAX_MANTISSA];
    char sing_power;
    char power[MAX_POWER];
    int add_power;
    int point;
    int exp;
    int int_mantissa[MAX_MANTISSA];
    int len_mantissa;
    int int_power;
} number_r;



#endif
