#include "list.h"

// создание стека в виде списка
list_stack_r *create_list_stack(int data)
{
    list_stack_r *stack = (list_stack_r *)malloc(sizeof(list_stack_r));

    if (!stack)
        return NULL;

    stack->data = data;
    stack->ind = 0;
    stack->next = NULL;

    return stack;
}

// добавление элемента в стек
int push_list(list_stack_r **stack, int data, int lim)
{
    if (full_list(*stack, lim))
        return PUSH_ERR;

    list_stack_r *stack_new = create_list_stack(data);
    if (!stack_new)
        return PUSH_ERR;

    stack_new->ind = (*stack)->ind + 1;
    stack_new->next = *stack;
    *stack = stack_new;

    return EXIT_SUCCESS;
}

// добавление элементов в стек
int input_stack_list(list_stack_r **stack, int count, int lim, int type, int elem)
{
    for (int i = 0; i < count; i++)
    {
        if (!(*stack))
            *stack = create_list_stack(elem);

        if (type)
        {
            if (scanf("%d", &elem) != 1)
            {
                printf("Incorrect element of stack.\n");
                return INPUT_ERR;
            }
        }

        if (push_list(stack, elem, lim))
            return PUSH_ERR;
    }

    return EXIT_SUCCESS;
}

// проверка на существование стека
int null_list(list_stack_r *stack)
{
    if (stack == NULL)
    {
        printf("\nStack is NULL.\n");
        return INPUT_ERR;
    }

    return EXIT_SUCCESS;
}

// проверка стека на пустоту
int empty_list_(list_stack_r *stack)
{
    return !stack;
}

// проверка стека на пустоту с сообщением
int empty_list(list_stack_r *stack)
{
    if (!stack)
    {
        printf("Stack is empty.\n");
        return EMPTY_ERR;
    }

    return EXIT_SUCCESS;
}

// проверка стека на переполнение
int full_list_(list_stack_r *stack, int lim)
{
    return stack->ind == lim;
}

// проверка стека на переполнение с сообщением
int full_list(list_stack_r *stack, int lim)
{
    if (stack->ind == lim)
    {
        printf("Stack is full.\n");
        return FULL_ERR;
    }

    return EXIT_SUCCESS;
}

// удаление элемета из стека
list_stack_r *pop_elem_list(list_stack_r *stack, int *elem, addresses_r *arr)
{

    if (empty_list(stack))
        return NULL;

    *elem = stack->data;
    list_stack_r *new_stack = stack->next;

    arr->arr[++arr->ind] = (size_t)stack;
    free(stack);
    return new_stack;
}

// удаление элемета из стека
int pop_elem_list_without_arr(list_stack_r **stack)
{
    if (empty_list(*stack))
        return POP_ERR;

    list_stack_r *cur = *stack;
    *stack = (*stack)->next;

    int p = cur->data;

    return p;
}

// вывод элементов из стека
int output_list_stack(list_stack_r *stack)
{
    empty_list(stack);

    list_stack_r *cur = stack;

    while (cur->next)
    {
        printf(" %d : %zx\n", cur->data, (size_t)(cur));
        cur = cur->next;
    }

    return EXIT_SUCCESS;
}

// освобождение списка
int free_list_stack(list_stack_r **stack, addresses_r *arr)
{
    int pop;
    while (!empty_list(*stack))
        pop_elem_list(*stack, &pop, arr);

    return EXIT_SUCCESS;
}

// создание массива пустых адресов
addresses_r *create_array_addresses(int capacity)
{
    addresses_r *array = (addresses_r *)malloc(200 * sizeof(addresses_r));
    if (!array)
        return NULL;

    array->cap = capacity;
    array->ind = -1;
    array->arr = (size_t *)malloc(sizeof(size_t));

    return array;
}

// проверка вершины стека
void check_top_list(list_stack_r *stack, addresses_r *arr, addresses_r *arr_two)
{
    size_t t = (size_t)stack;

    for (int i = 0; i <= arr->ind; i++)
    {
        if (t == arr->arr[i]) {
            for (int j = i; j < arr->ind - 1; j++) {
                size_t buf = arr->arr[j];
                arr->arr[j] = arr->arr[j + 1];
                arr->arr[j + 1] = buf;
            }
            arr->ind--;
        }
    }

    for (int i = 0; i <= arr_two->ind; i++)
    {
        if (t == arr_two->arr[i]) {
            for (int j = i; j < arr_two->ind - 1; j++) {
                size_t buf = arr_two->arr[j];
                arr_two->arr[j] = arr_two->arr[j + 1];
                arr_two->arr[j + 1] = buf;
            }
            arr_two->ind--;
        }
    }
}

// вывод массива пустых адресов
void output_array_addresses(addresses_r arr)
{
    if (arr.ind == -1)
    {
        printf("Array is empty.\n");
    }
    else
    {
        for (int i = 0; i < arr.ind + 1; i++)
            printf("%zx\n", arr.arr[i]);

        printf("\n");
    }
}

// сортировка одного стека
list_stack_r *sort_one_list(list_stack_r **one, int capacity)
{
    list_stack_r *three;
    three = create_list_stack((*one)->data);
    push_list(&three, (*one)->data, capacity);
    pop_elem_list_without_arr(one);

    while ((*one)->next != NULL)
    {
        while (three->data >= (*one)->data && empty_list_(*one))
        {
            push_list(&three, (*one)->data, capacity);
            pop_elem_list_without_arr(one);
        }

        if ((*one) == NULL)
            break;

        int buf = (*one)->data;
        pop_elem_list_without_arr(one);

        int count = 0;

        while (buf >= three->data && three->next != NULL)
        {
            push_list(one, three->data, capacity);
            pop_elem_list_without_arr(&three);
            count++;
        }

        push_list(&three, buf, capacity);

        for (int i = 0; i < count; i++)
        {
            push_list(&three, (*one)->data, capacity);
            pop_elem_list_without_arr(one);
        }
    }

    return three;
}


// сортровка двух стеков (результат - в третий)
list_stack_r *sort_list_stacks(list_stack_r *one, list_stack_r *two, int capacity)
{
    one = sort_one_list(&one, capacity);

    two = sort_one_list(&two, capacity);

    list_stack_r *three;

    if (one->data < two->data)
    {
        three = create_list_stack(one->data);
        push_list(&three, one->data, capacity);
        pop_elem_list_without_arr(&one);
    }
    else
    {
        three = create_list_stack(two->data);
        push_list(&three, two->data, capacity);
        pop_elem_list_without_arr(&two);
    }

    while ((one)->next && (two)->next)
    {
        if ((one)->data < (two)->data)
        {
            push_list(&three, (one)->data, capacity);
            pop_elem_list_without_arr(&one);
        }
        else
        {
            push_list(&three, (two)->data, capacity);
            pop_elem_list_without_arr(&two);
        }
    }


    while ((one)->next)
    {
        push_list(&three, (one)->data, capacity);
        pop_elem_list_without_arr(&one);
    }

    while ((two)->next)
    {
        push_list(&three, (two)->data, capacity);
        pop_elem_list_without_arr(&two);
    }

    return three;
}
