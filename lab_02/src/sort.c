#include "sort.h"

int compare_key(const void *a, const void *b)
{
    return ((key_r *)(a))->key - ((key_r *)(b))->key;
}

int compare_table(const void *a, const void *b)
{
    return ((playbill_r *)(a))->price_range[0] - ((playbill_r*)(b))->price_range[0];
}

int perform_sorting(table_r *table, int bub, int key, int tab)
{
    if (bub)
        if (key)
        {
            printf("\n It is bubble by key: \n");
            bubble_sort(table, !key);
            if (print_by_keys(table))
                return ENTER_ERR;
        }
        else
        {
            printf("\n It is bubble sort table: \n");
            bubble_sort(table, tab);
            print_table(table);
        }
    else
        if (key)
        {
            printf("\n It is qsort by key: \n");
            qsort(&table->key[0], table->size, sizeof(table->key[0]), compare_key);
            print_by_keys(table);
        }
        else
        {
            printf("\n It is qsort table: \n");
            qsort(&table->playbill[0], table->size,
                  sizeof(table->playbill[0]), compare_table);
            print_table(table);
        }

    return OK;
}

int choose_sort_and_param(table_r *table)
{
    int key, tab, bub, qs;

    printf("\nEnter the parameter of sorting.");
    printf("\nSort by KEYS? Enter y/n: ");
    if (input_yes_no(&key))
        return ENTER_ERR;

    if (!key)
    {
        printf("\nSort TABLE? Enter y/n: ");
        if (input_yes_no(&tab))
            return ENTER_ERR;
        if ((key && tab) || (!key && !tab))
        {
            printf("You need choose only one type of sorting.\n");
            return ENTER_ERR;
        }
    }


    printf("\nEnter the type of sorting.");
    printf("\nBubble sort? Enter y/n: ");
    if (input_yes_no(&bub))
        return ENTER_ERR;

    if (!bub)
    {
        printf("\nqsort? Enter y/n: ");
        if (input_yes_no(&qs))
            return ENTER_ERR;
        if ((bub && qs) || (!bub && !qs))
        {
            printf("You need choose only one type of sorting.\n");
            return ENTER_ERR;
        }
    }

    if (perform_sorting(table, bub, key, tab))
        return SORT_ERR;

    return OK;
}

void bubble_sort(table_r *table, int tabl_or_key)
{
    if (tabl_or_key) //по таблице
    {
        for (int i = 0; i < table->size; i++)
            for (int j = 0; j < table->size - 1; j++)
            {
                if (table->playbill[j].price_range[0] > table->playbill[j + 1].price_range[0])
                {
                    playbill_r buf = table->playbill[j];
                    table->playbill[j] = table->playbill[j + 1];
                    table->playbill[j + 1] = buf;
                }
            }
    }
    else
    {
        for (int i = 0; i < table->size; i++)
            for (int j = 0; j < table->size - 1; j++)
            {
                if (table->key[j].key > table->key[j + 1].key)
                {
                    key_r buf = table->key[j];
                    table->key[j] = table->key[j + 1];
                    table->key[j + 1] = buf;
                }
            }
    }
}

void sort_qsort_vs_bub(table_r *table)
{
    print_sort_hat(1);

    clean_table(table);
    download_from_file(table);

    clock_t time_start1 = clock();
    qsort(&table->playbill[0], table->size, sizeof(table->playbill[0]), compare_table);
    clock_t qs_tab = clock() - time_start1;
    print_res_comp(table, (double)(qs_tab) / CLOCKS_PER_SEC, 0, 1);

    clean_table(table);
    download_from_file(table);

    clock_t time_start2 = clock();
    bubble_sort(table, 1);
    clock_t bub_tab = clock() - time_start2;
    print_res_comp(table, (double)(bub_tab) / CLOCKS_PER_SEC, 1, 1);

    print_sort_hat(0);

    clean_table(table);
    download_from_file(table);

    clock_t time_start3 = clock();
    qsort(&table->key[0].key, table->size, sizeof(table->key[0].key), compare_key);
    clock_t qs_key = clock() - time_start3;
    print_res_comp(table, (double)(qs_key) / CLOCKS_PER_SEC, 0, 0);

    clean_table(table);
    download_from_file(table);

    clock_t time_start4 = clock();
    bubble_sort(table, 0);
    clock_t bub_key = clock() - time_start4;
    print_res_comp(table, (double)(bub_key) / CLOCKS_PER_SEC, 1, 0);
}
