#include "hash.h"

// остаток от деления числа на размер таблицы
int hash_function(int key, int table_size)
{
    key > 0 ? (key) : (key *= -1);
    return key % table_size;
}

// создать таблицу
hash_t *create_table(int n)
{
    hash_t *table = malloc(sizeof (hash_t));
    table->data = new_table_data(n);
    table->max_size = n;
    table->size = 0;
    table->limit = 0;

    return table;
}

// выделение памяти ячеек таблицы
cell_t *new_table_data(int n)
{
    cell_t *cells = malloc(sizeof(cell_t) * n);
    if (cells)
        for (int i = 0; i < n; ++i)
        {
            cells[i].flag = 0;
            cells[i].value = 0;
        }

    return cells;
}

// проверить, записывалось ли уже число
int duplicate_key(hash_t *table, int key)
{
    int h = hash_function(key, table->max_size);
    int i = h;
    int limit = 0;

    while (limit < table->max_size)
    {
        limit++;
        if (table->data[hash_function(i, table->max_size)].value == key &&
            table->data[hash_function(i, table->max_size)].flag == 1)
                return EXIT_FAILURE;
        i++;
    }
    return EXIT_SUCCESS;
}

// если количество заполненных ячеек превысило макс возможное
hash_t *restruct(hash_t *table, int limit)
{
    int u;
    printf("\nРеструктурирование таблицы.\n");
    hash_t *new_table = create_table(table->max_size * 2);

    for (int i = 0; i < table->max_size; ++i)
        if (table->data[i].flag == 1)
            load_table(new_table, table->data[i].value, &u, limit);

    free(table->data);
    free(table);

    return new_table;
}

// увеличение размера таблицы и перезапись
hash_t *rewrite_hash(hash_t *table)
{
    int size = table->max_size;
    table->max_size += (table->max_size / 3);
    cell_t *newdata = new_table_data(table->max_size);

    for (int i = 0; i < size; ++i)
    {
        newdata[i].flag = table->data[i].flag;
        newdata[i].value = table->data[i].value;
    }
    free(table->data);
    table->data = newdata;

    return table;
}

// заполнение таблицы
hash_t *load_table(hash_t *table, int key, int *count, int limit)
{
    *count = 1;
    if (table == NULL)
        return NULL;

    // все ячейки заполнены
    if (table->max_size == table->size)
        table = rewrite_hash(table);

    // большое количество сравнений
     while (table->limit >= limit)
     {
         //printf("\nЭлемент %d ", key);
         table = restruct(table, limit);
     }

    // если ключ уже записан в таблицу (не записывается заново)
    if (duplicate_key(table, key))
        return table;

    int h = hash_function(key, table->max_size);
    int limit_cur = 0;
    while (table->data[h % table->max_size].flag == 1)
    {
        if (limit_cur >= table->max_size)
        {
            printf("Таблица переполнена.\n");
            break;
        }
        h++;
        (*count)++;
        limit_cur++;
    }

    if (h >= table->max_size)
        h = h % table->max_size;

    table->limit += (limit_cur == 0) ? 0 : 1;
    table->data[h].value = key;
    table->data[h].flag = 1;
    (table->size)++;

    return table;
}

// освобождение таблицы
void free_table(hash_t *table)
{
    if (table)
    {
        free(table->data);
        free(table);
    }
}
