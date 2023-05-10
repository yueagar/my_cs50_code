#include <stdio.h>

int main(void)
{
    // Ask user to input his/her name.
    char name[30];
    printf("What is your name? ");
    scanf("%s", name);
    // Say hello to the user.
    printf("hello, %s\n", name);
};