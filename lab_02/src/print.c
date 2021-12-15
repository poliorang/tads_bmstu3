#include "print.h"

void welcome_print()
{
    printf(COLOR_GREEN "%s" COLOR_RESET,
            "\nChoose the command: \n");

    printf("%s",
           " 1 -  Load the table from the file.\n"
           " 2 -  Display the table on screen.\n"
           " 3 -  Display all musical special age less the spec. duration.\n"
           " 4 -  Add an entry to the end of the table.\n"
           " 5 -  Delete an entry from the table for the name of performance.\n"
           " 6 -  Sort (with choosing type and parameter) and display the table.\n"
           " 7 -  Display a table by the sorted key table.\n"
           " 8 -  Compare the time of sorting the table and sorting by keys\n"
           "      and the time of normal sorting and sorting the key table.\n"
           " 9 -  Clean table.\n"
           " 10 - Program exit.\n"
           " 11 - Display keys table.\n");
}

void print_hat()
{
    printf("\n%15s %25s %15s %15s %15s %15s %35s \n\n",
           "Theatre", "Perfomance", "Director", "Price", "Type", "Genre", "Other info.(for musical)");
}

int print_table(table_r *table)
{
    if (table->size <= 0 || table->size > MAX_TABLE_SIZE)
    {
        printf("Table is empty\n");
        return EMPTY_TABLE_ERR;
    }

    print_hat();
    for (int i = 0; i < table->size; i++)
    {
        if (strcmp(table->playbill[i].name_performance, "///////"))
        {
            printf("%15s %25s %15s", table->playbill[i].name_theatre,
                   table->playbill[i].name_performance, table->playbill[i].surname_director);
            printf("%13d-%d", table->playbill[i].price_range[0], table->playbill[i].price_range[1]);

            if (table->playbill[i].choose_type.is_childlike) {
                printf("%15s", "for childlike");

                if (table->playbill[i].type_perfomance.childlike.type_childlike.is_fairy_tale)
                    printf("%15s", "Fairy tale");
                if (table->playbill[i].type_perfomance.childlike.type_childlike.is_play)
                    printf("%15s", "Play");
                printf("      %d+", table->playbill[i].type_perfomance.childlike.age);
            }

            if (table->playbill[i].choose_type.is_adult) {
                printf("%15s", "for adult");
                if (table->playbill[i].type_perfomance.adult.is_play)
                    printf("%15s", "Play");
                if (table->playbill[i].type_perfomance.adult.is_fairy_tale)
                    printf("%15s", "Fairy tale");
                if (table->playbill[i].type_perfomance.adult.is_comedy)
                    printf("%15s", "Comedy");
            }

            if (table->playbill[i].choose_type.is_musical) {
                printf("%15s %15s", "musical", "");
                /*printf("     Composer - %s; ", table->playbill[i].type_perfomance.musical.composer);
                printf("Country - %s; ", table->playbill[i].type_perfomance.musical.country);
                printf("Min age - %d; ", table->playbill[i].type_perfomance.musical.min_age);
                printf("Duration - %d;", table->playbill[i].type_perfomance.musical.duration);*/
                printf("     %s, ", table->playbill[i].type_perfomance.musical.composer);
                printf("%s, ", table->playbill[i].type_perfomance.musical.country);
                printf("%d+, ", table->playbill[i].type_perfomance.musical.min_age);
                printf("%d min", table->playbill[i].type_perfomance.musical.duration);
            }
            printf("\n");
        }
    }

    return OK;
}

int print_select(table_r *table)
{
    int age, dur;

    printf("Enter minimum AGE: ");
    if (input_num(&age))
    {
        printf("Incorrect age.\n");
        return AGE_ERR;
    }

    printf("Enter (<1000) DURATION: ");
    if (input_num(&dur) || dur > 1000)
    {
        printf("Incorrect duration.\n");
        return DUR_ERR;
    }

    //if (input_age_and_dur(&age, &dur))
    //    return INPUT_AGE_DUR_ERR;

    if (table->size <= 0 || table->size > MAX_TABLE_SIZE)
    {
        printf("Table is empty\n");
        return EMPTY_TABLE_ERR;
    }
    int flag = 0;
    for (int i = 0; i < table->size; i++)
    {
        if (strcmp(table->playbill[i].name_performance, "///////"))
        {
            if (table->playbill[i].choose_type.is_musical && table->playbill[i].type_perfomance.musical.min_age == age
                && table->playbill[i].type_perfomance.musical.duration < dur)
            {
                if (!flag)
                    print_hat();
                flag = 1;
                printf("%15s %25s %15s", table->playbill[i].name_theatre,
                       table->playbill[i].name_performance, table->playbill[i].surname_director);
                printf("%13d-%d", table->playbill[i].price_range[0], table->playbill[i].price_range[1]);
                printf("%15s %15s", "musical", "");

                printf("     %s, ", table->playbill[i].type_perfomance.musical.composer);
                printf("%s, ", table->playbill[i].type_perfomance.musical.country);
                printf("%d+, ", table->playbill[i].type_perfomance.musical.min_age);
                printf("%d min\n", table->playbill[i].type_perfomance.musical.duration);
            }
        }
    }
    if (!flag)
        printf("Field not found.\n");
    return OK;
}

int print_by_keys(table_r *table)
{
    if (table->size <= 0 || table->size > MAX_TABLE_SIZE)
    {
        printf("Table is empty\n");
        return EMPTY_TABLE_ERR;
    }

    print_hat();

    for (int j = 0; j < table->size; j++)
    {
        int i = table->key[j].ind;
        if (strcmp(table->playbill[i].name_performance, "///////")) {
            printf("%15s %25s %15s", table->playbill[i].name_theatre,
                   table->playbill[i].name_performance, table->playbill[i].surname_director);
            printf("%13d-%d", table->playbill[i].price_range[0], table->playbill[i].price_range[1]);

            if (table->playbill[i].choose_type.is_childlike) {
                printf("%15s", "for childlike");

                if (table->playbill[i].type_perfomance.childlike.type_childlike.is_fairy_tale)
                    printf("%15s", "Fairy tale");
                if (table->playbill[i].type_perfomance.childlike.type_childlike.is_play)
                    printf("%15s", "Play");
                printf("      %d+", table->playbill[i].type_perfomance.childlike.age);
            }

            if (table->playbill[i].choose_type.is_adult) {
                printf("%15s", "for adult");
                if (table->playbill[i].type_perfomance.adult.is_play)
                    printf("%15s", "Play");
                if (table->playbill[i].type_perfomance.adult.is_fairy_tale)
                    printf("%15s", "Fairy tale");
                if (table->playbill[i].type_perfomance.adult.is_comedy)
                    printf("%15s", "Comedy");
            }

            if (table->playbill[i].choose_type.is_musical) {
                printf("%15s %15s", "musical", "");
                printf("     %s, ", table->playbill[i].type_perfomance.musical.composer);
                printf("%s, ", table->playbill[i].type_perfomance.musical.country);
                printf("%d+, ", table->playbill[i].type_perfomance.musical.min_age);
                printf("%d min", table->playbill[i].type_perfomance.musical.duration);
            }
            printf("\n");
        }
    }

    return OK;
}


void print_res_comp(table_r *table, double time, int type_sort, int type_table)
{
    if (!type_table)
        printf("%8s %11d %18f\n", (type_sort) ? "bubble" : "qsort",
               (int)sizeof(table->key[0]) * table->size, time);
    else
        printf("%8s %11d %18f\n", (type_sort) ? "bubble" : "qsort",
               (int)sizeof(table->playbill[0]) * table->size, time);
}

void print_sort_hat(int type)
{
    printf("\n");
    if (type) {
        printf(COLOR_BLUE"%s\n"COLOR_RESET, "SORTING TABLE:");
        printf("%8s %17s %10s\n", "Type", "Memory (bytes)", "Time");
        printf(" --------------------------------------------\n");
    } else
    {
        printf(COLOR_BLUE"%s\n"COLOR_RESET, "SORTING BY KEYS:");
        printf("%8s %17s %10s\n", "Type", "Memory (bytes)", "Time");
        printf(" --------------------------------------------\n");
    }

}

void print_keys(table_r *table)
{
    printf("\n%15s %15s %15s\n\n", "Pos. key", "Value", "Pos. in table");
    for (int i = 0; i < table->size; i++)
        printf("%15d %15d %15d\n", i + 1, table->key[i].key, table->key[i].ind + 1);
}
