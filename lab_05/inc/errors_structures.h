#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "math.h"

#define ERROR_KEY 1

#define TOTAL_NEED 2000 // суммарное число обработанных заявок
#define INTER_NEED 100 // число заявок, после которого нужно предоставить инфо о сост ОА

#define COMING_START 0 // мин время прихода
#define COMING_END 6 // макс время прихода
#define PROCESSING_START 0 // мин время обработки
#define PROCESSING_END 1 // макс время обработки

#define CHANCE 0.8 // вероятность

#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_RESET "\x1b[0m"


// очередь-список
struct queue_t
{
    double arrival_time; // время прихода в очередь
    struct queue_t *next; // указатель на след элемент
};

// очередь-массив
struct queue
{
    struct queue_t *pin; // указатель на начало очереди
    struct queue_t *pout; // указатель на конец очереди
    int len; // длина очереди
    int in_num; // число вошедших в очередь заявок
    int state; //для средней длины
    int max; // переменная для подсчета очереди в списке
    double total_stay_time; // время нахождения заявок в очереди
};

// обслуживающий аппарат
struct oa
{
    double time; //текущее время состояния аппарата 
    double downtime; // время простоя аппарата
    int triggering; // количество срабатывания аппарата
    int processed_count; //кол-во обработанных из очереди заявок
};

// массив адресов памяти
struct mem_t
{
    struct queue_t *queue_slot; //указатель на участок памяти
    int busy; // состояние участка 1 (занят) или 0
    struct mem_t *next; // указатель на след элемент очереди
};

unsigned long long tick(void);
double get_time(int t1, int t2);
int chance(double ch);
void add_mem(struct queue_t *slot, struct mem_t **mem);
void delete_mem(struct queue_t *slot, struct mem_t *mem);

#endif
