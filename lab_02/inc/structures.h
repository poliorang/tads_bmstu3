#ifndef STRUCTURES_H
#define STRUCTURES_H

#define COUNT_RECORDS 500
#define MAX_LEN_NAME 50
#define RANGE_PRICE 2

#define OK 0

#define FILE_NAME "theatre.txt"

// структура, содержащая подробную информацию о музыкальном спектакле
typedef struct musical
{
    char composer[MAX_LEN_NAME];
    char country[MAX_LEN_NAME];
    int min_age;
    int duration;
} musical_r;

// структура, содержащая информацию о типе взрослого спектакля
typedef struct adult
{
    int is_comedy;
    int is_fairy_tale;
    int is_play;
} adult_r;

// структура, содержащая информацию о типе детского спектакля
typedef struct type_childlike
{
    int is_fairy_tale;
    int is_play;
} type_childlike_r;

// структура, содержащая подробную информацию о детском спектакле
typedef struct childlike
{
    int age;
    type_childlike_r type_childlike;
} childlike_r;

// объединение, содержащее подробную информацию о виде спектакля
typedef union type_perfomance
{
    childlike_r childlike;
    adult_r adult;
    musical_r musical;
} type_perfomance_r;

// структура, содержащая сведения о типе спектакля (детский, взрослый, музыкалный)
typedef struct choose_type
{
    int is_childlike; // детский
    int is_adult; // взрослый
    int is_musical; // музыкальный
} type_r;

// структура, содержащая все сведения о спектакле
typedef struct playbill
{
    char name_theatre[MAX_LEN_NAME]; // название театра
    char name_performance[MAX_LEN_NAME]; // название спектакля
    char surname_director[MAX_LEN_NAME]; // фамилия режиссера
    int price_range[RANGE_PRICE]; //  диапазон цен
    type_r choose_type;
    type_perfomance_r type_perfomance;
} playbill_r;

// ключи
typedef struct keys
{
    int key; // значение минимальной цены
    int ind; // индекс записи с соответствующим значением цены в основной таблице
} key_r;

// таблица
typedef struct table
{
    playbill_r playbill[COUNT_RECORDS];
    key_r key[COUNT_RECORDS]; //минимальная цена
    int size;
} table_r;

#endif
