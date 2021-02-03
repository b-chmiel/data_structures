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

	to_insert->data = data;
	to_insert->next = NULL;

	if ((*stack)->root == NULL) {
		(*stack)->root = to_insert;
		(*stack)->el_cnt = 1;
	} else {
		to_insert->next = (*stack)->root;
		(*stack)->root = to_insert;
		(*stack)->el_cnt++;
	}
}

void *stack_pop(struct stack **stack)
{
	struct stack_node *tmp = NULL;
	const int el_cnt = (*stack)->el_cnt;
	void (*free_el)(void *) = (*stack)->interface->free_element;
	void *result = NULL;

	if (free_el == NULL) {
		free_el = free;
	}

	if (el_cnt == 1) {
		result = (*stack)->root->data;
		free_el((*stack)->root);
		(*stack)->root = NULL;
		(*stack)->el_cnt = 0;
	} else if (el_cnt > 1) {
		result = (*stack)->root->data;
		tmp = (*stack)->root;
		(*stack)->root = (*stack)->root->next;
		free_el(tmp);
		(*stack)->el_cnt--;
	}
	return result;
}
void *stack_get(struct stack *stack)
{
	if (stack == NULL || stack->root == NULL) {
		return NULL;
	}

	return stack->root->data;
}
void stack_clear(struct stack **stack)
{
	if (*stack == NULL)
		return;

	struct stack_node *tmp;
	struct stack_node *head = (*stack)->root;
	void (*free_el)(void *) = (*stack)->interface->free_element;

	if (free_el == NULL) {
		free_el = free;
	}

	while (head != NULL) {
		tmp = head;
		head = head->next;
		free_el(tmp);
	}
	(*stack)->el_cnt = 0;
}

void stack_free(struct stack *stack)
{
	stack_clear(&stack);
	free(stack->interface);
	free(stack);
}