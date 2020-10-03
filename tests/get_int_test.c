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

void test_get_int (void ** state)
{
    int one = get_int("");
    int two = get_int("");

    assert_true (one == 1);
    assert_true (two == 2);
}

int main(void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_get_int),
    };

    int count_fail_tests = cmocka_run_group_tests (tests, setup, teardown);

    return count_fail_tests;
}