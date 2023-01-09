#include <stdlib.h>
#include <stdint.h>
#include <check.h>
#include <limits.h>
#include <stdint.h>
#include "binary_tree.h"
#include "single_linked_list.h"

struct methods_interface *interface;
struct binary_tree *tree;
struct single_linked_list *result;

void binary_tree_setup(void)
{
	interface = malloc(sizeof(struct methods_interface));
	interface->compare = NULL;
	interface->free_element = free;
	tree = binary_tree_init(interface, sizeof(long int));
	result = single_linked_list_init(interface);
}

void binary_tree_teardown(void)
{
	binary_tree_free(tree);
	free(result);
}

/*
	1
	 \
	  2
	   \
	    3
		 \
		  ...
		   \
		   99
*/
START_TEST(test_add_sequential)
{
	const int tree_size = 100;

	for (long int i = 0; i < tree_size; i++)
		binary_tree_add(&tree, (void *)i);

	binary_tree_dfs_inorder(tree, &result);

	for (long int i = 0; i < tree_size; i++) {
		ck_assert_int_eq(i, (long int)single_linked_list_get_at(result,
									0));
		single_linked_list_delete_by_index(&result, 0);
	}
}
END_TEST

/*

	  10
	 /  \
	 5   30
	/ \   \
   4   8  40
  /
 1

*/
START_TEST(test_add_random)
{
	const long int to_add[] = { 10, 5, 30, 4, 8, 40, 1 };
	const long int expected[] = { 10, 5, 4, 1, 8, 30, 40 };
	const int tree_size = sizeof(to_add) / sizeof(to_add[0]);

	for (long int i = 0; i < tree_size; i++)
		binary_tree_add(&tree, (void *)to_add[i]);

	binary_tree_dfs_inorder(tree, &result);

	for (long int i = 0; i < tree_size; i++) {
		ck_assert_int_eq(expected[i],
				 (long int)single_linked_list_get_at(result,
								     0));
		single_linked_list_delete_by_index(&result, 0);
	}
}
END_TEST

/*

	  10
	 /  \
	 5   30
	/ \   \
   4   8  40
  /
 1

*/
START_TEST(test_dfs_preorder)
{
	const long int to_add[] = { 10, 5, 30, 4, 8, 40, 1 };
	const long int expected[] = { 1, 4, 5, 8, 10, 30, 40 };
	const int tree_size = sizeof(to_add) / sizeof(to_add[0]);

	for (long int i = 0; i < tree_size; i++)
		binary_tree_add(&tree, (void *)to_add[i]);

	binary_tree_dfs_preorder(tree, &result);

	for (long int i = 0; i < tree_size; i++) {
		ck_assert_int_eq(expected[i],
				 (long int)single_linked_list_get_at(result,
								     0));
		single_linked_list_delete_by_index(&result, 0);
	}
}
END_TEST

/*

	  10
	 /  \
	 5   30
	/ \   \
   4   8  40
  /
 1

*/
START_TEST(test_dfs_postorder)
{
	const long int to_add[] = { 10, 5, 30, 4, 8, 40, 1 };
	const long int expected[] = { 1, 4, 8, 5, 40, 30, 10 };
	const int tree_size = sizeof(to_add) / sizeof(to_add[0]);

	for (long int i = 0; i < tree_size; i++)
		binary_tree_add(&tree, (void *)to_add[i]);

	binary_tree_dfs_postorder(tree, &result);

	for (long int i = 0; i < tree_size; i++) {
		ck_assert_int_eq(expected[i],
				 (long int)single_linked_list_get_at(result,
								     0));
		single_linked_list_delete_by_index(&result, 0);
	}
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
	tcase_add_test(tc_core, test_dfs_preorder);
	tcase_add_test(tc_core, test_dfs_postorder);

	suite_add_tcase(s, tc_core);

	return s;
}
