#include "timememory.h"

void timememory(node_t *head, node_t *headbal, hash_t *table, FILE *f)
{
    int num;
    clock_t start_time, end_time;
    int count = 0 , countb = 0, counth = 0, search = 0;

    printf("Введите добавляемое число: ");
    if (fscanf(stdin, "%d", &num) != 1)
    {
        printf(COLOR_YELLOW"Ошибка ввода.\n\n"COLOR_RESET);
        return;
    }

    search = search_num_in_file(f, num);
    while (search)
    {
        printf(COLOR_YELLOW"\nЧисло уже существует.\n"COLOR_RESET);
        printf("Введите другое число: ");
        if (fscanf(stdin, "%d", &num) != 1)
        {
            printf(COLOR_YELLOW"Ошибка ввода.\n\n"COLOR_RESET);
            return;
        }
        search = search_num_in_file(f, num);
    }


    printf("______________________________________________\n");
    printf("|  Структура  |   Время  | Сравнений | Память |\n");
    printf("|_____________________________________________|\n");

    node_t *cur = create_node(num, 1);

    // ДДП
    start_time = clock();
    head = insert(head, cur, &count);
    end_time = clock();

    printf("|     ДДП     |  %6ld  | %9d | %6ld |\n",
           end_time - start_time, count, sizeof(node_t) * table->size);

    // АВЛ
    node_t *curbal = create_node(num, 1);
    start_time = clock();
    headbal = insert_balance(headbal, curbal, &countb);
    end_time = clock();

    printf("|     АВЛ     |  %6ld  | %9d | %6ld |\n",
           end_time - start_time, countb, sizeof(node_t) * table->size);

    // хэш-таблица
    start_time = clock();
    load_table(table, num, &counth, LIMIT);
    end_time = clock();

    printf("| ХЭШ-ТАБЛИЦА |  %6ld  | %9d | %6ld |\n",
           end_time - start_time, counth, sizeof(cell_t) * table->size + sizeof(hash_t));

    // файл
    start_time = clock();
    int s = ftell(f);
    fprintf(f, "%d\n", num);
    end_time = clock();

    printf("|     ФАЙЛ    |  %6ld  | %9d | %6ld |\n",
           end_time - start_time, table->size, sizeof(char) * s);
    printf("|_____________________________________________|\n");
}

void time_restruct()
{
    clock_t start_time, end_time;


    char files[3][100] = {"time_restruct/restruct1.txt", "time_restruct/restruct2.txt", "time_restruct/restruct3.txt"};
    int limits[3] = { 10, 5, 2 };
    long int times[18];

    int count = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            int limit = 55;

            FILE *f = fopen(files[j], "r");
            hash_t *hash_table = NULL;
            free_table(hash_table);

            start_time = clock();
            read_to_table(f, &hash_table, limit);
            end_time = clock();

            times[count++] = end_time - start_time;

            rewind(f);
            limit = limits[i];
            free_table(hash_table);
            start_time = clock();
            read_to_table(f, &hash_table, limit);
            end_time = clock();

            times[count++] = end_time - start_time;
            free_table(hash_table);
        }
    printf(COLOR_BLUE"\n\nИсходный размер таблицы: 15\n\n"COLOR_RESET);
    printf("|________________________________________________________________________|\n");
    printf("|  Сравнений |   12 элементов    |   20 элементов    |   50 элементов    |\n");
    printf("|            | Нерестр |  Рестр  | Нерестр |  Рестр  | Нерестр |  Рестр  |\n");
    printf("|____________|_________|_________|_________|_________|_________|_________|\n");
    for (int i = 0; i < 18; i += 6)
    {
        printf("|      %2d    |  %4ld   |  %4ld   |  %4ld   |  %4ld   |  %4ld   |  %4ld   |\n", limits[i / 6], times[i], times[i+1], times[i+2],
               times[i+3], times[i+4], times[i+5]);
    }
    printf("|____________|_________|_________|_________|_________|_________|_________|\n");
}
