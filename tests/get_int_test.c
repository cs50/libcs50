#include <stdio.h>
#include "cs50.h"
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

int setup (void ** state)
{
    return 0;
}

int teardown (void ** state)
{
    return 0;
}

void test_get_int_successfully_reads_user_input (void ** state)
{
    // Given user input
    // 1 and 2

    // When
    int one = get_int("");
    int two = get_int("");

    // Should
    assert_true (one == 1);
    assert_true (two == 2);
}

void test_get_int_ignore_non_number_input (void ** state)
{
    // Given user input
    // a, b, Rodrigo and 1

    // When
    int one = get_int("");

    // Should
    assert_true (one == 1);
}

int main(void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_get_int_successfully_reads_user_input),
        cmocka_unit_test (test_get_int_ignore_non_number_input),
    };

    int count_fail_tests = cmocka_run_group_tests (tests, setup, teardown);

    return count_fail_tests;
}