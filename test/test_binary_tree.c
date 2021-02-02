#include <stdlib.h>
#include <stdint.h>
#include <check.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include "binary_tree.h"

struct methods_interface *interface;
struct binary_tree *tree;

void binary_tree_setup(void)
{
	interface = malloc(sizeof(struct methods_interface));
	interface->compare = NULL;
	interface->free_element = free;
	tree = binary_tree_init(interface);
}

void binary_tree_teardown(void)
{
	binary_tree_free(tree);
}

START_TEST(test_add_sequential)
{
	int tree_size = 100;

	for (long int i = 0; i < tree_size; i++)
		binary_tree_add(&tree, (void *)i);

	// char *bfs_result = binary_tree_bfs(tree);

	// printf("%s", bfs_result);
	// for (long int i = 0; i < list_size; i++)
	// 	ck_assert_int_eq((long int)get_at(tree, i), i);
}
END_TEST

START_TEST(test_add_random)
{
	const long int to_add[] = { 10, 5, 30, 4, 8, 40, 1 };

	int tree_size = sizeof(to_add) / sizeof(to_add[0]);
	for (long int i = 0; i < tree_size; i++)
		binary_tree_add(&tree, (void *)to_add[i]);

	binary_tree_dfs_inorder(tree);

	// for (long int i = 0; i < list_size; i++)
	// 	ck_assert_int_eq((long int)get_at(tree, i), i);
}
END_TEST

Suite *binary_tree_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Binary tree");
	tc_core = tcase_create("binary_tree");

	tcase_add_checked_fixture(tc_core, binary_tree_setup,
				  binary_tree_teardown);
	tcase_add_test(tc_core, test_add_sequential);
	tcase_add_test(tc_core, test_add_random);

	suite_add_tcase(s, tc_core);

	return s;
}
