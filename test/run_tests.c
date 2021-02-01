#include "test_data_structures.h"
#include <stdlib.h>
#include <check.h>

int main(void)
{
	int number_failed;
	SRunner *sr;

	sr = srunner_create(single_linked_list_suite());
	srunner_add_suite(sr, binary_tree_suite());
	srunner_set_fork_status(sr, CK_NOFORK);
	srunner_run_all(sr, CK_VERBOSE);

	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}