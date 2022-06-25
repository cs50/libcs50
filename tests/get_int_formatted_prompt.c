#include <stdio.h>

#include "cs50.h"


int main(void) {
    int i = get_int("Prompt #%d: ", 1);
    printf("%d\n", i);

    i = get_int("%s #%d: ", "Prompt", 2);
    printf("%d\n", i);
}
