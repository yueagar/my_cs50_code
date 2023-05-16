#include <stdio.h>

/*int main(void)
{
    char name[50];
    printf("What's your name? ");
    scanf("%s", name);
    printf("Hello, %s\n", name);
};*/

int main(int argc, char* argv[50])
{
    if (argc == 2)
    {
        printf("hello, %s\n", argv[1], argv[2]);
    }
    else
    {
        printf("hello, world\n");
    }
};