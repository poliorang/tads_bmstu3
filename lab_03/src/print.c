#include "print.h"

void welcome_print()
{
    printf(COLOR_GREEN "%s" COLOR_RESET,
            "\n\nChoose the command: \n");
    printf(" 1 - Generate matrix and vector\n"
           " 2 - Input matrix and vector manually\n"
           " 3 - Display matrix\n"
           " 4 - Display vector\n"
           " 5 - Classical multiplication\n"
           " 6 - Special multiplication\n"
           " 0 - EXIT\n\n");
    printf("Enter number: ");
}


