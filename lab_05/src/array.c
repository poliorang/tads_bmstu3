#include "array.h"

unsigned long model_arr(int *mem_used)
{
    int all = TOTAL_NEED;
    struct queue_t *arr = malloc(all * sizeof(struct queue_t));
    struct queue queue;
    queue.pin = queue.pout = arr;
    queue.len = queue.in_num = queue.state = 0;
    queue.total_stay_time = 0;
    struct oa oa;
    oa.time = oa.downtime = 0;
    oa.processed_count = oa.triggering = 0;
    double total_time = 0;
    int f = 0;


    unsigned long time = tick(), t_buf1 = 0, t_buf2 = 0;
    while (f != 2 && oa.processed_count < TOTAL_NEED)
    {

        while (queue.len == 0 || oa.time > total_time)
        {
            new_req_arr(&total_time, &oa, &queue, arr, all);
            if (queue.len != 0 && queue.len != 1 && queue.pout == queue.pin)
                f = 2;
        }
        if (f != 2)
            f = processing_arr(&oa, &queue, arr, all);
        t_buf1 = tick();
        if (f == 1 && oa.processed_count % INTER_NEED == 0)
        {
            printf(COLOR_BLUE "%s" COLOR_RESET,
                    "\nВышло заявок: ");
            printf("%d\n", oa.processed_count);
            printf("Текущая длина очереди: %d\n", queue.len);
            printf("Средняя длина очереди: %.2f\n\n", (double)(queue.state / oa.triggering));
        }
        t_buf2 += tick() - t_buf1;
        if (f == 1)
            f = 0;
    }
    time = tick() - time - t_buf2;
    if (f == 2)
        printf("\nНи одна из 1000 заявок не вышла из очереди.\n");
    else
    {
        double model = 0;
        if ((double)(COMING_END + COMING_START) / 2 >= (double)(PROCESSING_END + PROCESSING_START) / 2)
            model = ((double)(COMING_END + COMING_START) / 2) * TOTAL_NEED;
        else
            model = ((double)(PROCESSING_END + PROCESSING_START) / 2) * TOTAL_NEED * (1 / (1 - CHANCE));
        if ((COMING_START == 0) && (COMING_END == 6) && (PROCESSING_END == 1) && (PROCESSING_START == 0))
            model = ((double)(COMING_END + COMING_START) / 2) * TOTAL_NEED;
     
        *mem_used = all * (sizeof(struct queue_t) - sizeof(struct queue_t*));
        printf("Ожидаемое время моделирования: %.2f\n", model);
        printf("Полученное время моделирования: %.2f\n", oa.time);
        printf("Погрешность: %.2f%%\n\n", fabs((oa.time - model) / model * 100));
        printf("Количество вошедших заявок: %d\n", queue.in_num);
        printf("Количество вышедших заявок: %d\n", oa.processed_count);
        printf("Среднее время в очереди: %.2f\n", queue.total_stay_time / oa.processed_count);
        printf("Время простоя аппарата: %.2f\n", oa.downtime);
        printf("Количество срабатывания аппарата: %d\n\n", oa.triggering);
    }
    free(arr);

    return time;
}

void new_req_arr(double *total_time, struct oa *oa, struct queue *queue, struct queue_t *array, int mass_len)
{
    double time = get_time(COMING_START, COMING_END);
    *total_time += time;
    if (queue->len == 0 && *total_time > oa->time)
    {
        oa->downtime += *total_time - oa->time;
        oa->time = *total_time;
    }

    if (queue->len > 1 && queue->pin != queue->pout)
    {
        if (queue->pin == array + mass_len - 1)
            queue->pin = array;
        else
            queue->pin++;
    }
    if (queue->len == 1)
    {
        if (queue->pin == array + mass_len - 1)
            queue->pin = array;
        else
            queue->pin++;
    }

    queue->pin->arrival_time = *total_time;
    queue->len++;
    queue->in_num++;
}

int processing_arr(struct oa *oa, struct queue *queue, struct queue_t *arr, int arr_len)
{
    int f = 0;

    queue->state += queue->len;
    oa->triggering++;
    oa->time += get_time(PROCESSING_START, PROCESSING_END);
    struct queue_t *buf = queue->pout;
    if (queue->pout == arr + arr_len - 1)
        queue->pout = arr;
    else
        queue->pout++;
    if (!chance(CHANCE))
    {
        if (queue->pin == arr + arr_len - 1)
            queue->pin = arr;
        else
            queue->pin++;
        queue->pin->arrival_time = buf->arrival_time;
    }
    else
    {
        if (queue->len == 1)
            queue->pin = queue->pout;
        queue->total_stay_time += oa->time - buf->arrival_time;
        oa->processed_count++;
        queue->len--;
        f = 1;
    }
    return f;
}
