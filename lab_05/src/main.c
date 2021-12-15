#include "array.h"
#include "list.h"
#include "print.h"
#include "errors_structures.h"

int main(void)
{
    int command;
    struct mem_t *mem = NULL;
    int mem_used = 0;
    srand(time(NULL));

    while(1)
    {
        welcome_print();
        if (scanf("%d", &command) != 1 || command < 0 || command > 4)
        {
            printf("\nНеверная команда.\n");
            return ERROR_KEY;
        }
        switch (command)   
        {
            case(0):
                return EXIT_SUCCESS;

            case(1):
                model_arr(&mem_used);
                break;

            case (2):
                model_list(&mem, &mem_used);
                break;

            case (3):
                show_mem(&mem);
                break;

            case (4):
                queue_compare(&mem);
                break;

            default:
                break;
        }
    }

    return EXIT_SUCCESS;
}
