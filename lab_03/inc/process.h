#ifndef PROCES_H
#define PROCES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct list
{
    int data;
    struct list *next;
} list;

void create_list(int n, list *head);
void write_list(list *head, int ind, int data);
int read_list(list *head, int ind);
void free_list(int n, list *head);
void print_list(int n, list *head);
void create_mat(int c, int r, int d, int a[], int ia[], list *head, int flag);
void create_vec(int r, int d, int a[], int ia[], list *head, int flag);
int* vect_mult(int c, int r, clock_t *start, clock_t *end);
int* classic_mult(int c, int r, clock_t *start, clock_t *end);
void print_aij(int res[], int n);
int input_obj(int r, int c);

#endif
