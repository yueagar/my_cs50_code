#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    /*int *x = malloc(3 * sizeof(int));
    x[1] = 72; // bug
    x[2] = 73;
    x[3] = 33;

    // not freed*/

    /* FIX */
    int *x = malloc(3 * sizeof(int));
    if (x == NULL)
    {
        return 1;
    };
    x[0] = 72;
    x[1] = 73;
    x[2] = 33;
    free(x);
    return 0;
};