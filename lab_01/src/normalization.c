#include "normalization.h"

void delete_sign(char *num)
{
    int len = strlen(num);
    if (num[0] == '-' || num[0] == '+')
    {
        for (int i = 0; i < len; i++)
            num[i] = num[i + 1];
        num[len - 1] = '\0';
    }
}

void delete_point(int *len_mantissa, char *mantissa, number_r *num)
{
    for (int i = 0; i < *(len_mantissa); i++)
    {
        if (mantissa[i] == '.')
        {
            num -> add_power = *(len_mantissa) - i - 1;
            for (int j = i; j < *(len_mantissa); j++)
                mantissa[j] = mantissa[j + 1];
            break;
        }
    }
}

int delete_zeros(char *mantissa, int len_mantissa)
{
    while (mantissa[0] == '0')
    {
        if (len_mantissa == '1')
            break;
        else
        {
            int i = 0;
            while (i < len_mantissa)
            {
                mantissa[i] = mantissa[i + 1];
                i++;
            }
        }
        len_mantissa--;
    }
    return len_mantissa;
}

void mantissa_formation(char *num, int arr[], int *len)
{
    int i = 0;
    while (num[i] != '\0')
    {
        arr[i] = num[i] - '0';
        i++;
    }
    *(len) = i;
}

void power_formation(char *num, int *int_num)
{
    *(int_num) = atoi(num);
}

int normalization(number_r *pars_num, number_r *normal_num)
{
    char *mantissa = pars_num -> mantissa;
    char *power = pars_num -> power;

    delete_sign(mantissa);

    int len_mantissa = strlen(mantissa);
    int len_power = strlen(power);

    delete_point(&len_mantissa, mantissa, normal_num);

    len_mantissa = delete_zeros(mantissa, len_mantissa);

    for (int i = 0; i < len_mantissa; i++)
        normal_num -> mantissa[i] = mantissa[i];

    for (int i = 0; i < len_power; i++)
        normal_num -> power[i] = power[i];

    normal_num->mantissa[len_mantissa] = '\0';
    normal_num->power[len_power] = '\0';

    mantissa_formation(normal_num->mantissa, normal_num->int_mantissa, &(normal_num->len_mantissa));
    power_formation(normal_num->power, &(normal_num->int_power));

    int check_zero = 0;

    for (int i = 0; i < normal_num->len_mantissa; i++)
        if (normal_num->int_mantissa[i] != '0')
            check_zero = 1;

    if (!check_zero)
        return ERR_ZERO;

    return OK;
}
