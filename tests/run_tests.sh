#!/bin/bash

# Compile
clang -o get_int_test get_int_test.c -lcs50 -lcmocka
clang -o get_string_test get_string_test.c -lcs50 -lcmocka

# Mock user input
one="1"
two="2"
name="Rodrigo"

# Run tests
printf $one'\n'$two'\n' | ./get_int_test
printf $name'\n' | ./get_string_test

# Cleanup
rm ./get_int_test
rm ./get_string_test
