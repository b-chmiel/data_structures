//
// Created by incvis on 19.12.2020.
//

#include <stdlib.h>
#include <stdint.h>
#include <check.h>
#include <lib/single_linked_list.h>
#include <limits.h>

struct node *head;

void setup(void)
{
        head = NULL;
}

void teardown(void)
{
}

START_TEST(test_add)
        {
                int list_size = 5;

                for (int i = 0; i < list_size; i++)
                        add(&head, i);

                for (int i = 0; i < list_size; i++)
                        ck_assert_int_eq(get_at(i, head), i);

                delete_list(&head);
        }
END_TEST

START_TEST(test_add_many)
        {
                int list_size = 5;

                add_many(&head, list_size, 0, 1, 2, 3, 4);

                for (int i = 0; i < list_size; i++)
                        ck_assert_int_eq(get_at(i, head), i);

                delete_list(&head);
        }
END_TEST

START_TEST(test_sequential_add_at)
        {
                int list_size = 7;
                int items[] = {1, 3, 2, 4, 5, 22, -23};

                for (int i = 0; i < list_size; i++)
                        add_at(i, items[i], &head);

                for (int i = 0; i < list_size; i++)
                        ck_assert_int_eq(get_at(i, head), items[i]);

                delete_list(&head);
        }
END_TEST

START_TEST(test_random_add)
        {
                int list_size = 7;

                add_at(0, 1, &head);
                add_at(5, 2, &head);
                add_at(3, 3, &head);
                add_at(6, 4, &head);
                add_at(2, 5, &head);
                add_at(2, 6, &head);
                add_at(1, 7, &head);

                int result[] = {1, 7, 2, 6, 5, 3, 4};
                for (int i = 0; i < list_size; i++)
                        ck_assert_int_eq(get_at(i, head), result[i]);

                delete_list(&head);
        }
END_TEST

START_TEST(test_split_into_two_even)
        {
                struct node *first = NULL;
                struct node *second = NULL;
                int list_size = 10;

                for (int i = 0; i < list_size; i++)
                        add(&head, i);

                split_into_two(head, &first, &second);

                int list1[] = {0, 1, 2, 3, 4};
                int list2[] = {5, 6, 7, 8, 9};

                for (int i = 0; i < list_size / 2; i++) {
                        ck_assert_int_eq(get_at(i, first), list1[i]);
                        ck_assert_int_eq(get_at(i, second), list2[i]);
                }

                delete_list(&first);
                delete_list(&second);
        }
END_TEST

START_TEST(test_split_into_two_odd)
        {
                struct node *first = NULL;
                struct node *second = NULL;
                int list_size = 9;

                for (int i = 0; i < list_size; i++)
                        add(&head, i);

                split_into_two(head, &first, &second);

                int list1[] = {0, 1, 2, 3, 4};
                int list2[] = {5, 6, 7, 8};
                for (int i = 0; i < list_size / 2 - 1; i++) {
                        ck_assert_int_eq(get_at(i, first), list1[i]);

                        ck_assert_int_eq(get_at(i, second), list2[i]);
                }

                delete_list(&first);
                delete_list(&second);
        }
END_TEST

START_TEST(test_split_one_element)
        {
                struct node *first = NULL;
                struct node *second = NULL;
                int list_size = 1;

                for (int i = 0; i < list_size; i++)
                        add(&head, i);

                split_into_two(head, &first, &second);

                ck_assert_int_eq(get_at(0, head), 0);
                ck_assert(second == NULL);
                ck_assert(first->next == NULL);

                delete_list(&first);
                delete_list(&second);
        }
END_TEST

START_TEST(test_merge_sorted_even)
        {
                struct node *first = NULL;
                struct node *second = NULL;

                int list_size = 10;
                int list1[] = {1, 23, 2, 4, 5};
                int list2[] = {4, 2, 6, 1, -3};

                for (int i = 0; i < list_size / 2; i++) {
                        add(&first, list1[i]);
                        add(&second, list2[i]);
                }

                merge_sorted(&head, first, second, NULL);
                int result[] = {1, 4, 2, 6, 1, -3, 23, 2, 4, 5};

                for (int i = 0; i < list_size; i++)
                        ck_assert(get_at(i, head) == result[i]);

                delete_list(&head);
        }
END_TEST

START_TEST(test_merge_sorted_odd)
        {
                struct node *first = NULL;
                struct node *second = NULL;

                int list_size = 9;
                int list1[] = {1, 23, 2, 4, 5};
                int list2[] = {4, 2, 6, 1};

                for (int i = 0; i < list_size / 2; i++) {
                        add(&first, list1[i]);
                        add(&second, list2[i]);
                }
                add(&first, list1[4]);

                merge_sorted(&head, first, second, NULL);
                int result[] = {1, 4, 2, 6, 1, 23, 2, 4, 5};

                for (int i = 0; i < list_size; i++)
                        ck_assert(get_at(i, head) == result[i]);

                delete_list(&head);
        }
END_TEST

START_TEST(test_merge_sorted_first_null_case)
        {
                struct node *first = NULL;
                struct node *second = NULL;

                int list_size = 9;
                int list1[] = {1, 3, 2, 4, 5};
                int list2[] = {4, 2, 6, 1};

                for (int i = 0; i < list_size / 2; i++) {
                        add(&first, list1[i]);
                        add(&second, list2[i]);
                }
                add(&first, list1[4]);

                merge_sorted(&head, first, second, NULL);
                int result[] = {1, 3, 2, 4, 2, 4, 5, 6, 1};

                for (int i = 0; i < list_size; i++)
                        ck_assert(get_at(i, head) == result[i]);

                delete_list(&head);
        }
END_TEST

START_TEST(test_merge_sort_1)
        {
                int list[] = {50, 24, 27, 70, 10, 68, 67, 94, 76, 85, 57, 66, 5, 41, 28, 47, 58, 49, 2, 16, 98, 45, 8,
                              48, 25, 26, 13};

                for (unsigned long i = 0; i < sizeof(list) / sizeof(list[0]); i++) {
                        add(&head, list[i]);
                }

                merge_sort(&head, NULL);
                int result[] = {2, 5, 8, 10, 13, 16, 24, 25, 26, 27, 28, 41, 45, 47, 48, 49, 50, 57, 58, 66, 67, 68, 70,
                                76, 85, 94, 98};

                for (unsigned long i = 0; i < sizeof(list) / sizeof(list[0]); i++)
                        ck_assert(get_at(i, head) == result[i]);

                delete_list(&head);
        }
END_TEST

START_TEST(test_merge_sort_2)
        {
                int list[] = {8, -61, -18, 98, 60, -53, 17, 68, 81, 74, -39, -71, 49, -68, -81, 21, 25, -20, 63, -9, 36,
                              -1, -58, -7, -62, 82, -4, -65, 34, -59, -34, -8, -29, 47, 28, -25, 51, -88, 2, 1, -15,
                              -84, -93, 96, 31, -23, -75, 19, 58, -86, -3, -13, -96, 38, -27, -21, -95, 7, -26, -56, 43,
                              -78, -19, 42, 53, 65, -31, 86, -67, -90, -38, 71, -2, -32, -97, 55, -16, 40, 26, 44, 24,
                              -10, 92, 70, -24, -55, -91, -92, 67, 93, 4, -11, 75, 90, -5, 16, -50, -46, -64, -52, 41,
                              -17, -72, 91, 22, 15, 32, 72, 80, -49, 30, 87, 57, -79, -48, -60, -57, 77, -100, -41, -14,
                              6, -47, 20, -12, 18, 59, 48, -94, -63, 54, 89, 97, -6, 100, -89, 94, 69, -70, 39, -44, 27,
                              29, 76, -87, -98, 13, -80, -73, 78, 33, -22, 10, -85, -36, -28, 64, -40, 45, 84, -35, 85,
                              35, 3, 99, -66, 12, -77, 95, 11, -37, -51, 5, 73, 66, -83, 50, -45, 79, -33, 46, -74, -69,
                              62, 23, 14, -76, -30, -43, 61, 0, 9, 83, 56, 37, -99, -82, 52, -42, -54, 88};

                for (unsigned long i = 0; i < sizeof(list) / sizeof(list[0]); i++) {
                        add(&head, list[i]);
                }

                merge_sort(&head, NULL);
                int result[] = {-100, -99, -98, -97, -96, -95, -94, -93, -92, -91, -90, -89, -88, -87, -86, -85, -84,
                                -83, -82, -81, -80, -79, -78, -77, -76, -75, -74, -73, -72, -71, -70, -69, -68, -67,
                                -66, -65, -64, -63, -62, -61, -60, -59, -58, -57, -56, -55, -54, -53, -52, -51, -50,
                                -49, -48, -47, -46, -45, -44, -43, -42, -41, -40, -39, -38, -37, -36, -35, -34, -33,
                                -32, -31, -30, -29, -28, -27, -26, -25, -24, -23, -22, -21, -20, -19, -18, -17, -16,
                                -15, -14, -13, -12, -11, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6,
                                7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
                                30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
                                52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73,
                                74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95,
                                96, 97, 98, 99, 100};

                for (unsigned long i = 0; i < sizeof(list) / sizeof(list[0]); i++)
                        ck_assert(get_at(i, head) == result[i]);

                delete_list(&head);
        }
END_TEST


START_TEST(test_get_element)
        {
                int list_size = 7;
                ck_assert(get_at(-1, head) == INT_MIN);

                for (int i = 0; i < list_size; i++)
                        add_at(i, i, &head);

                ck_assert(get_at(9, head) == INT_MAX);

                delete_list(&head);
        }
END_TEST

START_TEST(test_delete_by_content)
        {
                int list_size = 10;

                for (int i = 0; i < list_size; i++)
                        add_at(i, i, &head);

                ck_assert(delete_by_content(0, &head));
                ck_assert(delete_by_content(4, &head));
                ck_assert(delete_by_content(9, &head));
                ck_assert(!delete_by_content(112, &head));

                int result[] = {1, 2, 3, 5, 6, 7, 8};

                for (int i = 0; i < list_size - 3; i++)
                        ck_assert(get_at(i, head) == result[i]);

                delete_list(&head);
        }
END_TEST

START_TEST(test_delete_by_index)
        {
                int list_size = 10;

                for (int i = 0; i < list_size; i++)
                        add_at(i, i, &head);

                ck_assert(delete_by_index(0, &head));
                ck_assert(delete_by_index(4, &head));
                ck_assert(delete_by_index(7, &head));
                ck_assert(!delete_by_index(112, &head));

                int result[] = {1, 2, 3, 4, 6, 7, 8};

                for (int i = 0; i < list_size - 3; i++)
                        ck_assert(get_at(i, head) == result[i]);

                delete_list(&head);
        }
END_TEST

START_TEST(test_delete_list)
        {
                int list_size = 10;

                for (int i = 0; i < list_size; i++)
                        add_at(i, i, &head);

                delete_list(&head);

                ck_assert(get_at(0, head) == INT_MAX);
                ck_assert(head == NULL);
        }
END_TEST

Suite *adding_suite(void)
{
        Suite *s;
        TCase *tc_core;

        s = suite_create("Adding");

        /* Creation test case */
        tc_core = tcase_create("add");

        tcase_add_checked_fixture(tc_core, setup, teardown);
        tcase_add_test(tc_core, test_add);
        tcase_add_test(tc_core, test_add_many);
        tcase_add_test(tc_core, test_sequential_add_at);
        tcase_add_test(tc_core, test_random_add);

        suite_add_tcase(s, tc_core);

        return s;
}

Suite *splitting_suite(void)
{
        Suite *s;
        TCase *tc_core;

        s = suite_create("Splitting");

        /* Creation test case */
        tc_core = tcase_create("split");

        tcase_add_checked_fixture(tc_core, setup, teardown);
        tcase_add_test(tc_core, test_split_into_two_even);
        tcase_add_test(tc_core, test_split_into_two_odd);
        tcase_add_test(tc_core, test_split_one_element);

        suite_add_tcase(s, tc_core);

        return s;
}

Suite *get_element_suite(void)
{
        Suite *s;
        TCase *tc_core;

        s = suite_create("Get element");

        /* Creation test case */
        tc_core = tcase_create("get");

        tcase_add_checked_fixture(tc_core, setup, teardown);
        tcase_add_test(tc_core, test_get_element);

        suite_add_tcase(s, tc_core);

        return s;
}

Suite *sorting_suite(void)
{
        Suite *s;
        TCase *tc_core;

        s = suite_create("Get element");

        /* Creation test case */
        tc_core = tcase_create("get");

        tcase_add_checked_fixture(tc_core, setup, teardown);
        tcase_add_test(tc_core, test_merge_sorted_even);
        tcase_add_test(tc_core, test_merge_sorted_odd);
        tcase_add_test(tc_core, test_merge_sorted_first_null_case);
        tcase_add_test(tc_core, test_merge_sort_1);
        tcase_add_test(tc_core, test_merge_sort_2);

        suite_add_tcase(s, tc_core);

        return s;
}

Suite *deleting_suite(void)
{
        Suite *s;
        TCase *tc_core;

        s = suite_create("Deletion");

        /* Creation test case */
        tc_core = tcase_create("delete");

        tcase_add_checked_fixture(tc_core, setup, teardown);
        tcase_add_test(tc_core, test_delete_by_content);
        tcase_add_test(tc_core, test_delete_by_index);
        tcase_add_test(tc_core, test_delete_list);

        suite_add_tcase(s, tc_core);

        return s;
}

int main(void)
{
        int number_failed;
        SRunner *sr;

        sr = srunner_create(adding_suite());
        srunner_add_suite(sr, splitting_suite());
        srunner_add_suite(sr, get_element_suite());
        srunner_add_suite(sr, deleting_suite());
        srunner_add_suite(sr, sorting_suite());
        srunner_set_fork_status(sr, CK_NOFORK);
        srunner_set_log(sr, "test.log");
        srunner_set_xml(sr, "test.xml");
        srunner_run_all(sr, CK_VERBOSE);

        number_failed = srunner_ntests_failed(sr);
        srunner_free(sr);
        return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}