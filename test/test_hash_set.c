#include <check.h>
#include <stdlib.h>
#include <string.h>
#include "hash_set.h"
#include "hash.h"
#include "methods_interface.h"

struct hash_set *set;
struct methods_interface *interface;

void hash_set_setup(void)
{
	interface = malloc(sizeof(struct methods_interface));
	interface->compare = NULL;
	interface->free_element = NULL;
	interface->hash = hash_string;
}

void hash_set_teardown(void)
{
	hash_set_free(set);
}

START_TEST(test_add_size_1)
{
	const int n_to_insert = 1;
	const int size = 1;
	char tmp[][4] = { "k1", "k2", "k3", "k4" };

	set = hash_set_init(interface, size);

	for (int i = 0; i < n_to_insert; i++) {
		hash_set_insert(&set, tmp[i]);
	}

	for (int i = 0; i < n_to_insert; i++) {
		ck_assert(hash_set_contains(set, tmp[i]));
	}
	char non_existing[] = "k5";
	ck_assert(!hash_set_contains(set, non_existing));
}
END_TEST

START_TEST(test_add_one_colision)
{
	const int n_to_insert = 4;
	const int size = 3;
	char tmp[][4] = { "k1", "k2", "k3", "k4" };

	set = hash_set_init(interface, size);

	for (int i = 0; i < n_to_insert; i++) {
		hash_set_insert(&set, tmp[i]);
	}

	for (int i = 0; i < n_to_insert; i++) {
		ck_assert(hash_set_contains(set, tmp[i]));
	}
	char non_existing[] = "k5";
	ck_assert(!hash_set_contains(set, non_existing));
}
END_TEST

START_TEST(test_add_no_collisions)
{
	const int n_to_insert = 4;
	const int size = 10;
	char tmp[][4] = { "k1", "k2", "k3", "k4" };

	set = hash_set_init(interface, size);

	for (int i = 0; i < n_to_insert; i++) {
		hash_set_insert(&set, tmp[i]);
	}

	for (int i = 0; i < n_to_insert; i++) {
		ck_assert(hash_set_contains(set, tmp[i]));
	}
	char non_existing[] = "k5";
	ck_assert(!hash_set_contains(set, non_existing));
}
END_TEST

Suite *hash_set_suite(void)
{
	Suite *s;
	TCase *tc_core;
	s = suite_create("Hash set");
	tc_core = tcase_create("hash_set");

	tcase_add_checked_fixture(tc_core, hash_set_setup, hash_set_teardown);
	tcase_add_test(tc_core, test_add_size_1);
	tcase_add_test(tc_core, test_add_one_colision);
	tcase_add_test(tc_core, test_add_no_collisions);

	suite_add_tcase(s, tc_core);
	return s;
}
