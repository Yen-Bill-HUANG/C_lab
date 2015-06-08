#include <stdio.h>
#include <stdlib.h>

#include "usage.h"

void
usage(const char *str)
{
    fprintf(stderr, "usage: %s\n", str);
    exit(1);
}