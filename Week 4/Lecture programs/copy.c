#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *s = malloc(9 * sizeof(char));
    printf("s: ");
    scanf("%s", s);

    //char *t = s;
    char *t = malloc(strlen(s + 1));

    //t = s; // copy address --> pointers pointing to same address

    /*for (int i = 0, n = strlen(s) + 1; i < n; i++)
    {
        t[i] = s[i];
    };*/

    strcpy(t, s);

    if (strlen(t) > 0)
    {
        t[0] = toupper(t[0]);
    };

    printf("s: %s\n", s);
    printf("t: %s\n", t);

    free(s);
    free(t);
};