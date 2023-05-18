#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(char s[]);

char rotate(char c, int n);

int main(int argc, char *argv[]) 
{
    if (!(argc == 2 && only_digits(argv[1]))) { // rejects user's input if there are more than or less than 1 argument or the argument is not a digit.
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else {
        int key = atoi(argv[1]); // turn the character into integer.
        char text[10000];
        printf("plaintext: ");
        fgets(text, 10000, stdin);
        printf("ciphertext: ");
        for (int i = 0; i < strlen(text); i++) // encode every character
        {
            char encodedChar = rotate(text[i], key);
            printf("%c", encodedChar); // print out the encoded character
        };
        printf("\n");
        return 0;
    };
};

bool only_digits(char s[])
{
    bool isCharsDigits = true;
    for (int i = 0; i < strlen(s); i++)
    {
        if (!isdigit(s[i]))
        {
            isCharsDigits = false; // return false if the input is not a digit
        };
    };
    return isCharsDigits;
};

char rotate(char c, int n)
{
    if (c >= 65 && c <= 90) // checks if c is A-Z.
    {
        int code = (c - 65 + n) % 26; // shifts ascii code
        code += 65;
        return (char)code;
    }
    else if (c >= 97 && c <= 122) // checks if c is a-z.
    {
        int code = (c - 97 + n) % 26; // shifts ascii code
        code += 97;
        return (char)code;
    }
    else
    {
        return c;
    };
};