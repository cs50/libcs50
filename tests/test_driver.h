#ifndef TEST_DRIVER_H
#define TEST_DRIVER_H
#include <stdio.h>
#include <stdlib.h>
#include "../src/cs50.h"
#define Assertf(COND, ...)          \
    do                              \
    {                               \
        if (!(COND))                \
        {                           \
            eprintf(__VA_ARGS__);   \
            fprintf(stderr,"\n");   \
            abort();                \
        }                           \
    } while (false)                 \

#endif
