#include <stdio.h>
#include <string.h>

int main(void)
{
    const int N = 6;
    
    char *strings[] = {"battleship", "boot", "cannon", "iron", "thimble", "top hat"};

    int numbers[] = {20, 500, 10, 5, 100, 1, 50};

    /*int n;
    printf("Number: ");
    scanf("%d", &n);
    for (int i = 0; i < 7; i++) // Linear search
    {
        if (numbers[i] == n)
        {
            printf("Found\n");
            return 0;
        };
    };*/

    char *s;
    printf("String: ");
    scanf("%s", s);
    for (int i = 0; i < N; i++) // Linear search
    {
        printf("%s\n", strings[i]);
        // if (strings[i] == s) // doesn't work
        if (strcmp(strings[i], s) == 0)
        {
            printf("Found\n");
            return 0;
        };
    };

    printf("Not found\n");
    return 1;
};