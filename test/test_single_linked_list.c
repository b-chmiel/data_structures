//
// Created by incvis on 19.12.2020.
//

#include <stdlib.h>
#include <stdint.h>
#include <check.h>
#include <lib/includes/single_linked_list.h>
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

//TEST(Sorting, MergeSortedEven)
//{
//        struct node *head = nullptr;
//        struct node *first = nullptr;
//        struct node *second = nullptr;
//
//        int list_size = 10;
//        int list1[] = {1, 23, 2, 4, 5};
//        int list2[] = {4, 2, 6, 1, -3};
//
//        for (int i = 0; i < list_size / 2; i++) {
//                add(&first, list1[i]);
//                add(&second, list2[i]);
//        }
//
//        merge_sorted(&head, first, second, nullptr);
//        print_list(head);
//        int result[] = {1, 4, 2, 6, 1, -3, 23, 2, 4, 5};
//
//        for (int i = 0; i < list_size; i++)
//                EXPECT_EQ(get_at(i, head), result[i]);
//
//        delete_list(&head);
//}

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

                for ( int i = 0; i < list_size; i++)
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

                for ( int i = 0; i < list_size; i++)
                        add_at(i, i, &head);

                ck_assert(delete_by_index(0, &head));
                ck_assert(delete_by_index(4, &head));
                ck_assert(delete_by_index(7, &head));
                ck_assert(!delete_by_index(112, &head));

                int result[] = {1, 2, 3, 4, 6, 7, 8};

                for ( int i = 0; i < list_size - 3; i++)
                        ck_assert(get_at(i, head) == result[i]);

                delete_list(&head);
        }
END_TEST

START_TEST(test_delete_list)
        {
                int list_size = 10;

                for ( int i = 0; i < list_size; i++)
                        add_at(i, i, &head);

                delete_list(&head);

                ck_assert(get_at( 0, head) == INT_MAX);
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
        srunner_set_fork_status(sr, CK_NOFORK);
        srunner_set_log(sr, "test.log");
        srunner_set_xml(sr, "test.xml");
        srunner_run_all(sr, CK_VERBOSE);

        number_failed = srunner_ntests_failed(sr);
        srunner_free(sr);
        return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
