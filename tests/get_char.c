#include <stdio.h>
#include "cs50.h"

char main(void)
{
    char i = get_char();
    printf(" %c \n", i);
    char j = get_char("Enter Character: ");
    printf(" %c \n", j);
}
