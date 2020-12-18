//
// Created by bachm44 on 06/11/2020.
//

#include <malloc.h>
#include <limits.h>
#include <stdbool.h>
#include "single_linked_list.h"

void add_at(int position, int data, node_t **head)
{
        node_t *to_insert = malloc(sizeof(node_t) * 1);
        to_insert->data = data;
        to_insert->next = NULL;

        if (head == NULL) {
                *head = to_insert;
                return;
        }

        node_t *prev = NULL;
        node_t *curr = *head;
        int index = 0;

        while (position != index && curr != NULL) {
                prev = curr;
                curr = curr->next;
                index++;
        }

        if (index == 0) {
                *head = to_insert;
                to_insert->next = curr;
                return;
        }

        if (curr == NULL) {
                prev->next = to_insert;
                return;
        }

        prev->next = to_insert;
        to_insert->next = curr;
}

int get_at(int index, node_t *head)
{
        if (index < 0) {
                return INT_MIN;
        }

        node_t *temp = head;

        while(temp != NULL && index > 0) {
               temp = temp->next;
               index--;
        }

        if (temp == NULL) {
                return INT_MAX;
        }

        return temp->data;
}

bool delete_by_content(int data, node_t **head)
{
        node_t *prev = NULL;
        node_t *curr = *head;

        while (curr != NULL && curr->data != data) {
                prev = curr;
                curr = curr->next;
        }

        if (curr == NULL) {
                return false;
        }

        if (prev == NULL) {
                *head = curr->next;
                free(curr);
                return true;
        }

        if (curr->next == NULL) {
                prev->next = NULL;
                free(curr);
                return true;
        }

        prev->next = curr->next;
        free(curr);
        return true;
}

bool delete_by_index(int index, node_t **head)
{
        if (index < 0)
                return false;

        node_t *prev = NULL;
        node_t *curr = *head;

        while (curr != NULL && index > 0) {
                prev = curr;
                curr = curr->next;
                index--;
        }

        if (curr == NULL) {
                return false;
        }

        if (prev == NULL) {
                *head = curr->next;
                free(curr);
                return true;
        }

        prev->next = curr->next;
        free(curr);
        return true;
}

void delete_list(node_t **head)
{
        node_t *temp;
        while (*head != NULL) {
                temp = *head;
                *head = (*head)->next;
                free(temp);
        }
}

void print_list(node_t *head)
{
        node_t *temp = head;
        printf("List: ");
        while (temp != NULL) {
                printf("%d ", temp->data);
                temp = temp->next;
        }
        printf("\n");
}