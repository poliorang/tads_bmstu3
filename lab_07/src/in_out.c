#include "in_out.h"
#include "graph.h"

void welcome_print()
{
    printf(COLOR_GREEN"%s" COLOR_RESET "%s",
           "\n\nМеню\n\n",
           "1  - Загрузить граф из файла\n"
           "2  - Ввести граф вручную\n"
           "3  - Вывести граф\n"
           "4  - Вывести матрицу графа\n"
           "5  - Найти вершины, путь до которых\n"
           "        от заданной не длиннее А\n"
           "6  - Вывести сравнительную характеристику\n"
           "0  - Выход\n"
           "\nВведите номер команды: ");
}

// считать матрицу из файла
matrix_r *read_matrix(FILE *f)
{
    int count;
    if (fscanf(f, "%d", &count) != 1)
        return NULL;

    matrix_r *matrix = create_matrix(count);
    double num;

    for (int i = 0; i < count; ++i)
        for (int j = 0; j < count; ++j)
        {
            if (fscanf(f, "%lf", &num) != 1 || num < 0)
            {
                printf(COLOR_YELLOW"\nНеверный элемент.\n"COLOR_RESET);
                return NULL;
            }

            matrix->data[i][j] = num;
        }

    return matrix;
}

// напечатать матрицу
void print_matrix(FILE *f, matrix_r *graph)
{
    if (check_graph_null(graph))
        return;

    for (int i = 0; i < graph->count; ++i)
        for (int j = 0; j < graph->count; ++j)
            fprintf(f, "%6.2lf%c", graph->data[i][j], j < graph->count - 1 ? ' ' : '\n');
}

// в язык дот
void to_dot(matrix_r *graph)
{
    FILE *f = fopen("data/Graph.gv", "w");

    if (check_graph_null(graph))
        return;

    fprintf(f, "digraph LAB_07 {\n");

    for (int i = 0; i < graph->count; ++i)
        for (int j = 0; j < graph->count; ++j)
            if (graph->data[i][j] < MAX_SIZE && graph->data[i][j] != 0)
                fprintf(f, "%d -> %d [label=\"%.1f\"];\n", i, j, graph->data[i][j]);

    fprintf(f, "}\n");
    fclose(f);
}

// пример ручного ввода матрицы
void example(void)
{
    printf(COLOR_GREEN"\nПример:\n" COLOR_RESET);
    printf("\n3\n"
           "0 4 2\n"
           "7 1 9\n"
           "5 8 2\n\n");
}

// создать файл c последовательностью чисел
int generate_file()
{
    int height_for_gen = 0;
    printf("Введите количество вершин: ");
    if ((scanf("%d", &height_for_gen)) != 1 || height_for_gen <= 1)
    {
        printf("\nНеверное количество вершин.\n");
        return EXIT_FAILURE;
    }
    char gen[50] = "python generate_graph.py";
    char args[50];
    sprintf(args, " %d", height_for_gen);
    system(strcat(gen, args));

    return EXIT_SUCCESS;
}

// выбор открываемого файла
int get_file(void)
{
    printf(COLOR_YELLOW"Загрузка данных.\n"COLOR_RESET);

    printf("\nФайлы:\n"
           "1 - готовый файл (test1.txt)\n"
           "2 - сгенерировать файл (test2.txt)\n\n"
           "Выберите число: ");

    int file = 0;
    if (scanf("%d", &file) != 1 || file < 1 || file > 2)
    {
        printf(COLOR_YELLOW"Неверно выбран файл.\n\n"COLOR_RESET);
        return -1;
    }

    if (file == 2)
        if (generate_file())
            return -1;

    return file;
}

// ключевая вершина для пункта 5
static int get_top_and_way(int *top, double *min_way, matrix_r *graph)
{
    printf("\nВведите ключевую вершину (номер): ");
    if (scanf("%d", top) != 1 || *top < 0 || *top > graph->count)
    {
        printf(COLOR_YELLOW"Неверный номер.\n"COLOR_RESET);
        return INPUT_ERR;
    }

    printf("\nВведите максимальную длину А: ");
    if (scanf("%lf", min_way) != 0 && *min_way < 0)
    {
        printf("Число должно быть неотрицательным.\n");
        return GRAPH_ERR;
    }

    return EXIT_SUCCESS;
}

// номер команды
int get_command(int *command)
{
    welcome_print();
    fflush(stdin);
    if (scanf("%d", command) != 1 || *command < 0 || *command > 6)
    {
        printf("\nНеверная команда.\n");
        return INPUT_ERR;
    }

    return EXIT_SUCCESS;
}

// алгоритм Дейкстры
void Dijkstra(matrix_r *graph, double distance[graph->count], int top)
{
    int visited[graph->count]; // посещенные вершины
    int buf = 0;

    for (int i = 0; i < graph->count; i++)
    {
        distance[i] = INT_MAX;
        visited[i] = 0;
    }

    distance[top] = 0;
    for (int count = 0; count < graph->count - 1; count++)
    {
        int min = INT_MAX;
        for (int i = 0; i < graph->count; i++)
        {
            if (visited[i] == 0 && distance[i] <= min)
            {
                min = distance[i];
                buf = i;
            }
        }

        visited[buf] = 1;
        for (int i = 0; i < graph->count; i++)
        {
            if (visited[i] == 0 && graph->data[buf][i] && distance[buf] != INT_MAX &&
                distance[buf] + graph->data[buf][i] < distance[i])
                distance[i] = distance[buf] + graph->data[buf][i];
        }
    }
}

// поиск путей по заданию с помощью алгоритма Дейкстры
int find_tops_with_Dijkstra(matrix_r *graph, int *count)
{
    if (check_graph_null(graph))
        return GRAPH_ERR;

    int top = 0;
    double max_way = 0;
    if (get_top_and_way(&top, &max_way, graph))
        return INPUT_ERR;

    double distance[graph->count];
    Dijkstra(graph, distance, top);

    printf(COLOR_BLUE"\n\nФиолетовым"COLOR_RESET);
    printf(" будут выделены вершины,\nрасстояние до которых от заданной \nменьше, чем указанное\n\n");

    FILE *f = fopen("data/Task.gv", "w");
    fprintf(f, "digraph LAB_07 {\n");
    for (int i = 0; i < graph->count; i++)
        if (distance[i] != INT_MAX && i != top)
        {
            if (distance[i] < max_way)
            {
                (*count)++;
                fprintf(f, "%d -> %d [label=\"%.1f\"];\n", top, i, distance[i]);
                printf("%d -> ", top);
                printf(COLOR_BLUE"%d "COLOR_RESET, i);
                printf("= %lf \n", distance[i]);
            }
            else
                printf("%d -> %d = %lf \n", top, i, distance[i]);
        }
    fprintf(f, "}\n");
    fclose(f);
    return EXIT_SUCCESS;

}
