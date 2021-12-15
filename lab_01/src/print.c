#include "print.h"

void welcome_print()
{
    printf("%s",
           "\nThis program produces a multiplication of real numbers "
           "in the form <+-m.nE+-K>,\n"
           "where the length of the mantissa (m+n) is up to 30 significant\n"
           "numbers a value of the order of K up to 5 digits\n"
           "How to enter numbers correctly:\n\n"
           "1) Put a number sign (+ or -).\n"
           "2) Enter a real number without a space.\n"
           "3) Use a period, not a comma when entering a number.\n"
           "4) Put a order sign (+ or -) after a large letter 'E'.\n"
           "5) Order is an integer.\n\n"
           "                    +-1   5   10   15   20   25   30  33\n"
           "                     |----|----|----|----|----|----|--...\n");
}

void input(char *num)
{
    printf("Enter a real number: ");
    scanf("%s", num);
}

void no_sign_output()
{
    printf("Put a number sign. Check the rules\n.");
}

void zero_result_output()
{
    printf("\nResult of multiplication: +0.0E0\n");
}

void incorrect_output()
{
    printf("Incorrect input. Check the rules.\n");
}

void letters_output()
{
    printf("The entered string must not contain letters.\n");
}

void overflow_output()
{
    printf("Overflow power. Check the rules.\n");
}

void result_output()
{
    printf("\n Result of multiplication: ");
}

void print_sign(number_r *f, number_r *s)
{
    if (f->sing_num == '-' || s->sing_num == '-')
    {
        if (!(f->sing_num == '-' && s->sing_num == '-'))
            printf("-");
        else
            printf("+");
    }
    else
        printf("+");
}

