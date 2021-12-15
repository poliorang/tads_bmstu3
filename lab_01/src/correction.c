#include "correction.h"


int correct_letters(number_r *pars_num)
{
    int len_mantissa = strlen(pars_num->mantissa);
    int len_power = strlen(pars_num->power);
    int flag_point = 0;
    int flag_sign = 0;

    if ((pars_num->mantissa[0] == '+' || pars_num->mantissa[0] == '-') && \
        (len_mantissa == 1))
        return ERR_CORRECT_NUM;

    if ((pars_num->power[0] == '+' || pars_num->power[0] == '-') && \
        (len_power == 1))
        return ERR_CORRECT_NUM;

    for (int i = 0; i < len_mantissa; i++)
    {
        if (pars_num->mantissa[i] == '.')
        {
            if (flag_point == 0)
                flag_point = 1;
            else
                return ERR_CORRECT_NUM;
        }
        if (pars_num->mantissa[i] == '+' || pars_num->mantissa[i] == '-')
        {
            if (flag_sign == 0)
                flag_sign = 1;
            else
                return ERR_CORRECT_NUM;
        }

        if (pars_num->mantissa[i] != '.' && pars_num->mantissa[i] != '+' && pars_num->mantissa[i] != '-')
            if (!isdigit(pars_num->mantissa[i]))
                return ERR_CORRECT_NUM;
    }

    flag_sign = 0;

    for (int i = 0; i < len_power; i++)
    {
        if (pars_num->power[i] == '+' || pars_num->power[i] == '-')
        {
            if (flag_sign == 0)
                flag_sign = 1;
            else
                return ERR_CORRECT_NUM;
        }
        if (pars_num->power[i] != '+' && pars_num->power[i] != '-')
            if (pars_num->power[i] == '.' || !isdigit(pars_num->power[i]))
            {
                return ERR_CORRECT_NUM;
            }
    }

    return OK;
}

int correct_answer(int res_multi[], int len)
{
    for (int i = 0; i < len; i++)
    {
        if (res_multi[i] < 0)
            return ERR_CORRECT_NUM;
    }
    return OK;
}

int delete_end_zeroes_with_power(int res_multi[], int *power)
{
    int i = 0;
    while (res_multi[i] == 0)
    {
        i++;
        *(power) -= 1;
    }
    return i;
}

int delete_end_zeroes(int res_multi[])
{
    int i = 0;
    while (res_multi[i] == 0)
        i++;
    return i;
}

int rouding_and_len(int res_multi[], int *power, number_r *first, number_r *second, int *l)
{
    int flag = 0;
    int len = first->len_mantissa + second->len_mantissa;
    if (len > MAX_MANTISSA - 2)
    {
        flag = 1;
        int iter = 0;
        if (res_multi[len - 31] >= 5)
        {
            res_multi[len - 30]++;
            for (int i = len - 30; i < len; i++)
            {
                iter++;
                if (iter >= 30)
                    *(power) += 1;
                res_multi[i + 1] += res_multi[i] / 10;
                res_multi[i] %= 10;
            }
        }
        for (int i = 0; i < 30; i++)
            res_multi[i] = res_multi[i + (len - 30)];
    }
    if (flag)
        *l = 29;
    else
        *l = len - 1;
    return flag;
}

int plus_minus_check(char first_num[], char second_num[])
{
    if ((first_num[0] != '-' && first_num[0] != '+') || (second_num[0] != '-' && second_num[0] != '+'))
        return ERR_CORRECT_NUM;
    return OK;
}
