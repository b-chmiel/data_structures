#include <stdlib.h>
#include <stdint.h>
#include <check.h>
#include <limits.h>
#include <stdint.h>
#include <single_linked_list.h>

struct methods_interface *interface;
struct single_linked_list *list;

void single_linked_list_setup(void)
{
	interface = malloc(sizeof(struct methods_interface));
	interface->compare = NULL;
	interface->free_element = free;
	list = init(interface);
}

void single_linked_list_teardown(void)
{
	free_list(list);
}

START_TEST(test_add)
{
	int list_size = 50;

	for (long int i = 1; i < list_size + 1; i++)
		add(&list, (void *)i);

	for (long int i = 0; i < list_size - 1; i++)
		ck_assert_int_eq((long int)get_at(list, i), i + 1);
}
END_TEST

START_TEST(test_add_many)
{
	int list_size = 5;

	add_many(&list, list_size, 0, 1, 2, 3, 4);

	for (int i = 0; i < list_size; i++)
		ck_assert_int_eq((long int)get_at(list, i), i);
}
END_TEST

START_TEST(test_sequential_add_at)
{
	int list_size = 7;
	long int items[] = { 1, 3, 2, 4, 5, 22, -23 };

	for (int i = 0; i < list_size; i++)
		add_at(&list, i, (void *)items[i]);

	for (int i = 0; i < list_size; i++)
		ck_assert_int_eq((long int)get_at(list, i), items[i]);
}
END_TEST

START_TEST(test_random_add)
{
	int list_size = 7;

	add_at(&list, 0, (void *)1);
	add_at(&list, 5, (void *)2);
	add_at(&list, 3, (void *)3);
	add_at(&list, 6, (void *)4);
	add_at(&list, 2, (void *)5);
	add_at(&list, 2, (void *)6);
	add_at(&list, 1, (void *)7);

	int result[] = { 1, 7, 2, 6, 5, 3, 4 };
	for (int i = 0; i < list_size; i++)
		ck_assert_int_eq((long int)get_at(list, i), result[i]);
}
END_TEST

START_TEST(test_merge_sort_1)
{
	const long int to_sort[] = { 50, 24, 27, 70, 10, 68, 67, 94, 76,
				     85, 57, 66, 5,  41, 28, 47, 58, 49,
				     2,	 16, 98, 45, 8,	 48, 25, 26, 13 };

	for (unsigned long i = 0; i < sizeof(to_sort) / sizeof(to_sort[0]); i++)
		add(&list, (void *)to_sort[i]);

	merge_sort(&list);
	const long int result[] = { 2,	5,  8,	10, 13, 16, 24, 25, 26,
				    27, 28, 41, 45, 47, 48, 49, 50, 57,
				    58, 66, 67, 68, 70, 76, 85, 94, 98 };

	for (unsigned long i = 0; i < sizeof(result) / sizeof(result[0]); i++)
		ck_assert_int_eq((long int)get_at(list, i), result[i]);
}
END_TEST

START_TEST(test_merge_sort_2)
{
	const long int to_sort[] = {
		8,   -61, -18, 98,  60,	 -53, 17,  68,	81,  74,  -39,	-71,
		49,  -68, -81, 21,  25,	 -20, 63,  -9,	36,  -1,  -58,	-7,
		-62, 82,  -4,  -65, 34,	 -59, -34, -8,	-29, 47,  28,	-25,
		51,  -88, 2,   1,   -15, -84, -93, 96,	31,  -23, -75,	19,
		58,  -86, -3,  -13, -96, 38,  -27, -21, -95, 7,	  -26,	-56,
		43,  -78, -19, 42,  53,	 65,  -31, 86,	-67, -90, -38,	71,
		-2,  -32, -97, 55,  -16, 40,  26,  44,	24,  -10, 92,	70,
		-24, -55, -91, -92, 67,	 93,  4,   -11, 75,  90,  -5,	16,
		-50, -46, -64, -52, 41,	 -17, -72, 91,	22,  15,  32,	72,
		80,  -49, 30,  87,  57,	 -79, -48, -60, -57, 77,  -100, -41,
		-14, 6,	  -47, 20,  -12, 18,  59,  48,	-94, -63, 54,	89,
		97,  -6,  100, -89, 94,	 69,  -70, 39,	-44, 27,  29,	76,
		-87, -98, 13,  -80, -73, 78,  33,  -22, 10,  -85, -36,	-28,
		64,  -40, 45,  84,  -35, 85,  35,  3,	99,  -66, 12,	-77,
		95,  11,  -37, -51, 5,	 73,  66,  -83, 50,  -45, 79,	-33,
		46,  -74, -69, 62,  23,	 14,  -76, -30, -43, 61,  0,	9,
		83,  56,  37,  -99, -82, 52,  -42, -54, 88
	};

	for (unsigned long i = 0; i < sizeof(to_sort) / sizeof(to_sort[0]); i++)
		add(&list, (void *)to_sort[i]);

	merge_sort(&list);
	const long int result[] = {
		-100, -99, -98, -97, -96, -95, -94, -93, -92, -91, -90, -89,
		-88,  -87, -86, -85, -84, -83, -82, -81, -80, -79, -78, -77,
		-76,  -75, -74, -73, -72, -71, -70, -69, -68, -67, -66, -65,
		-64,  -63, -62, -61, -60, -59, -58, -57, -56, -55, -54, -53,
		-52,  -51, -50, -49, -48, -47, -46, -45, -44, -43, -42, -41,
		-40,  -39, -38, -37, -36, -35, -34, -33, -32, -31, -30, -29,
		-28,  -27, -26, -25, -24, -23, -22, -21, -20, -19, -18, -17,
		-16,  -15, -14, -13, -12, -11, -10, -9,	 -8,  -7,  -6,	-5,
		-4,   -3,  -2,	-1,  0,	  1,   2,   3,	 4,   5,   6,	7,
		8,    9,   10,	11,  12,  13,  14,  15,	 16,  17,  18,	19,
		20,   21,  22,	23,  24,  25,  26,  27,	 28,  29,  30,	31,
		32,   33,  34,	35,  36,  37,  38,  39,	 40,  41,  42,	43,
		44,   45,  46,	47,  48,  49,  50,  51,	 52,  53,  54,	55,
		56,   57,  58,	59,  60,  61,  62,  63,	 64,  65,  66,	67,
		68,   69,  70,	71,  72,  73,  74,  75,	 76,  77,  78,	79,
		80,   81,  82,	83,  84,  85,  86,  87,	 88,  89,  90,	91,
		92,   93,  94,	95,  96,  97,  98,  99,	 100
	};

	for (unsigned long i = 0; i < sizeof(result) / sizeof(result[0]); i++)
		ck_assert((long int)get_at(list, i) == result[i]);
}
END_TEST

START_TEST(test_get_element)
{
	int list_size = 7;
	ck_assert(get_at(list, -1) == NULL);

	for (long int i = 0; i < list_size; i++)
		add_at(&list, i, (void *)i);

	ck_assert(get_at(list, 9) == NULL);
}
END_TEST

START_TEST(test_delete_by_content)
{
	int list_size = 10;

	for (long int i = 0; i < list_size; i++)
		add(&list, (void *)i);

	ck_assert(delete_by_content(&list, (void *)0));
	ck_assert(delete_by_content(&list, (void *)4));
	ck_assert(delete_by_content(&list, (void *)9));
	ck_assert(!delete_by_content(&list, (void *)112));

	int result[] = { 1, 2, 3, 5, 6, 7, 8 };

	for (int i = 0; i < list_size - 3; i++)
		ck_assert_int_eq((long int)get_at(list, i), result[i]);
}
END_TEST

START_TEST(test_delete_by_index)
{
	int list_size = 10;

	for (long int i = 0; i < list_size; i++)
		add(&list, (void *)i);

	ck_assert(delete_by_index(&list, 0));
	ck_assert(delete_by_index(&list, 4));
	ck_assert(delete_by_index(&list, 7));
	ck_assert(!delete_by_index(&list, 112));

	int result[] = { 1, 2, 3, 4, 6, 7, 8 };

	for (int i = 0; i < list_size - 3; i++)
		ck_assert((long int)get_at(list, i) == result[i]);
}
END_TEST

START_TEST(test_clear_list)
{
	int list_size = 10;

	for (long int i = 0; i < list_size; i++)
		add(&list, (void *)i);

	clear_list(&list);

	ck_assert(get_at(list, 0) == NULL);
}
END_TEST

Suite *single_linked_list_suite(void)
{
	Suite *s;
	TCase *tc_core;
	s = suite_create("Single linked list");
	tc_core = tcase_create("single_linked_list");

	tcase_add_checked_fixture(tc_core, single_linked_list_setup,
				  single_linked_list_teardown);
	tcase_add_test(tc_core, test_add);
	tcase_add_test(tc_core, test_add_many);
	tcase_add_test(tc_core, test_sequential_add_at);
	tcase_add_test(tc_core, test_random_add);
	tcase_add_test(tc_core, test_get_element);
	tcase_add_test(tc_core, test_merge_sort_1);
	tcase_add_test(tc_core, test_merge_sort_2);
	tcase_add_test(tc_core, test_delete_by_content);
	tcase_add_test(tc_core, test_delete_by_index);
	tcase_add_test(tc_core, test_clear_list);

	suite_add_tcase(s, tc_core);
	return s;
}