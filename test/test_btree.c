#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include "btree.h"
#include "comparators.h"

struct methods_interface *interface;
struct btree *tree;

void btree_setup(void)
{
	interface = malloc(sizeof(struct methods_interface));
	interface->compare = compare_int;
	interface->compare_keys = compare_int;
	interface->free_element = free;
	interface->free_key = free;
	tree = btree_init(interface);
}

void btree_teardown(void)
{
	free(interface);
}

START_TEST(test_add)
{
	btree_add(&tree, (void *)1, (void *)100);
	printf("%ld\n", (long int)(tree->root->data_nodes[0])->data);
}
END_TEST

Suite *btree_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Btree");
	tc_core = tcase_create("btree");

	tcase_add_checked_fixture(tc_core, btree_setup, btree_teardown);
	tcase_add_test(tc_core, test_add);

	suite_add_tcase(s, tc_core);

	return s;
}