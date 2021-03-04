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
	interface = init_methods_interface(NULL, NULL, NULL);
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

START_TEST(test_quick_init)
{
	const int item_cnt = 5;
	char *items[] = { "a", "b", "c", "d", "e" };
	set = hash_set_quick_init(items, item_cnt);

	ck_assert(hash_set_contains(set, "a"));
	ck_assert(hash_set_contains(set, "b"));
	ck_assert(hash_set_contains(set, "c"));
	ck_assert(hash_set_contains(set, "d"));
	ck_assert(hash_set_contains(set, "e"));
	ck_assert(!hash_set_contains(set, "f"));
	ck_assert(hash_set_contains(set, "a"));

	free(interface);
}
END_TEST

START_TEST(test_quick_init_2)
{
	char *items[] = {
		"ALL",	    "AND",	 "AS",	     "ASC",	  "AVG",
		"BETWEEN",  "BYTE",	 "CHAR",     "CHARACTER", "CREATE",
		"COUNT",    "DATE",	 "DECIMAL",  "DELETE",	  "DESC",
		"DISTINCT", "DOUBLE",	 "DROP",     "EXISTS",	  "FALSE",
		"FLOAT",    "FOREIGN",	 "FROM",     "GROUP",	  "BY",
		"HAVING",   "IN",	 "INDEX",    "INSERT",	  "INTEGER",
		"INTO",	    "IS",	 "KEY",	     "LIKE",	  "MAX",
		"MIN",	    "NOT",	 "NULL",     "NUMERIC",	  "ON",
		"OR",	    "ORDER",	 "BY",	     "NULL",	  "NUMERIC",
		"TABLE",    "TEMPORARY", "TRUE",     "UPDATE",	  "UNION",
		"UNIQUE",   "UNKNOWN",	 "UNSIGNED", "VALUES",	  "VARCHAR",
		"VARYING",  "VIEW",	 "WHERE"
	};
	int item_cnt = 58;

	set = hash_set_quick_init(items, item_cnt);

	ck_assert(hash_set_contains(set, "WHERE"));
	ck_assert(hash_set_contains(set, "BY"));
	ck_assert(hash_set_contains(set, "IS"));
	ck_assert(hash_set_contains(set, "ALL"));
	ck_assert(hash_set_contains(set, "VIEW"));
	ck_assert(!hash_set_contains(set, "VVVa"));
	ck_assert(hash_set_contains(set, "AND"));

	free(interface);
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
	tcase_add_test(tc_core, test_quick_init);
	tcase_add_test(tc_core, test_quick_init_2);

	suite_add_tcase(s, tc_core);
	return s;
}
