#include "errors_structures.h"
#include "print.h"
#include "parser.h"
#include "correction.h"
#include "normalization.h"
#include "multiplication.h"

int correction(char *num, number_r *pars_num)
{
    if (num_sign_parser(num, pars_num))
        return ERR_CORRECT_NUM;

    if (e_sign_parser(num, pars_num))
        return ERR_CORRECT_NUM;

    if (mantissa_parser(num, pars_num))
        return ERR_CORRECT_NUM;

    if (point_parser(num, pars_num))
        return ERR_CORRECT_NUM;

    if (power_parser(num, pars_num))
        return ERR_CORRECT_NUM;
    return OK;
}

int main()
{
    setbuf(stdout, NULL);

    char first_num[MAX_LEN_NUM];
    char second_num[MAX_LEN_NUM];

    number_r first_pars_num = { 0 }, second_pars_num = { 0 };
    number_r first_normal_num = { 0 }, second_normal_num = { 0 };

    int res_power;
    int res_multi[MAX_MANTISSA * 2];

    welcome_print();

    input(first_num);
    if (strlen(first_num) < 1)
    {
        incorrect_output();
        return INCORRECT_INPUT;
    }

    if (correction(first_num, &first_pars_num))
    {
        incorrect_output();
        return INCORRECT_INPUT;
    }

    input(second_num);
    if (strlen(second_num) < 1)
    {
        incorrect_output();
        return INCORRECT_INPUT;
    }

    if (correction(second_num, &second_pars_num))
    {
        incorrect_output();
        return INCORRECT_INPUT;
    }

    if (plus_minus_check(first_num, second_num))
    {
        no_sign_output();
        return SIGN_ERR;
    }

    if (correct_letters(&first_pars_num) || correct_letters(&second_pars_num))
    {
        letters_output();
        return ERR_LETTERS;
    }

    if (normalization(&first_pars_num, &first_normal_num) || normalization(&second_pars_num, &second_normal_num))
    {
        zero_result_output();
        return EXIT_SUCCESS;
    }

    //printf("\n%d\n", first_normal_num.int_power);
    multiplication_mantissa(&first_normal_num, &second_normal_num, res_multi);
    if (multiplication_power(&first_normal_num, &second_normal_num, &res_power))
    {
        overflow_output();
        return ERR_OVERFLOW;
    }

    int del = 0;
    int len;
    rouding_and_len(res_multi, &res_power, &first_normal_num, &second_normal_num, &len);
    del = delete_end_zeroes(res_multi);

    if (correct_answer(res_multi, len))
    {
        incorrect_output();
        return ERR_CORRECT_NUM;
    }

    result_output();
    print_sign(&first_pars_num, &second_pars_num);

    printf("0.");
    for (int i = len; i >= del; i--)
        printf("%d", res_multi[i]);
    printf("E%d\n", res_power);

    return OK;
}
