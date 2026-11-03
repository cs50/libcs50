#include <stdio.h>
#include "cs50.h"

int main(void)
{
    string s = get_string("Enter a line: ");
    if (s == NULL)
    {
        return 1;
    }

    printf("%s\n", s);
}
