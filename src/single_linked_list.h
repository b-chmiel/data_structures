//
// Created by bachm44 on 06/11/2020.
//

#include <stdio.h>

#ifndef DATA_STRUCTURES_SINGLE_LINKED_LIST_H
#define DATA_STRUCTURES_SINGLE_LINKED_LIST_H

#endif //DATA_STRUCTURES_SINGLE_LINKED_LIST_H


typedef struct node_t {
    int data;
    struct node_t *next;
} node_t;


void add_at(int position, int data, node_t **head);

int get_at(int index, node_t *head);

bool delete_by_content(int item, node_t **head);

bool delete_by_index(int index, node_t **head);

void delete_list(node_t **list);

void print_list(node_t *head);
