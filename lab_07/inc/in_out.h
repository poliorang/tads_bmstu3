#ifndef IO_H
#define IO_H

#include "errors_structures.h"
#include "graph.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 4000

void welcome_print();
matrix_r *read_matrix(FILE *f);
void print_matrix(FILE *f, matrix_r *graph);
void to_dot(matrix_r *graph);
void example(void);
int get_file(void);
int get_command(int *command);
int get_ways(matrix_r *graph, int *count);
void Dijkstra(matrix_r *graph, double distance[graph->count], int top);
int find_tops_with_Dijkstra(matrix_r *graph, int *count);

#endif
