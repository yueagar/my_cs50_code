#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    /*int x;
    printf("x: ");
    scanf("%i", &x);
    printf("x: %i\n", x);*/

    // difficult to determine a good amount of memory that needs to be allocated
    char s[4];
    //char *s = malloc(4 * sizeof(char));
    printf("s: ");
    scanf("%s", s); // s is already an address of the first character of the whole string, no need to add & in before.
    printf("s: %s\n", s);
};