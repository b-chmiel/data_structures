#include <stdio.h>
#include <stdbool.h>
#include "methods_interface.h"

#ifndef SINGLE_LINKED_LIST_DEF
#define SINGLE_LINKED_LIST_DEF

struct single_linked_list {
	struct single_linked_list_node *root;
	struct methods_interface *interface;
};

struct single_linked_list_node {
	void *data;
	struct single_linked_list_node *next;
};

struct single_linked_list *
single_linked_list_init(struct methods_interface *interface);

void single_linked_list_add(struct single_linked_list **list, void *data);

void single_linked_list_add_many(struct single_linked_list **list,
				 int number_of_args, ...);

void single_linked_list_add_at(struct single_linked_list **list, int index,
			       void *data);

void *single_linked_list_get_at(struct single_linked_list *list, int index);

void single_linked_list_merge_sort(struct single_linked_list **list);

bool single_linked_list_delete_by_content(struct single_linked_list **list,
					  void *data);

bool single_linked_list_delete_by_index(struct single_linked_list **list,
					int index);

void single_linked_list_free(struct single_linked_list *list);

void single_linked_list_clear(struct single_linked_list **list);

void single_linked_list_print(struct single_linked_list_node *head);

#endif