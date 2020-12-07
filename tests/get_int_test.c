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
    int input1 = 1;
    int input2 = 2;

    // When
    int one = get_int("");
    int two = get_int("");

    // Should
    assert_true (one == input1);
    assert_true (two == input2);
}

void test_get_int_ignores_non_number_input (void ** state)
{
    // Given
    // user input is a, then b, then Rodrigo and finally 1
    int last_input = 1;

    // When
    int one = get_int("");

    // Should
    assert_true (one == last_input);
}

int main(void)
{
    const struct CMUnitTest tests [] = {
        cmocka_unit_test (test_get_int_successfully_reads_user_input),
        cmocka_unit_test (test_get_int_ignores_non_number_input),
    };

    int count_fail_tests = cmocka_run_group_tests (tests, setup, teardown);

    return count_fail_tests;
}