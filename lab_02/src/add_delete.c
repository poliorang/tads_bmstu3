#include "add_delete.h"

int input_yes_no(int *ans)
{
    char s[4];
    char *line;
    line = fgets(s, 4, stdin);
    if (line == NULL || s[0] == '\n')
    {
        printf("Incorrect input.\n");
        return NO_INPUT;
    }
    s[strlen(s) - 1] = '\0';
    if (strcmp(s, "y") && strcmp(s, "n"))
    {
        printf("You have to enter 'y' or 'n'.");
        return ENTER_ERR;
    }

    if (!strcmp(s, "y"))
        *ans = 1;
    if (!strcmp(s, "n"))
        *ans = 0;

    fflush(stdin);

    return OK;
}

int check_type(table_r *table, int ind)
{
    printf("\nIs this a children's show? Enter y/n: ");
    if (input_yes_no(&table->playbill[ind].choose_type.is_childlike))
        return ENTER_ERR;

    if (table->playbill[ind].choose_type.is_childlike)
    {
        table->playbill[ind].choose_type.is_adult = 0;
        table->playbill[ind].choose_type.is_musical = 0;
    }
    else
    {
        printf("\nIs this a adult's show? Enter y/n: ");
        if (input_yes_no(&table->playbill[ind].choose_type.is_adult))
            return ENTER_ERR;

        if (table->playbill[ind].choose_type.is_adult)
            table->playbill[ind].choose_type.is_musical = 0;
        else
        {
            printf("\nIs this a musical? Enter y/n: ");
            if (input_yes_no(&table->playbill[ind].choose_type.is_musical))
                return ENTER_ERR;
        }
    }

    return OK;
}

int check_type_adult(table_r *table, int ind)
{
    printf("\nIs this a FAIRY TALE? Enter y/n: ");
    if (input_yes_no(&table->playbill[ind].type_perfomance.adult.is_fairy_tale))
        return ENTER_ERR;

    if (table->playbill[ind].type_perfomance.adult.is_fairy_tale)
    {
        table->playbill[ind].type_perfomance.adult.is_play = 0;
        table->playbill[ind].type_perfomance.adult.is_comedy = 0;
    }
    else
    {
        printf("\nIs this a comedy? Enter y/n: ");
        if (input_yes_no(&table->playbill[ind].type_perfomance.adult.is_comedy))
            return ENTER_ERR;

        if (table->playbill[ind].type_perfomance.adult.is_comedy)
            table->playbill[ind].type_perfomance.adult.is_play = 0;
        else
        {
            printf("\nIs this a PLAY? Enter y/n: ");
            if (input_yes_no(&table->playbill[ind].type_perfomance.adult.is_play))
                return ENTER_ERR;
        }
    }

    return OK;
}

int add_entry(table_r *table)
{
    //printf("%d + 1 >= %d\n", table->size, COUNT_RECORDS);
    if (table->size <= 0 || table->size + 1 >= COUNT_RECORDS) {
        printf("Table is empty\n");
        return EMPTY_TABLE_ERR;
    }

    int ind = table->size;
    table->size += 1;

    printf("\nEnter the name of THEATRE (without spaces, no more than 15 characters): ");
    if (input_str(table->playbill[ind].name_theatre))
        return ENTER_ERR;

    printf("\nEnter the name of PERFOMANCE (without spaces, no more than 15 characters): ");
    if (input_str(table->playbill[ind].name_performance))
        return ENTER_ERR;

    printf("\nEnter the surname of DIRECTOR (without spaces, no more than 15 characters): ");
    if (input_str(table->playbill[ind].surname_director))
        return ENTER_ERR;

    printf("\nEnter the minimum price: ");
    if (input_num(&table->playbill[ind].price_range[0]))
        return ENTER_ERR;

    printf("\nEnter the maximum price: ");
    if (input_num(&table->playbill[ind].price_range[1]))
        return ENTER_ERR;

    if (table->playbill[ind].price_range[0] > table->playbill[ind].price_range[1])
    {
        printf("Minimum price must be less than maximum.\n");
        return ENTER_ERR;
    }

    table->key[ind].key = table->playbill[ind].price_range[0];

    if (check_type(table, ind))
        return ENTER_ERR;

    if (check_three_condition(table->playbill[ind].choose_type.is_adult,
                              table->playbill[ind].choose_type.is_childlike,
                              table->playbill[ind].choose_type.is_musical))
    {
        printf("Choose only one type of perfomance.\n");
        return ENTER_ERR;
    }

    if (table->playbill[ind].choose_type.is_childlike)
    {
        printf("\nEnter the minimum AGE: ");
        if (input_num(&table->playbill[ind].type_perfomance.childlike.age))
            return ENTER_ERR;
        if (table->playbill[ind].type_perfomance.childlike.age > 18)
        {
            printf("You have to enter the number less than 18.\n");
            return AGE_ERR;
        }

        printf("\nIs this a FAIRY TALE? Enter y/n: ");
        if (input_yes_no(&table->playbill[ind].type_perfomance.childlike.type_childlike.is_fairy_tale))
            return ENTER_ERR;

        if (table->playbill[ind].type_perfomance.childlike.type_childlike.is_fairy_tale)
            table->playbill[ind].type_perfomance.childlike.type_childlike.is_play = 0;
        else
        {
            printf("\nIs this a PLAY? Enter y/n: ");
            if (input_yes_no(&table->playbill[ind].type_perfomance.childlike.type_childlike.is_play))
                return ENTER_ERR;
        }

        if (table->playbill[ind].type_perfomance.childlike.type_childlike.is_play == table->playbill[ind].type_perfomance.childlike.type_childlike.is_fairy_tale) {
            printf("Choose only one type of perfomance.\n");
            return ENTER_ERR;
        }
    }

    if (table->playbill[ind].choose_type.is_adult)
    {
        if (check_type_adult(table, ind))
            return ENTER_ERR;

        if (check_three_condition(table->playbill[ind].type_perfomance.adult.is_comedy,
                              table->playbill[ind].type_perfomance.adult.is_play,
                              table->playbill[ind].type_perfomance.adult.is_fairy_tale))
        {
            printf("Choose only one type of perfomance.\n");
            return ENTER_ERR;
        }
    }

    if (table->playbill[ind].choose_type.is_musical)
    {
        printf("\nEnter the surname of COMPOSER (without spaces, no more than 15 characters): ");
        if (input_str(table->playbill[ind].type_perfomance.musical.composer))
            return ENTER_ERR;

        printf("\nEnter the surname of COUNTRY (without spaces, no more than 15 characters): ");
        if (input_str(table->playbill[ind].type_perfomance.musical.country))
            return ENTER_ERR;

        printf("\nEnter the minimum AGE: ");
        if (input_num(&table->playbill[ind].type_perfomance.musical.min_age))
            return ENTER_ERR;
        if (table->playbill[ind].type_perfomance.musical.min_age > 18)
            return AGE_ERR;

        printf("\nEnter the DURATION: ");
        if (input_num(&table->playbill[ind].type_perfomance.musical.duration))
            return ENTER_ERR;
        if (table->playbill[ind].type_perfomance.musical.min_age > 500)
            return DUR_ERR;
    }

    return OK;
}

int delete_entry(table_r *table)
{
    if (table->size <= 0 || table->size + 1 > COUNT_RECORDS)
    {
        printf("Table is empty\n");
        return EMPTY_TABLE_ERR;
    }

    char perf[50];

    printf("\nEnter name of PERFOMANCE (these performances will be deleted): ");
    if (input_str(perf))
        return ENTER_ERR;

    int flag = 0;
    for (int i = 0; i < table->size; i++)
    {
        if (!strcmp(table->playbill[i].name_performance, perf))
        {
            flag = 1;
            strcpy(table->playbill[i].name_performance, "///////");
        }
    }

    if (flag)
        printf("\nFields have been deleted.\n");
    else
        printf("\nFields not found.\n");
    return OK;
}
