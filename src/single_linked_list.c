#include <malloc.h>
#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include "single_linked_list.h"
#include "comparators.h"

struct single_linked_list *
single_linked_list_init(struct methods_interface *interface)
{
	struct single_linked_list *result =
		malloc(sizeof(struct single_linked_list));
	result->interface = interface;
	result->root = NULL;

	return result;
}

void single_linked_list_add(struct single_linked_list **list, void *data)
{
	single_linked_list_add_at(list, -1, data);
}

void single_linked_list_add_many(struct single_linked_list **list,
				 int number_of_args, ...)
{
	if (number_of_args <= 0)
		return;

	va_list arg_pointer;
	va_start(arg_pointer, number_of_args);

	do {
		single_linked_list_add_at(list, -1,
					  va_arg(arg_pointer, void *));
		number_of_args--;
	} while (number_of_args > 0);

	va_end(arg_pointer);
}

void single_linked_list_add_at(struct single_linked_list **list, int index,
			       void *data)
{
	struct single_linked_list_node **head = &((*list)->root);
	struct single_linked_list_node *to_insert =
		malloc(sizeof(struct single_linked_list_node));
	to_insert->data = data;
	to_insert->next = NULL;

	if (*head == NULL) {
		*head = to_insert;
		return;
	}

	struct single_linked_list_node *prev = NULL;
	struct single_linked_list_node *curr = *head;
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

void *single_linked_list_get_at(struct single_linked_list *list, int index)
{
	if (index < 0)
		return NULL;

	struct single_linked_list_node *temp = list->root;

	while (temp != NULL && index > 0) {
		temp = temp->next;
		index--;
	}

	if (temp == NULL)
		return NULL;

	return temp->data;
}

static void split_into_two(struct single_linked_list_node *head,
			   struct single_linked_list_node **first,
			   struct single_linked_list_node **second)
{
	struct single_linked_list_node *slow = head;
	struct single_linked_list_node *fast = head;

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

static void merge_sorted(struct single_linked_list_node **head,
			 struct single_linked_list_node *first,
			 struct single_linked_list_node *second,
			 int (*comparator)(const void *, const void *))
{
	*head = malloc(sizeof(struct single_linked_list_node));
	(*head)->next = NULL;
	(*head)->data = NULL;
	struct single_linked_list_node *head_tail = *head;

	while (second != NULL || first != NULL) {
		if (first != NULL && second != NULL) {
			if (comparator(&(first->data), &(second->data)) >= 0) {
				head_tail->next = second;
				head_tail = head_tail->next;
				second = second->next;
			} else {
				head_tail->next = first;
				head_tail = head_tail->next;
				first = first->next;
			}
		} else if (first == NULL) {
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

	struct single_linked_list_node *tmp = *head;
	*head = tmp->next;
	free(tmp);
}

static void merge_sort_rec(struct single_linked_list_node **head,
			   int (*comparator)(const void *, const void *))
{
	if (*head == NULL || (*head)->next == NULL)
		return;

	struct single_linked_list_node *first = NULL;
	struct single_linked_list_node *second = NULL;

	split_into_two(*head, &first, &second);

	merge_sort_rec(&first, comparator);
	merge_sort_rec(&second, comparator);

	merge_sorted(head, first, second, comparator);
}

void single_linked_list_merge_sort(struct single_linked_list **list)
{
	struct single_linked_list_node **head = &((*list)->root);
	int (*comparator)(const void *, const void *) =
		(*list)->interface->compare;

	merge_sort_rec(head, comparator);
}

bool single_linked_list_delete_by_content(struct single_linked_list **list,
					  void *data)
{
	struct single_linked_list_node *prev = NULL;
	struct single_linked_list_node *curr = (*list)->root;
	int (*compare)(const void *, const void *) =
		(*list)->interface->compare;

	while (curr != NULL && compare(&(curr->data), &data) != 0) {
		prev = curr;
		curr = curr->next;
	}

	if (curr == NULL)
		return false;

	if (prev == NULL) {
		(*list)->root = curr->next;
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

bool single_linked_list_delete_by_index(struct single_linked_list **list,
					int index)
{
	if (index < 0)
		return false;

	struct single_linked_list_node *prev = NULL;
	struct single_linked_list_node *curr = (*list)->root;

	while (curr != NULL && index > 0) {
		prev = curr;
		curr = curr->next;
		index--;
	}

	if (curr == NULL) {
		return false;
	}

	if (prev == NULL) {
		(*list)->root = curr->next;
		free(curr);
		return true;
	}

	prev->next = curr->next;
	free(curr);
	return true;
}

void single_linked_list_free(struct single_linked_list *list)
{
	struct single_linked_list_node *temp;
	struct single_linked_list_node *head = list->root;
	if (list->interface->free_element != NULL) {
		while (head != NULL) {
			temp = head;
			head = head->next;
			list->interface->free_element((void *)temp);
		}
	} else {
		while (head != NULL) {
			temp = head;
			head = head->next;
			free(temp);
		}
	}
	free(list->interface);
	free(list);
}

void single_linked_list_clear(struct single_linked_list **list)
{
	while ((*list)->root != NULL)
		single_linked_list_delete_by_index(list, 0);
}

void single_linked_list_print(struct single_linked_list_node *head)
{
	struct single_linked_list_node *temp = head;
	while (temp != NULL) {
		printf("%ld ", (long int)temp->data);
		temp = temp->next;
	}
	printf("\n");
}