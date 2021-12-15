#include "check_time.h"

int time_out()
{
    list_stack_r *list_stack_one = NULL, *list_stack_two = NULL;
    array_stack_r *array_stack_one = NULL, *array_stack_two = NULL;

    int first_cap, second_cap, max_capacity;
    clock_t start, end;


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

    list_stack_one = create_list_stack(array_stack_one->arr[0]);
    for (int i = 0; i <= array_stack_one->top; i++)
        push_list(&list_stack_one, array_stack_one->arr[i], max_capacity);


    printf("Enter the elements of second array: ");
    if ((array_stack_two = create_array_stack(max_capacity)) == NULL)
        return ALLOCATE_ERR;

    if (input_array_stack(array_stack_two, second_cap, 1, 0))
        return INPUT_ERR;

    list_stack_two = create_list_stack(array_stack_two->arr[0]);
    //printf("%d\n", array_stack_one->arr[0]);
    for (int i = 0; i <= array_stack_two->top; i++)
        push_list(&list_stack_two, array_stack_two->arr[i], max_capacity);

    printf("\n\nWork with first stack >>  ");
    output_array_stack(array_stack_one);

    printf(COLOR_BLUE "%s" COLOR_RESET,
           "         ADD ELEMENT     \n");
    print_hat();

    // время добавления элемента в список
    start = clock();
    push_list(&list_stack_one, 1, first_cap + 1);
    end = clock();

    printf("List stack:      %4zu    |    %zu   \n", (end - start), (sizeof (int) * 2 + sizeof (list_stack_one->next)) * (first_cap + 1));


    // время добавления элемента в массив
    start = clock();
    push_elem_array(array_stack_one, 1);
    end = clock();

    printf("Array stack:     %4zu    |    %zu   \n", (end - start), sizeof (int *) + sizeof (int) * max_capacity);

    printf("----------------------------------------\n");
    printf(COLOR_BLUE "%s" COLOR_RESET,
           "\n       REMOVE ELEMENT    \n");
    print_hat();

    // время удаления элемента из списка
    start = clock();
    pop_elem_list_without_arr(&list_stack_one);
    end = clock();

    printf("List stack:      %4zu    |    %zu   \n", (end - start), (sizeof (int) * 2 + sizeof (list_stack_one->next)) * first_cap);

    // время удаления элемента из массива
    start = clock();
    pop_elem_array(array_stack_one);
    end = clock();

    printf("Array stack:     %4zu    |    %zu   \n", (end - start), sizeof (int *) + sizeof (int) * max_capacity);

    printf("----------------------------------------\n");
    printf(COLOR_BLUE "%s" COLOR_RESET,
           "\n           SORTING    \n");
    print_hat();

    // время сортировки списков
    start = clock();
    sort_list_stacks(list_stack_one, list_stack_two, first_cap + second_cap);
    end = clock();

    printf("List stack:      %4zu    |    %zu   \n", (end - start), (sizeof (int) * 2 +
                                                                     sizeof (list_stack_one->next)) * (first_cap + second_cap));

    // время сортировки массивов
    start = clock();
    sort_array_stacks(array_stack_one, array_stack_two);
    end = clock();

    printf("Array stack:     %4zu    |    %zu   \n", (end - start), sizeof (int *) + sizeof (int) * (first_cap + second_cap));

    printf("----------------------------------------\n");

    return EXIT_SUCCESS;
}

