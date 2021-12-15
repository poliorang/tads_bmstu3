#ifndef ERR_H
#define ERR_H

#define INPUT_ERR 1
#define GRAPH_ERR 2

#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_RESET "\x1b[0m"

// матрица смежности
typedef struct
{
    int count; // количество вершин
    double **data; // данные
} matrix_r;


#endif
