#include "graph.h"
#include "in_out.h"

// создать матрицу
matrix_r *create_matrix(int count)
{
    matrix_r *matrix = malloc(sizeof(matrix_r));
    if (matrix)
    {
        matrix->count = count;
        matrix->data = allocate_matrix(count);
        if (matrix->data == NULL)
        {
            free(matrix);
            matrix = NULL;
        }
    }

    return matrix;
}

// выделить память под матрицу
double **allocate_matrix(int count)
{
    double **data = calloc(count, sizeof(double*));
    if (data)
        for (int i = 0; i < count; ++i)
        {
            data[i] = calloc(count, sizeof(double));
            if (!data[i])
            {
                free_matrix(data, count);
                data = NULL;
            }
        }

    return data;
}

// освободить матрицу
void free_matrix(double **data, int count)
{
    for (int i = 0; i < count; ++i)
        free(data[i]);

    free(data);
}


// не пустая ли матрица
int check_empty_matrix(matrix_r *graph)
{
    if (graph->data == NULL)
    {
        printf(COLOR_YELLOW"\nДанные еще не были загружены.\nВыберите пункт 1.\n\n"COLOR_RESET);
        return GRAPH_ERR;
    }

    return EXIT_SUCCESS;
}

// не нулл ли граф
int check_graph_null(matrix_r *graph)
{
    if (graph == NULL)
    {
        printf(COLOR_YELLOW"\nГраф - NULL.\n\n"COLOR_RESET);
        return GRAPH_ERR;
    }

    return EXIT_SUCCESS;
}

// сравнительная характеристика
void timeget()
{
    FILE *f1 = fopen("data/in_10.txt", "r");
    if (f1)
    {
        FILE *f2 = fopen("data/in_50.txt", "r");
        if (f2)
        {
            FILE *f3 = fopen("data/in_100.txt", "r");
            if (f3)
            {
                FILE *f4 = fopen("data/in_500.txt", "r");
                if (f4)
                {
                    printf("\nПроизводится сравнение времени работы и памяти, \nзатраченной на работу, ");
                    printf(COLOR_YELLOW"алгоритма Дейкстры\n"COLOR_RESET);
                    printf("\n_______________________________\n");
                    printf("| Кол-во |  Время  |  Память  |\n");
                    printf("|________|_________|__________|\n");
                    clock_t start, end;

                    matrix_r *g4 = read_matrix(f4);
                    double arr4[g4->count];
                    start = clock();
                    Dijkstra(g4, arr4, 0);
                    end = clock();
                    printf("| %6d |  %5lu  |  %7zu |\n", 500, end - start, sizeof(double)*g4->count + sizeof(matrix_r*));
                    printf("|________|_________|__________|\n");

                    matrix_r *g3 = read_matrix(f3);
                    double arr3[g3->count];
                    start = clock();
                    Dijkstra(g3, arr3, 0);
                    end = clock();
                    printf("| %6d |  %5lu  |  %7zu |\n", 100, end - start, sizeof(double)*g3->count + sizeof(matrix_r*));
                    printf("|________|_________|__________|\n");

                    matrix_r *g2 = read_matrix(f2);
                    double arr2[g2->count];
                    start = clock();
                    Dijkstra(g2, arr2, 0);
                    end = clock();
                    printf("| %6d |  %5lu  |  %7zu |\n", 50, end - start, sizeof(double)*g2->count + sizeof(matrix_r*));
                    printf("|________|_________|__________|\n");

                    matrix_r *g1 = read_matrix(f1);
                    double arr1[g1->count];
                    start = clock();
                    Dijkstra(g1, arr1, 0);
                    end = clock();
                    printf("| %6d |  %5lu  |  %7zu |\n", 10, end - start, sizeof(double)*g1->count + sizeof(matrix_r*));
                    printf("|________|_________|__________|\n");

                    fclose(f4);
                }
                fclose(f3);
            }
            fclose(f2);
        }
        fclose(f1);
    }
}
