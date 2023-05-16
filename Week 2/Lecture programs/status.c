#include <stdio.h>

int main(int argc, char* argv[50])
{
    if (argc != 2)
    {
        printf("Missing command-line argument\n");
        return 1;
    }
    else
    {
        printf("hello, %s\n", argv[1]);
    };
};