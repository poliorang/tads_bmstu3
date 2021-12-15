#include "list.h"

unsigned long model_list(struct mem_t **mem, int *mem_used)
{
    struct queue queue;
    queue.pin = queue.pout = NULL;
    queue.len = queue.in_num = queue.state = queue.max = 0;
    queue.total_stay_time = 0;
    struct oa oa;


    oa.time = oa.downtime = 0;
    oa.processed_count = oa.triggering = 0;
    double total_time = 0;
    int f = 0;

    if (CHANCE >= 1)
    {
        printf("\nНи одна из 1000 заявок не вышла из очереди.\n");
        exit(EXIT_FAILURE);
    }
    unsigned long time = tick(), t_buf1 = 0, t_buf2 = 0;
    while (oa.processed_count < TOTAL_NEED)
    {
        while (queue.len == 0 || oa.time > total_time)
        {
            new_req(&total_time, &queue, &oa, mem);
        }
        f = processing(&oa, &queue, mem);
        t_buf1 = tick();
        if (f && oa.processed_count % INTER_NEED == 0)
        {
            printf(COLOR_BLUE "%s" COLOR_RESET,
                    "\nВышло заявок: ");
            printf("%d\n", oa.processed_count);
            printf("Текущая длина очереди: %d\n", queue.len);
            printf("Средняя длина очереди: %.2f\n\n", (float)(queue.state / oa.triggering));
        }
        t_buf2 += tick() - t_buf1;
        if (f)
            f = 0;
    }
    time = tick() - time - t_buf2;
    double model = 0;
    
    if ((double)(COMING_END + COMING_START) / 2 >= (double)(PROCESSING_END + PROCESSING_START) / 2)
        model = ((double)(COMING_END + COMING_START) / 2) * TOTAL_NEED;
    else
        model = (double)(PROCESSING_END + PROCESSING_START) / 2 * TOTAL_NEED * (1 / (1 - CHANCE));

    if ((COMING_START == 0) && (COMING_END == 6) && (PROCESSING_END == 1) && (PROCESSING_START == 0))
        model = ((double)(COMING_END + COMING_START) / 2) * TOTAL_NEED;
    
    *mem_used = queue.max * (sizeof(struct queue_t) + sizeof (double));
    
    printf("Ожидаемое время моделирования: %.2f\n", model);
    printf("Полученное время моделирования: %.2f\n", oa.time);
    printf("Погрешность: %.2f%%\n\n", fabs((oa.time - model) / model * 100));
    printf("Количество вошедших заявок: %d\n", queue.in_num);
    printf("Количество вышедших заявок: %d\n", oa.processed_count);
    printf("Среднее время в очереди: %.2f\n", queue.total_stay_time / oa.processed_count);
    printf("Время простоя аппарата: %.2f\n", oa.downtime);
    printf("Количество срабатывания аппарата: %d\n\n", oa.triggering);
    return time;
}

void new_req(double *total_time, struct queue *queue, struct oa *oa, struct mem_t **mem)
{
    double time = get_time(COMING_START, COMING_END);

    *total_time += time;
    if (queue->len == 0 && *total_time > oa->time)
    {
        oa->downtime += *total_time - oa->time;
        oa->time = *total_time;
    }


    struct queue_t *buf = malloc(sizeof(struct queue_t));
    if (queue->pin != NULL)
        queue->pin->next = buf;
    buf->next = NULL;
    buf->arrival_time = *total_time;
    queue->pin = buf;
    if (queue->len == 0)
        queue->pout = buf;
    queue->len++;
    queue->in_num++;
    add_mem(buf, mem);
}

int processing(struct oa *oa, struct queue *queue, struct mem_t **mem)
{
    int f = 0;
    queue->state += queue->len;
    if (queue->len > queue->max)
        queue->max = queue->len;
    oa->triggering++;
    oa->time += get_time(PROCESSING_START, PROCESSING_END);
    struct queue_t *buf = queue->pout;
    if (queue->len > 1)
        queue->pout = buf->next;
    //printf("\n%lf\n", CHANCE);
    if (!chance(CHANCE))
    {
        queue->pin->next = buf;
        queue->pin = buf;
        buf->next = NULL;
    }

    else
    {
        if (queue->len == 1)
            queue->pin = queue->pout = NULL;
        queue->total_stay_time += oa->time - buf->arrival_time;
        oa->processed_count++;
        queue->len--;
        free(buf);
        delete_mem(buf, *mem);
        f = 1;
    }
    return f;
}

void show_mem(struct mem_t **mem)
{
    struct mem_t *buf = *mem, *buf1;
    if (buf == NULL)
        printf("\nНе смоделирована очередь-список.\n\n");
    else
    {
        int flag = 0;

        printf(COLOR_YELLOW "%s" COLOR_RESET, "Желтый адрес");
        printf(" - адрес использован заново\nБелый адрес - адрес не использован заново\n");
        printf("\nCписок использованных заново адресов (для первых 50 элементов):\n\n");
        while (buf != NULL && flag != 50)
        {
            buf->busy != 1 ? printf("%p\n", (void*)buf->queue_slot) :
                printf(COLOR_YELLOW "%p\n" COLOR_RESET, (void*)buf->queue_slot);

            buf1 = buf;
            buf = buf->next;
            free(buf1);
            flag++;
        }
        *mem = NULL;
    }
}

void queue_compare(struct mem_t **mem)
{
    int mem1 = 0, mem2 = 0;
    unsigned long t1 = model_list(mem, &mem1);
    unsigned long t2 = model_arr(&mem2);
 
    struct mem_t *buf = *mem;
    while (buf)
    {
        *mem = buf->next;
        free(buf);
        buf = *mem;
    }
    printf(COLOR_YELLOW "%s" COLOR_RESET,
            "\nСравнение:\n");

    printf("Время для списка: %lu тиков\n", t1);
    printf("Время для массива: %lu тиков\n\n", t2);
    printf("Память для списка: %d байт\n", mem1);
    printf("Память для массива: %d байт\n", mem2);
}
