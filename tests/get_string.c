#include <stdio.h>

#include "cs50.h"


int main(void) {
    string s = get_string("Input: ");
    if (s) {
        printf("%s\n", s);
    }
}
