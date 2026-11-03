#include <stdio.h>
#include "cs50.h"

int main(void)
{
    float f = get_float("Enter a float: ");
    printf("%g\n", (double) f);
}
