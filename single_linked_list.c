//
// Created by bartl on 06/11/2020.
//

#include <malloc.h>
#include "single_linked_list.h"

node *insert(int item, node *head)
{
        node *to_insert = malloc(sizeof(node) * 1);

        if (to_insert == NULL) return NULL;

        to_insert->data = item;
        to_insert->next = NULL;

        if (head == NULL) {
                head = to_insert;
        } else if (head->next == NULL) {
                head->next = to_insert;
        } else {
                node *tmp = head;
                while (tmp->next != NULL) {
                        tmp = tmp->next;
                }
                tmp->next = to_insert;
        }
        return head;
}

void print(node *head)
{
        node *tmp = head;

        while (tmp != NULL) {
                printf("%d ", tmp->data);
                tmp = tmp->next;
        }
        printf("\n");
}

void freeList(node *head)
{
        node *tmp;
        while (head != NULL) {
                tmp = head;
                printf("clear for %d\n", tmp->data);
                head = head->next;
                free(tmp);
                tmp = NULL;
        }
        print(head);
        head = NULL;
}

void delete_by_content(void *item)
{}

void delete_by_index(int index)
{}

void delete_list(node *head)
{}
