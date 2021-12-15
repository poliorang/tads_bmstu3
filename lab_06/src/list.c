#include "list.h"

// соззать узел дерева
node_t *create_node(int data, int height)
{
    node_t *node = malloc(sizeof (node_t));
    if (node)
    {
        node->data = data;
        node->height = height;
        node->right = NULL;
        node->left = NULL;
    }
    else
        node = NULL;

    return node;    
}

// вставить узел в несбалансированное дерево
node_t *insert(node_t *head, node_t *node, int *rc)
{
    (*rc)++;
    if (head == NULL)
        return node;
    else
    {
        if (node->data < head->data)
            head->left = insert(head->left, node, rc);
        else if (node->data > head->data)
            head->right = insert(head->right, node, rc);
        else if (node->data == head->data)
        {
            free(node);
            return head;
        }
    }

    return head;    
}

// вставить узел в сбалансированное дерево
node_t *insert_balance(node_t *head, node_t *node, int *rc)
{
    (*rc)++;
    if (head == NULL)
        return node;

    if (node->data < head->data)
        head->left = insert_balance(head->left, node, rc);
    else if (node->data > head->data)
        head->right = insert_balance(head->right, node, rc);
    else if (node->data == head->data)
        return head;

    return balance_node(head);
}

// определить длину в узле
int what_height(node_t *head)
{
    return head ? head->height : 0;
}

// записать длину в узле
void new_height(node_t *head)
{
    int hl = what_height(head->left);
    int hr = what_height(head->right);
    head->height = ((hl > hr) ? hl : hr) + 1;
}

// разница между длинами в ветвях
int factorlr(node_t *head)
{
    return what_height(head->right) - what_height(head->left);
}

// повернуть направо
node_t *turn_right(node_t *head)
{
    node_t *buf = head->left;
    head->left = buf->right;
    buf->right = head;
    new_height(head);
    new_height(buf);

    return buf;
}

// повернуть налево
node_t *turn_left(node_t *head)
{
    node_t *buf = head->right;
    head->right = buf->left;
    buf->left = head;

    new_height(head);
    new_height(buf);

    return buf;
}

//  балансировка
node_t *balance_node(node_t *head)
{
    new_height(head);
    if (factorlr(head) == 2)
    {
        if (factorlr(head->right) < 0)
            head->right = turn_right(head->right);
        return turn_left(head);
    }
    if (factorlr(head) == -2)
    {
        if (factorlr(head->left) > 0)
            head->left = turn_left(head->left);
        return turn_right(head);
    }

    return head;
}

// освободить узел дерева
void free_tree_node(node_t *head)
{
    if (head)
        free(head);

    head = NULL;
}

// освободить дерево
void free_tree(node_t *head)
{
    if (head)
        apply_po(head, free_tree_node, NULL);
}

void apply_pre(node_t *head, void (*f)(node_t *, void *), void *arg)
{
    if (head == NULL)
        return;
    
    f(head, arg);
    apply_pre(head->right, f, arg);
    apply_pre(head->left, f, arg);
}

void apply_po(node_t *head, void (*f)(node_t *), void *arg)
{
    if (head == NULL)
        return;
    
    apply_po(head->right, f, arg);
    apply_po(head->left, f, arg);
    f(head);
}

// найти число в файле
int search_num_in_file(FILE *f, int num)
{
    int count = 0, flag = 0, num_file = 0;
    for (; fscanf(f, "%d", &num_file) > 0; count++)
        if (num == num_file)
        {
            flag = 1;
            break;
        }

    if (flag == 1)
        return count;
    else
        return 0;
}

