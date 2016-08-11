#include "../test_driver.h"

int main(void)
{
    long long l = get_long_long();
    Assertf(l == 2147483647, "Expected -1, got %lld", l);

    l = get_long_long();
    Assertf(l == -2147483648, "Expected 1, got %lld", l);
}
