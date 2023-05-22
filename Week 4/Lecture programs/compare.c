#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    /*int i, j;
    printf("i: ");
    scanf("%i", &i);
    printf("j: ");
    scanf("%i", &j);*/
    char *s, *t = malloc(9 * sizeof(char));
    printf("s: ");
    scanf("%s", s);
    printf("t: ");
    scanf("%s", t);

    /*//if (i == j)
    //if (s == t)
    if (strcmp(s, t) == 0)
    //if (*s == *t) // comparing first letter only
    {
        printf("Same\n");
    }
    else
    {
        printf("Different\n");
    };*/

    //printf("%s\n", s);
    //printf("%s\n", t);
    printf("%p\n", s);
    printf("%p\n", t);

    free(s);
    free(t);
};