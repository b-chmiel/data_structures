#ifndef STACK_DEF
#define STACK_DEF

#include <stddef.h>
#include "methods_interface.h"

struct stack {
	struct stack_node *root;
	struct methods_interface *interface;
	size_t size;
	int el_cnt;
};

struct stack_node {
	void *data;
	struct stack_node *next;
};

struct stack *stack_init(struct methods_interface *interface, size_t size);

void stack_push(struct stack **stack, void *data);

void *stack_pop(struct stack **stack);

void *stack_get(struct stack *stack);

void stack_clear(struct stack **stack);

void stack_free(struct stack *stack);

#endif