#include <stdio.h>
#include "cs50.h"

int main(void)
{
    int i = get_int("Enter a number:\n");
    printf("%i\n", i);
    int j = get_int("Foo: ");
    printf("%i\n", j);
}
