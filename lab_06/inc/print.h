#ifndef PRINT_H
#define PRINT_H

#include "errors_structures.h"

void welcome_print();
int read_to_tree(FILE *f, node_t **head, node_t **head_bal, int *rc);
void read_to_table(FILE *f, hash_t **table, int limit);
int generate_file();
void table_print(hash_t *hash_table);
int check_tree(node_t *head, node_t *balance_head);

#endif
