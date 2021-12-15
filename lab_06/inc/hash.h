#ifndef _HASH_H_
#define _HASH_H_

#include "errors_structures.h"

int hash_function(int key, int len);
cell_t *new_table_data(int n);
hash_t *rewrite_hash(hash_t *table);
int duplicate_key(hash_t *table, int key);
hash_t *create_table(int n);
hash_t *restruct(hash_t *table, int limit);
hash_t* load_table(hash_t *table, int key, int *count, int limit);
void free_table(hash_t *table);

#endif
