#include "errors_structures.h"


int num_sign_parser(char *num, number_r *parser_num)
{
    if (num[0] == '-')
    {
        parser_num -> sing_num = MINUS;
        return OK;
    }
    parser_num -> sing_num = PLUS;
    return OK;
}

int point_parser(char *num, number_r *parser_num)
{
    int pos_in_num = 0;
    int point_pos = -41;
    int flag = 1;
    int length_num = strlen(num);

    for ( ; pos_in_num < length_num; pos_in_num++)
    {
        if (num[pos_in_num] == '.')
        {
            if (flag)
            {
                point_pos = pos_in_num;
                flag = 0;
            }
            else
                return PARSER_ERR;
        }
    }
    parser_num -> point = point_pos - 1;
    return OK;
}

int e_sign_parser(char *num, number_r *parser_num)
{
    int pos_in_num = 0;
    int e_pos;
    int length_num = strlen(num);

    for ( ; pos_in_num < length_num; pos_in_num++)
    {
        if (num[pos_in_num] == 'E')
        {
            e_pos = pos_in_num;
            break;
        }
    }
    if (pos_in_num == length_num)
        e_pos = -41;

    parser_num -> exp = e_pos;
    return OK;
}

int mantissa_parser(char *num, number_r *parser_num)
{
    int start = 0;
    int end;

    if (parser_num -> exp == -41)
        end = strlen(num);
    else
        end = parser_num -> exp - 1;

    if ((parser_num -> point == -42 && end - start > 30) || \
        (end - start > 31 && parser_num -> point != -42))
        return PARSER_ERR;


    for ( ; start <= end; start++)
        parser_num -> mantissa[start] = num[start];

    parser_num -> mantissa[start] = '\0';

    return OK;
}

int power_parser(char *num, number_r *parser_num)
{
    if (parser_num -> exp == -41)
    {
        parser_num -> power[0] = '+';
        parser_num -> power[1] = '0';
        parser_num -> power[2] = '\0';
    }
    else
    {
        int start = parser_num -> exp + 1;
        int end = strlen(num);

        if ((end - start) > 7 - 1)
            return PARSER_ERR;

        int pos_in_num = 0;

        for ( ; start < end; start++, pos_in_num++)
            parser_num -> power[pos_in_num] = num[start];

        parser_num -> power[pos_in_num] = '\0';
    }
    return OK;
}
