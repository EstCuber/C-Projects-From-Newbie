//
// Created by ivanefremov on 24.11.2025.
//

#ifndef C_PROJECTS_LIST_QUERY_H
#define C_PROJECTS_LIST_QUERY_H

typedef struct list_node {
    int data;
    struct list_node *next;
    struct list_node *prev;
} list_node;

list_node *create_root_node(int data);
list_node *append_list_node(list_node *root, int data);
void delete_list_node(list_node **root, int data);
void print_list_node(const list_node *root);

#endif //C_PROJECTS_LIST_QUERY_H