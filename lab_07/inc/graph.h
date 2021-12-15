#ifndef GRAPH_H
#define GRAPH_H

#include "errors_structures.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>

matrix_r *create_matrix(int count);
double **allocate_matrix(int count);
void free_matrix(double **data, int count);
int check_empty_matrix(matrix_r *graph);
int check_graph_null(matrix_r *graph);
matrix_r *all_way(matrix_r *graph);
void timeget();

#endif
