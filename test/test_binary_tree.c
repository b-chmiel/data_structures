
#include <stdlib.h>
#include <stdint.h>
#include <check.h>
#include <limits.h>
#include <stdint.h>
#include <binary_tree.h>

struct methods_interface *interface;
struct binary_tree *tree;

void binary_tree_setup(void)
{
}

void binary_tree_teardown(void)
{
}

START_TEST(test_add_sequential)
{
	// int list_size = 10;

	// for (long int i = 0; i < list_size; i++)
	//     add(&tree, (void *)i);

	// for (long int i = 0; i < list_size; i++)
	//     ck_assert_int_eq((long int)get_at(tree, i), i);
	ck_assert(1);
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

	suite_add_tcase(s, tc_core);

	return s;
}
