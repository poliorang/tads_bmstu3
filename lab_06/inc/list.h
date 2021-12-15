#ifndef _LIST_H_
#define _LIST_H_

#include "errors_structures.h"

node_t *create_node(int data, int height);
node_t *insert(node_t *head, node_t *node, int *rc);
int what_height(node_t *head);
void new_height(node_t *head);
int factorlr(node_t *head);
int search_num_in_file(FILE *f, int num);
node_t *turn_right(node_t *head);
node_t *turn_left(node_t *head);
node_t *balance_node(node_t *head);
node_t *insert_balance(node_t *head, node_t *node, int *rc);
void print_tree(node_t *head, int down, int lr);
void free_tree(node_t *head);
void apply_pre(node_t *head, void (*f)(node_t *, void *), void *arg);
void apply_po(node_t *head, void (*f)(node_t *), void *arg);

#endif
