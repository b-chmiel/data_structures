#include <stdio.h>
#include <stdbool.h>
#include <methods_interface.h>

struct single_linked_list {
        struct node *root;
        struct methods_interface *interface;
};

struct node {
	void *data;
	struct node *next;
};

struct single_linked_list* init(struct methods_interface *interface);

void add(struct single_linked_list **list, void* data);

void add_many(struct single_linked_list **list, int number_of_args, ...);

void add_at(int index, void* data, struct single_linked_list **list);

void* get_at(int index, struct single_linked_list *list);

void split_into_two(struct node *head, struct node **first, struct node **second);

void merge_sorted(struct node **head,
             struct node *first,
             struct node *second,
             int(*comparator)(const void *, const void *));

void _merge_sort(struct node **head, int(*comparator)(const void *, const void *));

void merge_sort(struct single_linked_list **list);

bool delete_by_content(int item, struct node **head);

bool delete_by_index(int index, struct node **head);

void free_list(struct single_linked_list *list);

void print_list(struct node *head);
