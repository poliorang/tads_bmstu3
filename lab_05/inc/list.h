#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "errors_structures.h"
#include "array.h"


unsigned long model_list(struct mem_t **mem, int *mem_used);
void new_req(double *total_time, struct queue *queue, struct oa *oa, struct mem_t **mem);
int processing(struct oa *oa, struct queue *queue, struct mem_t **mem);
void queue_compare(struct mem_t **mem);
void show_mem(struct mem_t **mem);

#endif
