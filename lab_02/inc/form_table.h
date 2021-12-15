#ifndef FORM_TABLE_H
#define FORM_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read.h"

#include "structures.h"

#define OPEN_FILE_ERR 1
#define SIZE_ERR 2
#define DOWNLOAD_ERR 3

int file_size(FILE *f, table_r *table);
int download_from_file(table_r *table);
void clean_table(table_r *table);
void clean_field(table_r *table, int ind);

#endif
