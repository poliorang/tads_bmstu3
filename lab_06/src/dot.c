#include "dot.h"

void export_to_dot(FILE *f, node_t *head)
{
    fprintf(f, "digraph %s {\n", "my_graph");
    apply_pre(head, to_dot, f);
    fprintf(f, "}\n");
}

void to_dot(node_t *head, void *p)
{
    FILE *f = p;

    if (head->left)
        fprintf(f, "%d -> %d;\n", head->data, head->left->data);

    if (head->right)
        fprintf(f, "%d -> %d;\n", head->data, head->right->data);
}

void get_dot_file(node_t *head, node_t *head_balance)
{
    FILE *f;
    f = fopen("data/Tree.gv", "w");
    export_to_dot(f, head);
    fclose(f);

    f = fopen("data/Balance_tree.gv", "w");
    export_to_dot(f, head_balance);
    fclose(f);
}
