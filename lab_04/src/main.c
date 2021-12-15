#include "errors_structures.h"
#include "list.h"
#include "array.h"
#include "print.h"
#include "check_time.h"

int main(void)
{
    setbuf(stdout, NULL);

    list_stack_r *list_stack_one = NULL, *list_stack_two = NULL, *list_stack_three = NULL;
    array_stack_r *array_stack_one = NULL, *array_stack_two = NULL, *array_stack_three = NULL;
    addresses_r *arr_one = NULL, *arr_two = NULL;

    int first_cap, second_cap, max_capacity;
    int type, pop_elem;

    int command = -1;
    while (command)
    {
        welcome_print();
        printf("\nEnter the number of command: ");
        if (input_number(&command, 0, 12)) {
            printf("Incorrect number.\n");
            continue;
        }

        switch (command)
        {
            case 1:
                printf(COLOR_YELLOW"%s"COLOR_RESET, "\nInput elements into two stacks.\n\n");

                if (array_stack_one || array_stack_two)
                {
                    printf("Stack already exists.\n");
                    break;
                }
                printf("Enter maximum capacity: ");
                if (input_number(&max_capacity, 1, INT32_MAX))
                    return INCORRECT_INPUT;

                printf("Enter the capacity of the FIRST array: ");
                if (input_number(&first_cap, 1, max_capacity))
                    return INCORRECT_INPUT;

                printf("Enter the capacity of the SECOND array: ");
                if (input_number(&second_cap, 1, max_capacity))
                    return INCORRECT_INPUT;

                printf("Enter the elements of first array: ");
                if ((array_stack_one = create_array_stack(max_capacity)) == NULL)
                    return ALLOCATE_ERR;

                if (input_array_stack(array_stack_one, first_cap, 1, 0))
                    return INPUT_ERR;

                printf("Enter the elements of second array: ");
                if ((array_stack_two = create_array_stack(max_capacity)) == NULL)
                    return ALLOCATE_ERR;

                if (input_array_stack(array_stack_two, second_cap, 1, 0))
                    return INPUT_ERR;

                break;

            case 2:
                printf(COLOR_YELLOW"%s"COLOR_RESET, "\nAdd element to the stack.\n\n");

                if (null_array(array_stack_one) || null_array(array_stack_two))
                    return ALLOCATE_ERR;

                printf(" 1 - Add elements to the first stack\n"
                       " 2 - Add elements to the second stack.\n"
                       "Enter 1 or 2: ");

                if (scanf("%d", &type) != 1 || (type != 1 && type != 2))
                {
                    printf("You have to enter 1 or 2.\n");
                    return INCORRECT_INPUT;
                }

                printf("Enter element: ");
                if (type == 1)
                {
                    if (full_array(array_stack_one))
                        return FULL_ERR;

                    if (input_array_stack(array_stack_one, 1, 1, 0))
                        return ADD_ERR;
                }

                if (type == 2)
                {
                    if (full_array(array_stack_two))
                        return FULL_ERR;

                    if (input_array_stack(array_stack_two, 1, 1, 0))
                        return ADD_ERR;
                }

                break;

            case 3:
                printf(COLOR_YELLOW"%s"COLOR_RESET, "\nRemove an element from the stack.\n\n");

                if (null_array(array_stack_one) || null_array(array_stack_two))
                    return ALLOCATE_ERR;

                printf(" 1 - add elements to the first stack\n"
                       " 2 - add elements to the first stack.\n"
                       "Enter 1 or 2: ");

                if (scanf("%d", &type) != 1 || (type != 1 && type != 2))
                    return INCORRECT_INPUT;

                if (type == 1)
                {
                    if (empty_array(array_stack_one))
                        return EMPTY_ERR;

                    pop_elem = pop_elem_array(array_stack_one);
                }

                if (type == 2)
                {
                    if (empty_array(array_stack_two))
                        return EMPTY_ERR;

                    pop_elem = pop_elem_array(array_stack_two);
                }

                printf("Element '%d' has been deleted.\n", pop_elem);

                break;

            case 4:
                printf(COLOR_YELLOW"%s"COLOR_RESET, "\nOutput the current state of the stacks.\n\n");

                if (null_array(array_stack_one) || null_array(array_stack_two))
                    return ALLOCATE_ERR;

                if (array_stack_one == NULL || array_stack_two == NULL)
                {
                    printf("Stack is exist.\n");
                    break;
                }

                printf("State of FIRST stack:\n");
                if (output_array_stack(array_stack_one))
                    return OUT_ERR;

                printf("State of SECOND stack:\n");
                if (output_array_stack(array_stack_two))
                    return OUT_ERR;

                break;

            case 5:
                printf(COLOR_YELLOW"%s"COLOR_RESET, "\nSort with third stack.\n\n");

                if (null_array(array_stack_one) || null_array(array_stack_two))
                    return ALLOCATE_ERR;

                if (empty_array(array_stack_one) || empty_array(array_stack_two))
                    return ALLOCATE_ERR;

                array_stack_three = sort_array_stacks(array_stack_one, array_stack_two);
                output_array_stack(array_stack_three);

                break;

            case 6:
                printf(COLOR_YELLOW"%s"COLOR_RESET, "\nInput elements into two stacks.\n\n");

                if (list_stack_one || list_stack_two)
                {
                    printf("Stack already exists.\n");
                    break;
                }

                printf("Enter maximum capacity: ");
                if (input_number(&max_capacity, 1, INT32_MAX))
                    return INCORRECT_INPUT;

                printf("Enter the capacity of the FIRST array: ");
                if (input_number(&first_cap, 1, max_capacity))
                    return INCORRECT_INPUT;

                printf("Enter the capacity of the SECOND array: ");
                if (input_number(&second_cap, 1, max_capacity))
                    return INCORRECT_INPUT;

                arr_one = create_array_addresses(max_capacity * max_capacity);
                arr_two = create_array_addresses(max_capacity * max_capacity);


                printf("Enter the elements of first array: ");
                if (input_stack_list(&list_stack_one, first_cap, max_capacity, 1, 0))
                    return INPUT_ERR;

                printf("Enter the elements of second array: ");
                if (input_stack_list(&list_stack_two, second_cap, max_capacity, 1, 0))
                    return INPUT_ERR;

                break;

            case 7:
                printf(COLOR_YELLOW"%s"COLOR_RESET, "\nAdd element to the stack.\n\n");

                if (null_list(list_stack_one) || null_list(list_stack_two))
                    return ALLOCATE_ERR;

                printf(" 1 - Add elements to the first stack\n"
                       " 2 - Add elements to the second stack.\n"
                       "Enter 1 or 2: ");

                if (scanf("%d", &type) != 1 || (type != 1 && type != 2))
                    return INCORRECT_INPUT;

                printf("Enter element: ");
                if (type == 1)
                {
                    if (full_list(list_stack_one, max_capacity))
                        return FULL_ERR;

                    if (input_stack_list(&list_stack_one, 1, max_capacity, 1, 0))
                        return ADD_ERR;
                }

                if (type == 2)
                {
                    if (full_list(list_stack_two, max_capacity))
                        return FULL_ERR;

                    if (input_stack_list(&list_stack_two, 1, max_capacity, 1, 0))
                        return ADD_ERR;
                }

                check_top_list(list_stack_one, arr_one, arr_two);
                check_top_list(list_stack_two, arr_one, arr_two);

                break;

            case 8:
                printf(COLOR_YELLOW"%s"COLOR_RESET, "\nRemove an element from the stack.\n\n");

                if (null_list(list_stack_one) || null_list(list_stack_two))
                    return ALLOCATE_ERR;

                printf(" 1 - Remove elements from the first stack\n"
                       " 2 - Remove elements from the second stack.\n"
                       "Enter 1 or 2: ");

                if (scanf("%d", &type) != 1 || (type != 1 && type != 2))
                    return INCORRECT_INPUT;


                if (type == 1)
                {
                    if (empty_list(list_stack_one))
                        return EMPTY_ERR;

                    // pop_elem = pop_elem_list(&list_stack_one, arr_one);
                    if ((list_stack_one = pop_elem_list(list_stack_one, &pop_elem, arr_one)) == NULL)
                        return POP_ERR;
                }

                if (type == 2)
                {
                    if (empty_list(list_stack_two))
                        return EMPTY_ERR;

                    //pop_elem = pop_elem_list(&list_stack_two, arr_two);
                    if ((list_stack_two = pop_elem_list(list_stack_two, &pop_elem, arr_two)) == NULL)
                        return POP_ERR;
                }

                printf("Element '%d' has been deleted.\n", pop_elem);

                break;

            case 9:
                printf(COLOR_YELLOW"%s"COLOR_RESET, "\nOutput the current state of the stacks.\n\n");

                if (null_list(list_stack_one) || null_list(list_stack_two))
                    return ALLOCATE_ERR;

                printf("State of FIRST stack:\n");
                if (output_list_stack(list_stack_one))
                    return OUT_ERR;

                printf("\nState of SECOND stack:\n");
                if (output_list_stack(list_stack_two))
                    return OUT_ERR;

                break;

            case 10:
                printf(COLOR_YELLOW"%s"COLOR_RESET, "\nOutput an array of freed addresses.\n\n");

                if (null_list(list_stack_one) || null_list(list_stack_two))
                    return ALLOCATE_ERR;

                printf("Freed address-array of FIRST stack:\n");
                output_array_addresses(*arr_one);

                printf("\nFreed address-array of SECOND stack:\n");
                output_array_addresses(*arr_two);

                break;

            case 11:
                printf(COLOR_YELLOW"%s"COLOR_RESET, "\nSort with third stack.\n\n");

                if (null_list(list_stack_one) || null_list(list_stack_two) ||
                list_stack_one->ind == 0 || list_stack_two->ind == 0)
                {
                    printf("One of stacks is empty.\n");
                    return ALLOCATE_ERR;
                }

                list_stack_three = sort_list_stacks(list_stack_one, list_stack_two, first_cap + second_cap);

                output_list_stack(list_stack_three);

                break;

            case 12:
                printf(COLOR_YELLOW"%s"COLOR_RESET, "\nOperations time.\n\n");

                time_out();

                break;

            case 0:
                free(arr_one);
                free(arr_two);
                free(array_stack_one);
                free(array_stack_two);
                free_list_stack(&list_stack_one, arr_one);
                free_list_stack(&list_stack_two, arr_two);
                exit(EXIT_SUCCESS);
        }
    }

    free(arr_one);
    free(arr_two);
    free(array_stack_one);
    free(array_stack_two);
    free_list_stack(&list_stack_one, arr_one);
    free_list_stack(&list_stack_two, arr_two);

    return EXIT_SUCCESS;
}
