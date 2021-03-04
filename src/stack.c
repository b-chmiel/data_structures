#include <stdlib.h>
#include "stack.h"

struct stack *stack_init(struct methods_interface *interface, size_t size)
{
	struct stack *result = malloc(sizeof(struct stack));
	result->el_cnt = 0;
	result->interface = interface;
	result->root = NULL;
	result->size = size;

	return result;
}

void stack_push(struct stack **stack, void *data)
{
	struct stack_node *to_insert = malloc(sizeof(struct stack_node));
	struct stack_node **root = &(*stack)->root;
	int *el_cnt = &(*stack)->el_cnt;

	to_insert->data = data;
	to_insert->next = NULL;

	if (*root == NULL) {
		*root = to_insert;
		*el_cnt = 1;
	} else {
		to_insert->next = *root;
		*root = to_insert;
		(*el_cnt)++;
	}
}

void *stack_pop(struct stack **stack)
{
	struct stack_node *tmp = NULL;
	struct stack_node **root = &(*stack)->root;
	void (*free_el)(void *) = (*stack)->interface->free_element;
	void *result = NULL;
	void **root_data = &(*stack)->root->data;
	int *el_cnt = &(*stack)->el_cnt;

	if (free_el == NULL)
		free_el = free;

	if (*el_cnt == 1) {
		result = *root_data;
		free_el(*root);
		*root = NULL;
		*el_cnt = 0;
	} else if (*el_cnt > 1) {
		result = *root_data;
		tmp = *root;
		(*stack)->root = (*stack)->root->next;
		free_el(tmp);
		(*el_cnt)--;
	} else {
		return NULL;
	}

	return result;
}
void *stack_get(struct stack *stack)
{
	if (stack == NULL || stack->root == NULL)
		return NULL;

	return stack->root->data;
}
void stack_clear(struct stack **stack)
{
	if (*stack == NULL)
		return;

	int *el_cnt = &(*stack)->el_cnt;
	struct stack_node *tmp;
	struct stack_node *head = (*stack)->root;
	void (*free_el)(void *) = (*stack)->interface->free_element;

	if (free_el == NULL)
		free_el = free;

	while (head != NULL) {
		tmp = head;
		head = head->next;
		free_el(tmp);
	}
	*el_cnt = 0;
}

void stack_free(struct stack *stack)
{
	stack_clear(&stack);
	free(stack->interface);
	free(stack);
}