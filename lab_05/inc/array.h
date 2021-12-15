#ifndef ARRAY_H
#define ARRAY_H

#include "errors_structures.h"

unsigned long model_arr(int *mem_used);
void new_req_arr(double *total_time, struct oa *oa, struct queue *queue, struct queue_t *array, int mass_len);
int processing_arr(struct oa *oa, struct queue *queue, struct queue_t *arr, int arr_len);

#endif
