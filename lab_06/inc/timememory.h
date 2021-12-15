#ifndef TIMEMEMORY_H
#define TIMEMEMORY_H

#include "errors_structures.h"
#include "list.h"
#include "hash.h"
#include "print.h"

void timememory(node_t *head, node_t *headbal, hash_t *table, FILE *f);
void time_restruct();

#endif
