//
// Created by bartl on 06/11/2020.
//

#include <stdio.h>

#ifndef DATA_STRUCTURES_SINGLE_LINKED_LIST_H
#define DATA_STRUCTURES_SINGLE_LINKED_LIST_H

#endif //DATA_STRUCTURES_SINGLE_LINKED_LIST_H


typedef struct node {
    int data;
    struct node *next;
} node;



node *insert(int item, node *head);

void print(node *head);

void freeList(node *head);

void delete_by_content(void* item);

void delete_by_index(int index);

void delete_list(node* list);


