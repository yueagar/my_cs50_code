#include <stdio.h>
#include <string.h>

int main(void)
{
    char name[50];
    printf("What is your name? ");
    scanf("%s", name);

    /*int n = 0;
    while (name[n] != '\0')
    {
        n++;
    };
    printf("%d\n", n);*/
    printf("%d\n", strlen(name));
};