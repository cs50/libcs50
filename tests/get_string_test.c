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

void test_get_string_successfully_reads_user_input (void ** state)
{
    // Given
    // user input: Rodrigo

    // When
    string name = get_string("");

    // Should
    assert_string_equal(name, "Rodrigo");
}

void test_get_string_reads_strings_with_spaces (void ** state)
{
    // Given
    // user input: Harness your curiosity to learn about the world—and yourself.

    // When
    string long_string = get_string("");

    // Should
    assert_string_equal(long_string, "Harness your curiosity to learn about the world—and yourself.");
}

int main(void)
{
    const struct CMUnitTest tests [] = {
        cmocka_unit_test (test_get_string_successfully_reads_user_input),
        cmocka_unit_test (test_get_string_reads_strings_with_spaces),
    };

    int count_fail_tests = cmocka_run_group_tests (tests, setup, teardown);

    return count_fail_tests;
}