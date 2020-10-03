#include "cs50.h"
#include <stdio.h>
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

void test_get_string (void ** state)
{
    string name = get_string("");

    assert_string_equal(name, "Rodrigo");
}

int main(void)
{
    const struct CMUnitTest tests [] =
            {
                    cmocka_unit_test (test_get_string),
            };

    int count_fail_tests = cmocka_run_group_tests (tests, setup, teardown);

    return count_fail_tests;
}