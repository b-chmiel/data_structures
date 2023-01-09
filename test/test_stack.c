#include <check.h>
#include "stdlib.h"
#include "stack.h"
#include "comparators.h"

struct stack *stack;
struct methods_interface *interface;

void stack_setup(void)
{
	interface = malloc(sizeof(struct methods_interface));
	interface->compare = compare_int;
	interface->compare_keys = NULL;
	interface->free_element = free;
	interface->free_key = NULL;
	stack = stack_init(interface, sizeof(long int));
}

void stack_teardown(void)
{
	stack_free(stack);
}

START_TEST(test_add)
{
	const int el_cnt = 100;
	for (long int i = 0; i < el_cnt; i++) {
		stack_push(&stack, (void *)i);
	}

	ck_assert_int_eq((long int)stack_get(stack), el_cnt - 1);
	ck_assert_int_eq(stack->el_cnt, el_cnt);

	for (long int i = el_cnt - 1; i >= 0; i--) {
		ck_assert_int_eq((long int)stack_pop(&stack), i);
	}
	ck_assert(stack_get(stack) == NULL);
	ck_assert(stack_pop(&stack) == NULL);
	ck_assert_int_eq(stack->el_cnt, 0);
}
END_TEST

Suite *stack_suite(void)
{
	Suite *s;
	TCase *tc_core;
	s = suite_create("Stack");
	tc_core = tcase_create("stack");
	tcase_add_checked_fixture(tc_core, stack_setup, stack_teardown);
	tcase_add_test(tc_core, test_add);

	suite_add_tcase(s, tc_core);
	return s;
}