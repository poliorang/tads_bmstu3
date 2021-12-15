#include "process.h"
#include "print.h"

int main()
{
    int r, c, d;

    list head, head1;
    head.data = -1;
    head1.data = -1;
    int empty = 0, flag = 0;


    int *a, *ia;
    int *av, *iav;
    int *a1, *ia1, *ja1;

    int command = -1;
    while (command != 0)
    {
        clock_t start, end;

        welcome_print();
        if (scanf("%d", &command) != 1)
            break;

        if (command == 1)
        {
            flag = 0;
            printf("\nCount of rows: ");
            if (scanf("%d", &r) != 1 || r < 1)
            {
                printf("Incorrect data.\n");
                return EXIT_FAILURE;
            }

            printf("Count of columns: ");
            if (scanf("%d", &c) != 1 || c < 1)
            {
                printf("Incorrect data.\n");
                return EXIT_FAILURE;
            }

            printf("Enter the per-cent of zeroes for matrix [0, 100%%): ");
            if (scanf("%d", &d) != 1 || d < 0 || d >= 100)
            {
                printf("Incorrect data.\n");
                return EXIT_FAILURE;
            }

            a = calloc(r * c, sizeof(int));
            ia = calloc(r * c, sizeof(int));

            av = calloc(r, sizeof(int));
            iav = calloc(r, sizeof(int));

            a1 = calloc(r * c, sizeof(int));
            ia1 = calloc(r * c, sizeof(int));
            ja1 = calloc(r * c, sizeof(int));
            create_list(c, &head);
            create_list(r, &head1);
            create_mat(r, c, d, a, ia, &head, flag);
            printf("Enter the per-cent of zeroes for vector [0, 100%%): ");
            if (scanf("%d", &d) != 1 || d < 0 || d >= 100)
            {
                printf("Incorrect data.\n");
                return EXIT_FAILURE;
            }
            create_vec(r, d, av, iav, &head1, flag);

            empty = 1;
        }

        if (command == 2)
        {
            printf("\nCount of rows: ");
            if (scanf("%d", &r) != 1 || r < 1)
            {
                printf("\nIncorrect data.\n");
                return 1;
            }

            printf("Count of columns: ");
            if (scanf("%d", &c) != 1 || c < 1)
            {
                printf("\nIncorrect data.\n");
                return 1;
            }


            if (input_obj(r, c))
            {
                printf("\nInput error.\n");
                return EXIT_FAILURE;
            }


            flag = 1;


            a = calloc(r * c, sizeof(int));
            ia = calloc(r * c, sizeof(int));
            create_list(c, &head);
            create_mat(r, c, 0, a, ia, &head, flag);
            av = calloc(c, sizeof(int));
            iav = calloc(c, sizeof(int));
            create_list(r, &head1);
            create_vec(r, 0, av, iav, &head1, flag);
            empty = 1;

        }

        if (command == 3)
        {
            printf("\n 1 - Classical representation\n"
                   " 2 - Special representation\n"
                   "Enter type of representation: ");
            int type;
            while (scanf("%d", &type) != 1)
                printf("You must enter 1 or 2.\n");

            if (type == 2)
            {
                if (!empty)
                {
                    printf("Empty matrix or vector.\n");
                    continue;
                }

                printf("\n");

                int i = -1;
                int counter = 0;
                printf(" A: ");
                while (a[++i])
                {
                    printf("%d ", a[i]);
                    counter++;
                }

                printf("\n");
                printf("IA: ");
                i = -1;
                while (++i < counter)
                    printf("%d ", ia[i]);
                print_list(c, &head);
                printf("\n");
            }

            if (type == 1)
            {
                if (!empty)
                {
                    printf("Empty matrix or vector.\n");
                    continue;
                }

                FILE *f = fopen("matrix.txt", "r");
                if (f == NULL)
                    return 1;

                int elem;
                printf("\n");
                for (int i = 0; i < r; ++i)
                {
                    for (int j = 0; j < c; ++j)
                    {
                        fscanf(f, "%d", &elem);
                        printf("%d ", elem);
                    }
                    printf("\n");
                }
                fclose(f);
            }
        }

        if (command == 4)
        {
            printf("\n 1 - Classical representation\n"
                   " 2 - Special representation\n"
                   "Enter type of representation: ");
            int type;
            while (scanf("%d", &type) != 1)
                printf("You must enter 1 or 2.\n");

            if (type == 2)
            {
                if (!empty)
                {
                    printf("Empty matrix or vector.\n");
                    continue;
                }

                int counter = 0;
                printf("\n");
                int i = -1;
                printf(" A: ");
                while (av[++i])
                {
                    printf("%d ", av[i]);
                    counter++;
                }

                printf("\n");
                printf("IA: ");
                i = -1;
                while (++i < counter)
                    printf("%d ", iav[i]);
                print_list(r, &head1);
                printf("\n");
            }

            if (type == 1)
            {
                if (!empty)
                {
                    printf("Empty matrix or vector.\n");
                    continue;
                }

                FILE *fv = fopen("vector.txt", "r");
                if (fv == NULL)
                    return 1;

                int elem;
                printf("\n");
                for (int i = 0; i < r; ++i)
                {
                    fscanf(fv, "%d", &elem);
                    printf("%d ", elem);
                }
                printf("\n");
                fclose(fv);
            }
        }


        if (command == 5)
        {
            if (!empty)
            {
                printf("Empty matrix or vector.\n");
                continue;
            }

            int *res = classic_mult(r, c, &start, &end);
            printf("\n");
            int i = -1;
            printf("Answer: ");
            while (++i < c)
                printf("%d ", res[i]);

            print_aij(res, c);
            printf(COLOR_YELLOW "%s" COLOR_RESET,
                   "\n\nTime: ");
            printf("%6ld T", end - start);
            printf(COLOR_YELLOW "%s" COLOR_RESET,
                   "\nMemory: ");
            printf("%6ld B\n", (r * sizeof(int)));
            free(res);
        }

        if (command == 6)
        {
            if (!empty)
            {
                printf("Empty matrix or vector.\n");
                continue;
            }

            int *res = vect_mult(r, c, &start, &end);
            printf("\n");
            int i = -1;
            printf("Answer: ");
            int mem = 0;
            while (++i < c) {
                if (res[i])
                    mem++;
                printf("%d ", res[i]);
            }

            print_aij(res, c);
            printf(COLOR_YELLOW "%s" COLOR_RESET,
                   "\n\nTime: ");
            printf("%6ld T", end - start);
            printf(COLOR_YELLOW "%s" COLOR_RESET,
                   "\nMemory: ");
            printf("%6ld B\n", (mem * sizeof(int)));
            free(res);
        }
    }

    free(a);
    free(ia);
    free(a1);
    free(ia1);
    free(ja1);
    free(av);
    free(iav);
    free_list(r, &head);
    free_list(r, &head1);
    return 0;
}
