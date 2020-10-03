#!/bin/bash

# Compile
clang -o get_int_test get_int_test.c -lcs50 -lcmocka
clang -o get_string_test get_string_test.c -lcs50 -lcmocka

# Mock user input
a="a"
b="b"
one="1"
two="2"
name="Rodrigo"
string_with_spaces="Harness your curiosity to learn about the world—and yourself."

# Run tests
echo 'Testing get_int function'
printf $one'\n'$two'\n\'$a'n\'$b'\n'$name'\n'$one'\n' | ./get_int_test
echo 'Testing get_string function'
printf $name'\n'"$string_with_spaces"'\n' | ./get_string_test

# Cleanup
rm ./get_int_test
rm ./get_string_test
