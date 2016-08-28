#include "../test_driver.h"
#include <math.h>

int main(void)
{
    double d = get_double();
    Assertf(d == 0.5, "Expected 0.5, got %lf", d);
    d = get_double();
    Assertf(d == -0.5, "Expected -0.5, got %lf", d);
    d = get_double();
    Assertf(d == 4.0, "Expected 4, got %lf", d);
}
