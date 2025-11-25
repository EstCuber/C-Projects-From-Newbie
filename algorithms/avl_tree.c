#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl_tree.h"

node_bn *root = NULL;

static inline int get_max(int a, int b) {
    return ((a > b) ? a : b);
}

static inline int get_height_node(node_bn *n) {
    if (n == NULL) {
        return 0;
    }
    return n->height;
}

static inline int get_balance(
    node_bn *n
)
{
    return get_height_node(n->left_n) - get_height_node(n->right_n);
}

static node_bn* _create_node (
    long long int value
)
{
    node_bn *node = (node_bn*)malloc(sizeof(node_bn));
    node->value = value;
    node->left_n = NULL;
    node->right_n = NULL;
    node->height = 1;
    return node;
}


static void _update_height (
    node_bn *node
)
{
    if (node != NULL) {
        int h_left = get_height_node(node->left_n);
        int h_right = get_height_node(node->right_n);
        node->height = 1 + get_max(h_left, h_right);
    }
}

static node_bn* _rotate_left (
    node_bn *node
)
{
    node_bn *right_n = node->right_n;
    node_bn *left_n = right_n->left_n;

    right_n->left_n = node;
    node->right_n = left_n;

    _update_height(node);
    _update_height(right_n);

    return right_n;
}

static node_bn* _rotate_right(
    node_bn *node
)
{
    node_bn *left_n = node->left_n;
    node_bn *right_n = left_n->right_n;

    left_n->right_n = node;
    node->left_n = right_n;

    _update_height(node);
    _update_height(left_n);

    return left_n;
}

static node_bn* _insert(node_bn *node, long long int value)
{
    if (node == NULL)
    return _create_node(value);
    
    if (value == node->value)
    return node;

    if (value < node->value) {
        node->left_n = _insert(node->left_n, value);
    } else {
        node->right_n = _insert(node->right_n, value);
    }

    _update_height(node);
    int balance = get_balance(node);

    if (balance > 1 && value < node->left_n->value) {
        return _rotate_right(node);
    }
    if (balance < -1 && value > node->right_n->value) {
        return _rotate_left(node);
    }
    if (balance > 1 && value > node->left_n->value) {
        node->left_n = _rotate_left(node->left_n);
        return _rotate_right(node);
    }
    if (balance < -1 && value < node->right_n->value) {
        node->right_n = _rotate_right(node->right_n);
        return _rotate_left(node);
    }
    return node;
}



void add_node(long long int value) {
    root = _insert(root, value);
}