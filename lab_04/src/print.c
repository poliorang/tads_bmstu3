#include "print.h"
#include "list.h"
#include "array.h"

void welcome_print()
{
    printf(COLOR_GREEN "%s" COLOR_RESET,
            "\nChoose the command: \n");

    printf("%s",
           "\nFor arrays:\n"
           " 1 - Input elements into two stacks.\n"
           " 2 - Add element to the stack.\n"
           " 3 - Remove an element from the stack.\n"
           " 4 - Output the current state of the stacks.\n"
           " 5 - Sort.\n"
           "\nFor lists:\n"
           " 6 - Input elements into two stacks.\n"
           " 7 - Add element to the stack.\n"
           " 8 - Remove an element from the stack.\n"
           " 9 - Output the current state of the stacks.\n"
           "10 - Output arrays of freed addresses.\n"
           "11 - Sort.\n"
           "12 - Statistics of the operation of functions.\n\n"
           "0  - Exit.\n");
}

int input_number(int *number, int left, int right)
{
    char num[5];
    char *n;
    fflush(stdin);
    n = fgets(num, 6, stdin);
    if (n == NULL || num[0] == '\n')
        return INCORRECT_INPUT;
    num[strlen(num) - 1] = '\0';
    *number = (int)atoi(num);

    if (*number < left || *number > right)
    {
        printf("Incorrect number.\n");
        return INCORRECT_INPUT;
    }


    return EXIT_SUCCESS;
}

// проверка двух стеков в виде массива на существование, переполнение и пустоту
int check_two_stacks_array(array_stack_r *one, array_stack_r *two)
{
    if (one == NULL || two == NULL)
    {
        printf("\nStack is NULL.\n");
        return ALLOCATE_ERR;
    }

    if (empty_array(one) || empty_array(two))
    {
        printf("\nStack is empty.\n");
        return EMPTY_ERR;
    }

    if (full_array(one) || full_array(two))
    {
        printf("\nStack is full.\n");
        return FULL_ERR;
    }

    return EXIT_SUCCESS;
}

void print_hat()
{
    printf("----------------------------------------\n"
           "    type         time    |   memory \n"
           "----------------------------------------\n");
}

