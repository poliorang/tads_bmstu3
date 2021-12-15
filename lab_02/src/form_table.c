#include "form_table.h"

int file_size(FILE *f, table_r *table)
{
    if (fscanf(f, "%d", &table->size) != 1 || table->size < 1)
        return SIZE_ERR;

    return OK;
}

int download_from_file(table_r *table)
{
    FILE *f = fopen(FILE_NAME, "r");

    if (f == NULL)
    {
        fclose(f);
        printf("File errors.\n");
        return OPEN_FILE_ERR;
    }

    if (file_size(f, table))
    {
        printf("Incorrect data about the size of the table");
        return SIZE_ERR;
    }
    int size = table->size;

    for (int i = 0; i < size; i++)
    {
        if (read_field(f, table, i))
            return DOWNLOAD_ERR;
    }

    return OK;
}

void clean_table(table_r *table)
{
    for (int i = 0; i < table->size; i++)
    {
        table->playbill[i].price_range[0] = 0;
        table->key[i].key = 0;
    }
    table->size = 0;
}

void clean_field(table_r *table, int ind)
{
    table->playbill[ind].price_range[0] = 0;
    table->key[ind].key = 0;
    table->size -= 1;
}
