#ifndef DOT_H
#define DOT_H

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void export_to_dot(FILE *f, node_t *head);
void to_dot(node_t *head, void *p);
void get_dot_file(node_t *head, node_t *head_balance);

#endif
