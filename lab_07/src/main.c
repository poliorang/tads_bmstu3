#include "errors_structures.h"
#include "graph.h"
#include "in_out.h"

char files[2][50] = { "data/test1.txt", "data/test2.txt" };

int main()
{
    setbuf(stdout, NULL);
    FILE *f_in = NULL;
    matrix_r *graph = malloc(sizeof(matrix_r*));
    graph->data = NULL;
    graph->count = 0;
    int command = -1, file, count_tops = 0;

    while (command)
    {
        get_command(&command);
        switch (command)
        {
            case 1:
                free_matrix(graph->data, 0);
                graph = NULL;

                if ((file = get_file()) < 1)
                    break;

                f_in = fopen(files[file - 1], "r");

                if (f_in == NULL)
                {
                    printf(COLOR_YELLOW"\nОшибка открытия файла.\n"COLOR_RESET);
                    break;
                }

                graph = read_matrix(f_in);
                print_matrix(stdout, graph);
                break;

            case 2:
                example();
                free_matrix(graph->data, 0);
                graph = NULL;
                printf("Последовательно введите количество вершин и вес ребер: \n");
                graph = read_matrix(stdin);
                break;

            case 3:
                if (check_graph_null(graph))
                    break;
                to_dot(graph);
                system("open data/Graph.gv");
                break;

            case 4:
                if (check_empty_matrix(graph))
                    break;
                print_matrix(stdout, graph);
                break;

            case 5:
                if (check_empty_matrix(graph))
                    break;

                find_tops_with_Dijkstra(graph, &count_tops);
                if (count_tops)
                    system("open data/Task.gv");
                break;

            case 6:
                timeget();
                break;

            default:
                break;
        }
    }

    return EXIT_SUCCESS;
}
