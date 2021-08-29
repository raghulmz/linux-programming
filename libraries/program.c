#include <stdio.h>
#include "simplelib.h"

int main()
{
    printf("simplelib version: %s\n", ver());
    printf("Sum: %d\n", addSome(1, 2));
    return 0;
}