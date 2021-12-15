#include "errors_structures.h"

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc": "=A" (d));
    return d;
}

// рандомное время из промежутка
double get_time(int t1, int t2)
{
    double r = (double)rand() / (double)RAND_MAX;
    r = (t2 - t1) * r + t1;
    return r;
}

// вероятность
int chance(double ch)
{
    if (ch == 0.0)
        return 1;
    int count = 0;
    for (; ch < 1; ch *= 10, count++);

    int hundred_percent = (int)pow(10.0, count);

    int ind = rand() % hundred_percent;
    if (ind < ch)
        return 0;
    return 1;
}

void add_mem(struct queue_t *t, struct mem_t **mem)
{
    struct mem_t *buf = malloc(sizeof(struct mem_t));
    buf->queue_slot = t;
    buf->busy = 1;
    buf->next = *mem;
    *mem = buf;
}

void delete_mem(struct queue_t *slot, struct mem_t *mem)
{
    struct mem_t *buf = mem;
    int f = 0;
    while (!f && buf != NULL)
    {
        if (buf->queue_slot == slot)
        {
            f = 1;
            buf->busy = 0;
        }
        buf = buf->next;
    }
}
