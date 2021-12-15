#include "process.h"

//выделение динамической памяти под список
void create_list(int n, list *head)
{
    list *cur = head;
    for (int i = 0; i < n; ++i)
    {
        cur->next = malloc(sizeof(list));
        cur->next->data = -1;
        cur = cur->next;
    }
}

//записать данные в определенный элемент списка
void write_list(list *head, int ind, int data)
{
    list *cur = head;
    for (int i = 0; i < ind; ++i)
        cur = cur->next;
    cur->data = data;
}

//считать данные из определенного элемента списка
int read_list(list *head, int ind)
{
    list cur = *head;
    for (int i = 0; i < ind; ++i)
        cur = *cur.next;
    return cur.data;
}

//освободить динамическую память из под списка
void free_list(int n, list *head)
{
    list *cur;
    list *next = head->next;
    for (int i = 0; i < n - 1; ++i)
    {
        cur = next;
        next = cur->next;
        free(cur);
    }
}

//напечатать n элементов спика на экран
void print_list(int n, list *head)
{
    list cur = *head;
    printf("\nJA: ");
    for (int i = 0; i < n; ++i)
    {
        if (cur.data == -1)
            printf("%s", "- ");
        else
            printf("%d ", cur.data);
        cur = *cur.next;
    }
}

//ручной ввод разреженной матрицы и вектора
int input_obj(int r, int c)
{
    int *matr = calloc(r * c, sizeof(int));
    int *vector = calloc(r, sizeof(int));

    int count, x, y;
    printf("\nNumber of non-zero elems for matrix (0; %d]: ", r*c);
    if(scanf("%d", &count) != 1 || count < 1 || count > r*c)
        return EXIT_FAILURE;

    for (int i = 0; i < count; ++i)
    {
        printf("\nElement %d of %d. ", i + 1, count);
        printf("\nEnter row: ");
        if (scanf("%d", &y) != 1 || y < 0 || y >= r)
            return EXIT_FAILURE;

        printf("Enter column: ");
        if (scanf("%d", &x) != 1 || x < 0 || x >= c)
            return EXIT_FAILURE;

        printf("Enter element: ");
        if (scanf("%d", &matr[y*c + x]) != 1)
            return EXIT_FAILURE;
    }

    printf("\nNumber of non-zero elems for vector (0; %d]: ", r);
    if (scanf("%d", &count) != 1 || count < 1 || count > r)
        return 1;

    for (int i = 0; i < count; ++i)
    {
        printf("\nElement %d of %d.\n", i + 1, count);

        printf("\nEnter column: ");
        if (scanf("%d", &x) != 1 || x < 0 || x >= r)
            return 1;

        printf("Enter element: ");
        if (scanf("%d", &vector[x]) != 1)
            return 1;
    }

    FILE *mat = fopen("matrix.txt", "w");
    FILE *vec = fopen("vector.txt", "w");

    if (mat == NULL || vec == NULL)
        return EXIT_FAILURE;

    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
            fprintf(mat, "%d ", matr[i*c + j]);

        fprintf(mat, "\n");
    }

    for (int i = 0; i < r; ++i)
        fprintf(vec, "%d ", vector[i]);

    free(matr);
    free(vector);
    fclose(mat);
    fclose(vec);

    return 0;
}

//печать вектора в разреженном виде
void print_aij(int res[], int n)
{
    int a_i = 0, ia_i = 0;

    int *a = malloc(n * sizeof(int));
    int *ia = malloc(n * sizeof(int));

    list head;
    head.data = -1;
    create_list(n, &head);

    int c = 0;
    for (int i = 0; i < n; ++i)
    {
        if (res[i])
        {
            a[a_i++] = res[i];
            ia[ia_i++] = 0;
            if (read_list(&head, i) == -1)
                write_list(&head, i, a_i - 1);
            c++;
        }
    }
    printf("\n\n A: ");
    for(int i = 0; i < c; ++i)
        printf("%d ", a[i]);

    printf("\nIA: ");
    for(int i = 0; i < c; ++i)
        printf("%d ", ia[i]);
    print_list(n, &head);

    free(a);
    free(ia);
    free_list(n, &head);
}

// создать матрицу
void create_mat(int c, int r, int d, int a[], int ia[], list *head, int flag)
{
    if (!flag)
    {
        char command[50] = "python gen.py";
        char args[50];
        sprintf(args, " %d %d %d", c, r, d);
        system(strcat(command, args));
    }

    FILE *f = fopen("matrix.txt", "r");
    if (f == NULL)
        return;

    int elem, ia_i = 0, a_i = 0;

    for (int i = 0; i < c; ++i)
        for (int j = 0; j < r; ++j)
        {
            fscanf(f, "%d", &elem);
            if (elem)
            {
                a[a_i++] = elem;
                ia[ia_i++] = i;
                if (read_list(head, j) == -1)
                    write_list(head, j, a_i - 1);
            }
        }

    fclose(f);
}

// создать вектор
void create_vec(int r, int d, int a[], int ia[], list *head, int flag)
{
    if (!flag)
    {
        char command[50] = "python gen_v.py";
        char args[50];
        sprintf(args, " %d %d", r, d);
        system(strcat(command, args));
    }

    FILE *f = fopen("vector.txt", "r");
    if (f == NULL)
        return;

    int elem, ia_i = 0,  a_i = 0;

    for (int j = 0; j < r; ++j)
    {
        fscanf(f, "%d", &elem);
        if (elem)
        {
            a[a_i++] = elem;
            ia[ia_i++] = 0;
            if (read_list(head, j) == -1)
                write_list(head, j, a_i - 1);
        }
    }
    fclose(f);
}

//классическое умножение
int* classic_mult(int c, int r, clock_t *start, clock_t *end)
{
    FILE *mat = fopen("matrix.txt", "r");
    FILE *vec = fopen("vector.txt", "r");

    if (mat == NULL || vec == NULL)
        return NULL;

    int *matr = malloc(r * c * sizeof(int));
    int *vector = malloc(c * sizeof(int));
    int *res = malloc(r * sizeof(int));

    for (int i = 0; i < c; ++i)
        for (int j = 0; j < r; ++j)
            fscanf(mat, "%d", &matr[i * r + j]);

    for (int i = 0; i < c; ++i)
        fscanf(vec, "%d", &vector[i]);

    int sum = 0, res_i = 0;

    *start = clock();
    for (int j = 0; j < r; ++j)
    {
        for (int i = 0; i < c; ++i)
            sum += matr[i * r + j] * vector[i];
        res[res_i++] = sum;
        sum = 0;
    }
    *end = clock();

    free(matr);
    free(vector);

    fclose(mat);
    fclose(vec);

    return res;
}

//умножение по заданию
int* vect_mult(int c, int r, clock_t *start, clock_t *end)
{
    FILE *mat = fopen("matrix.txt", "r");
    FILE *vec = fopen("vector.txt", "r");

    if (mat == NULL || vec == NULL)
        return NULL;

    int *a = calloc(r * c, sizeof(int));
    int *ia = calloc(r * c, sizeof(int));
    int *ja = calloc(r * c, sizeof(int));

    int a_i = 0, ia_i = 0, ja_i = 0;

    int *matr = malloc(r * c * sizeof(int));
    int *vector = malloc(c * sizeof(int));
    int *res = malloc(r * sizeof(int));

    for (int i = 0; i < c; ++i)
        for (int j = 0; j < r; ++j)
            fscanf(mat, "%d", &matr[i * r + j]);

    for (int i = 0; i < c; ++i)
        fscanf(vec, "%d", &vector[i]);

    //получение в разреженном виде
    for (int j = 0; j < r; ++j)
        for (int i = 0; i < c; ++i)
            if (matr[i * r + j])
            {
                a[a_i++] = matr[i * r + j];
                ia[ia_i++] = i;
                ja[ja_i++] = j;
            }

    int i = 0, sum = 0, row = 0, res_i = 0;

    *start = clock();
    while (a[i] || res_i < r)
    {
        if (row != ja[i])
        {
            res[res_i++] = sum;
            sum = 0;
            row++;
            continue;
        }
        sum += a[i] * vector[ia[i]];
        ++i;
    }
    *end = clock();

    free(a);
    free(ia);
    free(ja);

    free(matr);
    free(vector);

    fclose(mat);
    fclose(vec);

    return res;
}
