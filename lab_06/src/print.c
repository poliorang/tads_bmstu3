#include "print.h"
#include "list.h"
#include "hash.h"

void welcome_print()
{
    printf(COLOR_GREEN"\nМеню\n"COLOR_RESET);
    printf("%s",
    "1 - Загрузить данные из файла\n"
    "2 - Вывести деревья и хеш-таблицу\n"
    "3 - Добавить элемент\n"
    "4 - Сравнить эффективность СД\n"
    "5 - Эффективность реструктуризации\n"
    "0 - Выход\n\n"
    "Выберите пункт меню: ");

}

// заполнить дерево
int read_to_tree(FILE *f, node_t **head, node_t **head_bal, int *rc)
{
    node_t *cur = NULL;
    node_t *cur_bal = NULL;

    int count = 0, max = 0, num = 0;
    
    while (TRUE)
    {
        if (feof(f))
            break;

        fscanf(f, "%d", &num);
        count++;
        num > 0 ? (num) : (num *= -1);

        if (num > max)
            max = num;

        cur = create_node(num, 1);
        cur_bal = create_node(num, 1);

        *head = insert(*head, cur, rc);
        *head_bal = insert_balance(*head_bal, cur_bal, rc);
    }

    return count;
}

// заполнить таблицу
void read_to_table(FILE *f, hash_t **table, int limit)
{
    int u;
    hash_t *tab = create_table(SIZE);
    int num;
    while (!feof(f))
    {
        fscanf(f, "%d", &num);
        tab = load_table(tab, num, &u, limit);
    }
    *table = tab;
}

// создать файл c последовательностью чисел
int generate_file()
{
    int height_for_gen = 0;
    printf("\nВведите количество генерируемых чисел: ");
    if ((scanf("%d", &height_for_gen)) != 1)
    {
        printf("\nНеверное количество генерируемых чисел.\n");
        return EXIT_FAILURE;
    }
    char gen[50] = "python gen.py";
    char args[50];
    sprintf(args, " %d", height_for_gen);
    system(strcat(gen, args));

    return EXIT_SUCCESS;
}

// печать таблицы
void table_print(hash_t *hash_table)
{
    printf("_________________________________\n");
    printf("|   №   |   Хэш   |    Число     |\n");
    printf("|________________________________|\n");

    for (int i = 0; i < hash_table->max_size; i++)
        printf("| %3d   |   %3d   |   %8d   |\n",
                i, hash_function(hash_table->data[i].value, hash_table->max_size), hash_table->data[i].value);

    printf("|________________________________|\n");
    printf("\nКоличество коллизий: %d\n", hash_table->limit);
}

int check_tree(node_t *head, node_t *head_balance)
{
    if (head == NULL || head_balance == NULL)
    {
        printf(COLOR_YELLOW"\nДанные для построения дерева не были загружены.\nВыберите пункт 1.\n\n"COLOR_RESET);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
