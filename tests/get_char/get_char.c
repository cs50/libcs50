#include <stdio.h>
#include "../test_driver.h"

int main(void)
{
    char c = get_char();
    Assertf(c == 'c', "Expected 'c', got '%c'", c);
}
