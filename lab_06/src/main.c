#include "errors_structures.h"
#include "print.h"
#include "list.h"
#include "hash.h"
#include "timememory.h"
#include "dot.h"

char files[2][100] = {"data/test1.txt", "data/test2.txt"};
int file = 1;

int main()
{
    node_t *head = NULL, *head_balance = NULL;
    hash_t *hash_table = NULL;
    int count, rc = 0, command = -1, num = 0;
    FILE *f;

    while(command != 0)
    {
        welcome_print();
        if (scanf("%d", &command) != 1 || command < 0 || command > 5)
        {
            printf("\nНеверная команда.\n");
            break;
        }
        switch (command)
        {
            case (0):
                return EXIT_SUCCESS;

            case (1):
                printf(COLOR_YELLOW"Загрузка данных.\n"COLOR_RESET);

                printf("\nФайлы:\n"
                       "1 - готовый файл (test1.txt)\n"
                       "2 - сгенерировать файл (test2.txt)\n\n"
                       "Выберите число: ");

                if (scanf("%d", &file) != 1 || file < 1 || file > 2)
                {
                    printf(COLOR_YELLOW"Неверно выбран файл.\n\n"COLOR_RESET);
                    break;
                }

                if (file == 2)
                    if (generate_file())
                        break;

                free_tree(head);
                free_tree(head_balance);
                f = fopen(files[file - 1], "r");
                if (f == NULL)
                {
                    printf(COLOR_YELLOW"Ошибка открытия файла.\n\n"COLOR_RESET);
                    break;
                }

                count = read_to_tree(f, &head, &head_balance, &rc);
                fclose(f);

                if (count > 0)
                {
                    f = fopen(files[file - 1], "r");
                    if (f == NULL)
                    {
                        printf(COLOR_YELLOW"Ошибка открытия файла.\n\n"COLOR_RESET);
                        break;
                    }
                    free_table(hash_table);
                    read_to_table(f, &hash_table, LIMIT);
                    fclose(f);
                }
                printf(COLOR_YELLOW"\nДанные были успешно загружены.\n\n"COLOR_RESET);
                break;

            case (2):
                if (check_tree(head, head_balance))
                    break;

                get_dot_file(head, head_balance);

                printf(COLOR_YELLOW"\nХэш-таблица\n"COLOR_RESET);
                table_print(hash_table);
                printf("\n");
                system("open data/Tree.gv");
                system("open data/Balance_tree.gv");
                break;

            case (3):
                if (check_tree(head, head_balance))
                    break;

                rc = 0;
                fprintf(stdout, "Введите добавляемое число: ");
                if (fscanf(stdin, "%d", &num) != 1)
                {
                    printf(COLOR_YELLOW"Ошибка ввода.\n"COLOR_RESET);
                    break;
                }

                node_t *cur = create_node(num, 1);
                node_t *cur_bal = create_node(num, 1);

                head = insert(head, cur, &rc);
                head_balance = insert_balance(head_balance, cur_bal, &rc);

                if (!hash_table)
                    hash_table = create_table(SIZE);

                hash_table = load_table(hash_table, num, &rc, LIMIT);

                f = fopen(files[file - 1], "r");
                int sear = search_num_in_file(f, num);
                fclose(f);

                if (sear == 0)
                {
                    f = fopen(files[file - 1], "a");
                    fprintf(f, "%d\n", num);
                    fclose(f);
                    printf(COLOR_YELLOW"\nЧисло успешно добавлено.\n"COLOR_RESET);
                }
                else
                    printf(COLOR_YELLOW"\nЧисло уже существует.\n"COLOR_RESET);

                get_dot_file(head, head_balance);

                break;

            case (4):
                if (check_tree(head, head_balance))
                    break;
                f = fopen(files[file - 1], "r+");
                timememory(head, head_balance, hash_table, f);
                fclose(f);
                break;

            case (5):
                time_restruct();
                break;

            default:
                break;
        }
    }
}
