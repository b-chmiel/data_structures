#include <malloc.h>
#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include "single_linked_list.h"

struct single_linked_list* init(struct methods_interface* interface)
{
        struct single_linked_list* result = malloc(sizeof(struct single_linked_list));
        result->interface = interface;
        result->root = NULL;

        return result;
}

void add(struct node **head, void* data)
{
        add_at(-1, data, (void* )head);
}

void add_many(struct node **head, int number_of_args, ...)
{
        if (number_of_args <= 0)
                return;

        va_list arg_pointer;
        va_start(arg_pointer, number_of_args);

        do {
                add_at(-1, va_arg(arg_pointer, void*), head);
                number_of_args--;
        } while (number_of_args > 0);

        va_end(arg_pointer);
}

void add_at(int index, void* data, struct node **head)
{
        struct node *to_insert = malloc(sizeof(struct node));
        to_insert->data = data;
        to_insert->next = NULL;

        if (head == NULL) {
                *head = to_insert;
                return;
        }

        struct node *prev = NULL;
        struct node *curr = *head;
        int position = 0;

        while (position != index && curr != NULL) {
                prev = curr;
                curr = curr->next;
                position++;
        }

        if (position == 0) {
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

void* get_at(int index, struct node *head)
{
        if (index < 0) {
                return NULL;
        }

        struct node *temp = head;

        while (temp != NULL && index > 0) {
                temp = temp->next;
                index--;
        }

        if (temp == NULL) {
                return NULL;
        }

        return temp->data;
}

void split_into_two(struct node *head, struct node **first, struct node **second)
{
        struct node *slow = head;
        struct node *fast = head;

        while (fast != NULL) {
                fast = fast->next;
                if (fast != NULL)
                        fast = fast->next;
                if (fast != NULL)
                        slow = slow->next;
        }

        *second = slow->next;
        slow->next = NULL;
        *first = head;
}

void
merge_sorted(struct node **head, struct node *first, struct node *second, int(*comparator)(const void *, const void *))
{
        *head = malloc(sizeof(struct node));
        (*head)->next = NULL;
        (*head)->data = NULL;
        struct node *head_tail = *head;

        while (second != NULL || first != NULL) {
                if (first != NULL && second != NULL) {
                        if (first->data >= second->data) {
                                head_tail->next = second;
                                head_tail = head_tail->next;
                                second = second->next;
                        } else {
                                head_tail->next = first;
                                head_tail = head_tail->next;
                                first = first->next;
                        }
                } else if(first == NULL) {
                        head_tail->next = second;
                        head_tail = head_tail->next;
                        second = second->next;
                } else {
                        head_tail->next = first;
                        head_tail = head_tail->next;
                        first = first->next;
                }
                head_tail->next = NULL;
        }
        delete_by_index(0, head);
}

void merge_sort(struct node **head, int(*comparator)(const void *, const void *))
{
        if (*head == NULL || (*head)->next == NULL)
                return;

        struct node *first = NULL;
        struct node *second = NULL;

        split_into_two(*head, &first, &second);

        merge_sort(&first, comparator);
        merge_sort(&second, comparator);

        merge_sorted(head, first, second, comparator);
}

bool delete_by_content(int data, struct node **head)
{
        struct node *prev = NULL;
        struct node *curr = *head;

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

bool delete_by_index(int index, struct node **head)
{
        if (index < 0)
                return false;

        struct node *prev = NULL;
        struct node *curr = *head;

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

void delete_list(struct node **head)
{
        struct node *temp;
        while (*head != NULL) {
                temp = *head;
                *head = (*head)->next;
                free(temp);
        }
}

void print_list(struct node *head)
{
        struct node *temp = head;
        printf("List: ");
        while (temp != NULL) {
                printf("%d ", temp->data);
                temp = temp->next;
        }
        printf("\n");
}