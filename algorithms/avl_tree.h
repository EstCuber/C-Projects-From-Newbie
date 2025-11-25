#ifndef C_PROJECTS_AVL_TREE_H
#define C_PROJECTS_AVL_TREE_H

typedef struct node_bn {
    struct node_bn *left_n;
    struct node_bn *right_n;
    long long int value;
    int height;
} node_bn;

void add_node (long long int value);

#endif