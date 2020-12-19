//
// Created by incvis on 19.12.2020.
//


#include <stdlib.h>
#include <stdint.h>
#include <check.h>




void setup(void)
{
}

void teardown(void)
{
}

START_TEST(test_sample_create) {
        ck_assert_int_eq(11, 10);
}

END_TEST

START_TEST(test_sample_sum)
{
        ck_assert_int_eq(15, 15);
}

END_TEST


Suite * make_sample_creation_suite(void) {
        Suite *s;
        TCase *tc_core;

        s = suite_create("Sample Creation Test Suite");

        /* Creation test case */
        tc_core = tcase_create("Test Cases with Setup and Teardown");

        tcase_add_checked_fixture(tc_core, setup, teardown);
        tcase_add_test(tc_core, test_sample_create);
        tcase_add_test(tc_core, test_sample_sum);

        suite_add_tcase(s, tc_core);

        return s;
}
int main(void)
{
        int number_failed;
        SRunner *sr;

        sr = srunner_create(make_sample_creation_suite());
        srunner_set_fork_status(sr, CK_NOFORK);
        srunner_set_log (sr, "test.log");
        srunner_set_xml (sr, "test.xml");
        srunner_run_all(sr, CK_VERBOSE);

        number_failed = srunner_ntests_failed(sr);
        srunner_free(sr);
        return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
