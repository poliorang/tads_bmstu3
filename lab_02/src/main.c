#include "print.h"
#include "choose.h"
#include "read.h"
#include "form_table.h"

#include "structures.h"

int main()
{
    table_r table;
    int command = -1;
    while (command)
    {
        welcome_print();
        if (input_command(&command))
            continue;

        else
        {
            if (choose(command, &table))
                command = -1;
        }
    }

    return EXIT_SUCCESS;
}
