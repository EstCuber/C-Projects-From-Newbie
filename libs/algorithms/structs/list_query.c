#include <stdio.h>
#include <stdlib.h>
#include "list_query.h"


static list_node *_create_root_node(int data) {
    list_node *node = (list_node *)malloc(sizeof(list_node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

list_node *create_root_node(int data) {
    list_node *node = _create_root_node(data);
    if (node == NULL) {
        return NULL;
    }
    return node;
}

static list_node *_append_list_node(list_node *root, int data) {
    if (root->next != NULL) {
        return _append_list_node(root->next, data);
    }

    list_node *new_node = (list_node *)malloc(sizeof(list_node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->prev = root;
    new_node->next = NULL;
    root->next = new_node;

    return new_node;
}

list_node *append_list_node(list_node *root, int data) {
    if ((root == NULL) || (data == 0)) {
        return NULL;
    }
    list_node *new_node = _append_list_node(root, data);
    return new_node;
}

void delete_list_node(list_node **root, int data) {
    if (root == NULL || *root == NULL) return;

    list_node *current = *root;

    if (current->data == data) {
        *root = current->next;
        if (*root != NULL) {
            (*root)->prev = NULL;
        }

        free(current);
        return;
    }

    while (current != NULL && current->data != data) {
        current = current->next;
    }
    if (current == NULL) return;

    list_node *next_node = current->next;
    list_node *prev_node = current->prev;

    prev_node->next = next_node;
    if (next_node != NULL) {
        next_node->prev = prev_node;
    }

    free(current);

}

void print_list_node(const list_node *root) {
    while (root != NULL) {
        printf("%d ", root->data);
        root = root->next;
    }
    printf("\n");
}
