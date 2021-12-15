#include "multiplication.h"

#define TEN 10

int multiplication_power(number_r *first, number_r *second, int *r)
{
    int res = first->int_power + second->int_power - first->add_power - second->add_power;
    res += first->len_mantissa + second->len_mantissa;

    if (res > MAX_MEANING_POWER_PLUS || res < MAX_MEANING_POWER_MINUS)
        return ERR_MULTIPLICATION;

    *(r) = res;
    return OK;
}

void multiplication_mantissa(number_r *first, number_r *second, int arr[])
{
    for (int i = 0; i < MAX_MANTISSA * 2; i++)
        arr[i] = 0;

    for (int i = first->len_mantissa - 1, i2 = 0; i >= 0; i--, i2++)
        for (int j = second->len_mantissa - 1, j2 = 0; j >= 0; j--, j2++)
        {
            int x = (first->int_mantissa[i] * second->int_mantissa[j]);
            arr[i2 + j2] += x % TEN;
            arr[i2 + j2 + 1] += x / TEN;

            if (arr[i2 + j2] >= TEN)
            {
                arr[i2 + j2 + 1] += (arr[i2 + j2] / TEN);
                arr[i2 + j2] = arr[i2 + j2] % TEN;
            }
        }

    int len = first->len_mantissa + second->len_mantissa - 1;

    if (arr[len] == 0)
        first->len_mantissa -= 1;
}





