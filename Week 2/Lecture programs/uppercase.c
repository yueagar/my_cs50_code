#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    char s[100];
    printf("Before: ");
    scanf("%s", s);
    printf("After: ");
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        /*//if (s[i] >= 'a' && s[i] <= 'z')
        if (islower(s[i]))
        {
            //printf("%c", s[i] - 32);
            printf("%c", toupper(s[i]));
        }
        else
        {
            printf("%c", s[i]);
        };*/
        printf("%c", toupper(s[i]));
    };
    printf("\n");
};