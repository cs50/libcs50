#include "../test_driver.h"

int main(void)
{
    float f = get_float();
    Assertf(f == 0.5, "Expected 0.5, got %f", f);
    f = get_float();
    Assertf(f == -0.5, "Expected -0.5, got %f", f);
    f = get_float();
    Assertf(f == 4.0, "Expected 4, got %f", f);
}
