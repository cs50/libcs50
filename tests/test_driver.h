#ifndef TEST_DRIVER_H
#define TEST_DRIVER_H
#include "cs50.h"
#include <stdlib.h>
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
