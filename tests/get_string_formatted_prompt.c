#include <stdio.h>

#include "cs50.h"


int main(void) {
    string s = get_string("Prompt #%d: ", 1);
    if (s) {
        printf("%s\n", s);
    }

    s = get_string("%s #%d: ", "Prompt", 2);
    if (s) {
        printf("%s\n", s);
    }
}
