#include "read.h"

int input_command(int *command)
{
    printf("\nEnter the number of command: ");
    char num[4];
    char *n;
    n = fgets(num, 4, stdin);
    if (n == NULL || num[0] == '\n')
        return NO_INPUT;
    num[strlen(num) - 1] = '\0';

    int a = atoi(num);
    if (!a)
        *command = -1;
    else
        *command = a;

    if (*command < LEFT_LIMIT || *command > RIGHT_LIMIT || (command == NULL))
    {
        //clean_();
        printf("Incorrect number of command.\n");
        return INCORRECT_INPUT;
    }

    return OK;
}

int input_str(char *string)
{
    fflush(stdin);
    //char inp[50];
    char *line;
    line = fgets(string, 20, stdin);
    if (line == NULL || string[0] == '\n' || strlen(line) > 16)
    {
        fflush(stdin);
        printf("Incorrect input.\n");
        return NO_INPUT;
    }
    string[strlen(string) - 1] = '\0';

    return OK;
}

int input_num(int *number)
{
    char num[11];
    char *n;
    n = fgets(num, 11, stdin);
    if (n == NULL || num[0] == '\n')
    {
        printf("Incorrect input.\n");
        return NO_INPUT;
    }
    num[strlen(num) - 1] = '\0';
    *number = atoi(num);

    if (*number < 0)
    {
        printf("You have to enter the non-negative integer number.\n");
        return NO_INPUT;
    }

    return OK;
}

int check_three_condition(int a, int b, int c)
{
    if ((a && b && c) || (!a && !b && !c))
        return CONDITION_ERR;
    if ((a && b && !c) || (a && !b && c) || (!a && b && c))
        return CONDITION_ERR;

    return OK;
}

int read_field_child(FILE *f, table_r *table, int i)
{
    int age;
    int fairy, play;

    if (fscanf(f, "%d", &age) != 1)
    {
        printf("Invalid age.\n");
        return INCORRECT_FIELD_CHILD;
    }

    if (fscanf(f, "%d%d", &fairy, &play) != 2)
    {
        printf("Invalid type.\n");
        return INCORRECT_FIELD_CHILD;
    }

    if ((fairy && play) || (!fairy && !play))
        return INCORRECT_FIELD_CHILD;

    table->playbill[i].type_perfomance.childlike.age = age;
    table->playbill[i].type_perfomance.childlike.type_childlike.is_fairy_tale = fairy;
    table->playbill[i].type_perfomance.childlike.type_childlike.is_play = play;

    return OK;
}

int read_field_adult(FILE *f, table_r *table, int i)
{
    int comedy, fairy, play;

    if (fscanf(f, "%d%d%d", &comedy, &fairy, &play) != 3)
    {
        printf("Invalid type.\n");
        return INCORRECT_FIELD_ADULT;
    }

    if (check_three_condition(comedy, fairy, play))
    {
        printf("Ambiguous choice.\n");
        return INCORRECT_FIELD_ADULT;
    }

    table->playbill[i].type_perfomance.adult.is_comedy = comedy;
    table->playbill[i].type_perfomance.adult.is_fairy_tale = fairy;
    table->playbill[i].type_perfomance.adult.is_play = play;

    return OK;
}

int read_field_mus(FILE *f, table_r *table, int i)
{
    char composer[MAX_LEN_NAME], country[MAX_LEN_NAME];
    int min_age, duration;

    if (fscanf(f, "%s%s", composer, country) != 2 || strlen(composer) > 16 || strlen(country) > 16)
    {
        printf("Invalid composer/country.\n");
        return INCORRECT_FIELD_MUS;
    }

    if (fscanf(f, "%d%d", &min_age, &duration) != 2)
    {
        printf("Invalid minimum age/duratation.b\n");
        return INCORRECT_FIELD_MUS;
    }

    strcpy(table->playbill[i].type_perfomance.musical.composer, composer);
    strcpy(table->playbill[i].type_perfomance.musical.country, country);
    table->playbill[i].type_perfomance.musical.min_age = min_age;
    table->playbill[i].type_perfomance.musical.duration = duration;

    return OK;
}

int read_field(FILE *f, table_r *table, int i)
{
    char theatre[MAX_LEN_NAME], performance[MAX_LEN_NAME], surname_director[MAX_LEN_NAME];
    int min_price, max_price;

    int child, adult, mus;

    if (fscanf(f, "%s", theatre) != 1 || strlen(theatre) > 16)
    {
        printf("Invalid theatre\n");
        return INCORRECT_FIELD_PLAYBILL;
    }

    if (fscanf(f, "%s", performance) != 1 || strlen(performance) > 26)
    {
        printf("Invalid performance\n");
        return INCORRECT_FIELD_PLAYBILL;
    }

    if (fscanf(f, "%s", surname_director) != 1 || strlen(surname_director) > 16)
    {
        printf("Invalid director surname\n");
        return INCORRECT_FIELD_PLAYBILL;
    }

    for (size_t j = 0; j < strlen(surname_director); j++)
    {
        if (!isalpha(surname_director[j]))
            return INCORRECT_FIELD_PLAYBILL;
    }

    if (fscanf(f, "%d", &min_price) != 1)
    {
        printf("Invalid min price\n");
        return INCORRECT_FIELD_PLAYBILL;
    }


    if (fscanf(f, "%d", &max_price) != 1)
    {
        printf("Invalid max price\n");
        return INCORRECT_FIELD_PLAYBILL;
    }

    table->key[i].key = min_price;
    table->key[i].ind = i;

    if (fscanf(f, "%d%d%d", &child, &adult, &mus) != 3)
    {
        printf("Invalid type\n");
        return INCORRECT_FIELD_PLAYBILL;
    }

    if (check_three_condition(child, adult, mus))
    {
        printf("Ambiguous choice\n");
        return INCORRECT_FIELD_PLAYBILL;
    }

    strcpy(table->playbill[i].name_theatre, theatre);
    strcpy(table->playbill[i].name_performance, performance);
    strcpy(table->playbill[i].surname_director, surname_director);
    table->playbill[i].price_range[0] = min_price;
    table->playbill[i].price_range[1] = max_price;
    table->playbill[i].choose_type.is_childlike = child;
    table->playbill[i].choose_type.is_adult = adult;
    table->playbill[i].choose_type.is_musical = mus;

    if (child && !adult && !mus)
    {
        if (read_field_child(f, table, i))
            return INCORRECT_FIELD_CHILD;
    }

    if (!child && adult && !mus)
    {
        if (read_field_adult(f, table, i))
            return INCORRECT_FIELD_ADULT;
    }

    if (!child && !adult && mus)
    {
        if (read_field_mus(f, table, i))
            return INCORRECT_FIELD_MUS;
    }

    return OK;
}

