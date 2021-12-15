#include "choose.h"

int choose(int command, table_r *table)
{
    switch (command)
    {
        case 1:
            printf(COLOR_YELLOW"%s"COLOR_RESET, " - 1 - Entering data from a file\n");
            if (download_from_file(table))
            {
                clean_table(table);
                printf("Error in writting in the file.\n");
                return CASE_ONE_ERR;
            }

            printf("Data is loaded into the table.\n");
            break;

        case 2:
            printf(COLOR_YELLOW"%s"COLOR_RESET, " - 2 - Output the table\n");
            if (print_table(table))
                return EMPTY_TABLE_ERR;
            break;


        case 3:
            printf(COLOR_YELLOW"%s"COLOR_RESET, " - 3 - Display all musical spec. age less the spec. duration\n");
            if (print_select(table))
                return SELECT_ERR;
            break;

        case 4:
            printf(COLOR_YELLOW"%s"COLOR_RESET, " - 4 - Adding an entry to the end of the file\n");
            if (add_entry(table))
            {
                clean_field(table, table->size);
                return ENTER_ERR;
            }
            printf("\nData is loaded into the table\n");
            break;

        case 5:
            printf(COLOR_YELLOW"%s"COLOR_RESET, " - 5 - Deleting an entry from a file by the specified field\n");
            if (delete_entry(table))
                return ENTER_ERR;
            break;

        case 6:
            printf(COLOR_YELLOW"%s"COLOR_RESET, " - 6 - Sorting table\n");
            if (choose_sort_and_param(table))
                return ENTER_ERR;
            break;

        case 7:
            printf(COLOR_YELLOW"%s"COLOR_RESET, " - 7 - Display a table by sorted keys\n");
            if (perform_sorting(table, 0, 1, 0))
                return SORT_ERR;
            break;

        case 8:
            printf(COLOR_YELLOW"%s"COLOR_RESET, " - 8 - Comparison of sorts\n");
            sort_qsort_vs_bub(table);
            break;


        case 9:
            printf(COLOR_YELLOW"%s"COLOR_RESET, " - 9 - Clean table\n");
            clean_table(table);
            printf("Table is cleared\n");
            break;

        case 10:
            exit(EXIT_SUCCESS);

        case 11:
            printf(COLOR_YELLOW"%s"COLOR_RESET, " - 11 - Keys table\n");
            print_keys(table);
            break;
    }
    return OK;
}
