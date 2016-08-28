#include "../test_driver.h"

int main(void)
{
    int i = get_int();
    Assertf(i == -1, "Expected -1, got %d", i);

    i = get_int();
    Assertf(i == 1, "Expected 1, got %d", i);
}
