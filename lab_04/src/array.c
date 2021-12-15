#include "array.h"

// создание стека в виде массива
array_stack_r *create_array_stack(int capacity)
{
    array_stack_r *stack = (array_stack_r *)malloc(sizeof(array_stack_r));
    if (!stack)
        return NULL;

    stack->top = -1;
    stack->cap = capacity;
    stack->arr = (int *)malloc(stack->cap * sizeof(int));

    if (!stack->arr)
    {
        printf("Errors with memory.\n");
        free(stack);
        return NULL;
    }

    return stack;
}

// добавление элемента в стек
int push_elem_array(array_stack_r *stack, int elem)
{
    if (full_array_(stack))
        return PUSH_ERR;

    stack->arr[++stack->top] = elem;

    return EXIT_SUCCESS;
}

// ввод элементов в стек
int input_array_stack(array_stack_r *stack, int count, int type_input, int elem)
{
    for (int i = 0; i < count; i++)
    {
        if (type_input)
            if (scanf("%d", &elem) != 1)
            {
                printf("Incorrect element of stack.\n");
                return INPUT_ERR;
            }

        if (push_elem_array(stack, elem))
            return FULL_ERR;
    }

    return EXIT_SUCCESS;
}

// проверка на существование
int null_array(array_stack_r *stack)
{
    if (stack == NULL)
    {
        printf("\nStack is NULL.\n");
        return INPUT_ERR;
    }

    return EXIT_SUCCESS;
}

// проверка стека на пустоту с сообщением
int empty_array(array_stack_r *stack)
{
    if (stack->top == -1) {
        printf("\nStack is empty.\n");
        return EMPTY_ERR;
    }

    return EXIT_SUCCESS;
}

// проверка стека на пустоту
int empty_array_(array_stack_r *stack)
{
    return stack->top == -1;
}

// проверка стека на переполнение с сообщением
int full_array(array_stack_r *stack)
{
    if (stack->top == stack->cap - 1)
    {
        printf("\nStack is full.\n");
        return FULL_ERR;
    }

    return EXIT_SUCCESS;
}

// проверка стека на переполнение
int full_array_(array_stack_r *stack)
{
    return stack->top == stack->cap - 1;
}

// удаление элемента из стека
int pop_elem_array(array_stack_r *stack)
{
    if (empty_array_(stack))
        return POP_ERR;

    return stack->arr[stack->top--];
}

// вывод стека
int output_array_stack(array_stack_r *stack)
{
    empty_array(stack);

    for (int top = stack->top; top >= 0; top--)
    {
        if (stack->arr[top] < 2000)
            printf("%d ", stack->arr[top]);
    }

    printf("\n\n");

    return EXIT_SUCCESS;
}

// сортировка одного стека
void sort_one_array(array_stack_r *one, int capacity)
{
    array_stack_r *three = NULL;
    three = create_array_stack(capacity);

    push_elem_array(three, one->arr[one->top]);
    pop_elem_array(one);

    while (!empty_array_(one))
    {
        //printf("%d > %d\n", three->arr[three->top], one->arr[one->top]);
        while (three->arr[three->top] >= one->arr[one->top])
        {
            push_elem_array(three, one->arr[one->top]);
            pop_elem_array(one);
        }
        if (empty_array_(one))
            continue;

        int buf = one->arr[one->top];
        pop_elem_array(one);

        int count = 0;

        while (buf >= three->arr[three->top] && !empty_array_(three))
        {
            //printf("%d > %d\n", buf, three->arr[three->top]);
            push_elem_array(one, three->arr[three->top]);
            pop_elem_array(three);
            count++;
        }

        push_elem_array(three, buf);

        for (int i = 0; i < count; i++)
        {
            push_elem_array(three, one->arr[one->top]);
            pop_elem_array(one);
        }

    }

    while (!empty_array_(three))
    {
        push_elem_array(one, three->arr[three->top]);
        pop_elem_array(three);
    }
}

// сортровка двух стеков (результат - в третий)
array_stack_r *sort_array_stacks(array_stack_r *one, array_stack_r *two)
{
    sort_one_array(one, one->cap);
    sort_one_array(two, two->cap);

    array_stack_r *three;
    if ((three = create_array_stack(one->cap + two->cap)) == NULL)
        return NULL;

    while (!empty_array_(one) && !empty_array_(two))
    {
        if (one->arr[one->top] > two->arr[two->top])
        {
            push_elem_array(three, one->arr[one->top]);
            pop_elem_array(one);
        }
        else
        {
            push_elem_array(three, two->arr[two->top]);
            pop_elem_array(two);
        };
    }

    while (!empty_array_(one))
    {
        push_elem_array(three, one->arr[one->top]);
        pop_elem_array(one);
    }

    while (!empty_array_(two))
    {
        push_elem_array(three, two->arr[two->top]);
        pop_elem_array(two);
    }

    return three;
}
