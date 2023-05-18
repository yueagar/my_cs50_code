#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool only_alphabets(char s[]);

void substitute(char p[], char k[]);

int main(int argc, char *argv[]) 
{
    if (!(argc == 2 && only_alphabets(argv[1])))
    { // rejects user's input if there are more than or less than 1 argument or the argument is not English alphabets.
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26) // rejects user's input if the key is not 26 characters long.
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else
    {
        char text[10000];
        printf("plaintext: ");
        fgets(text, 10000, stdin);
        printf("ciphertext: ");
        substitute(text, argv[1]);
        printf("\n");
        return 0;
    };
};

bool only_alphabets(char s[])
{
    bool isCharsAlphabets = true;
    for (int i = 0; i < strlen(s); i++)
    {
        if (!isalpha(s[i]))
        {
            isCharsAlphabets = false; // return false if the input is not an English alphabet
        };
    };
    return isCharsAlphabets;
};

void substitute(char p[], char k[])
{
    char output[strlen(p)];
    for (int i = 0; i < strlen(p); i++)
    {
        char c = p[i];
        if (c >= 65 && c <= 90) // checks if c is A-Z.
        {
            output[i] = (char)toupper(k[p[i] - 65]); // substitution
        }
        else if (c >= 97 && c <= 122) // checks if c is a-z.
        {
            output[i] = (char)tolower(k[p[i] - 97]); // substitution
        }
        else
        {
            output[i] = p[i]; // we leave characters that are not English alphabets alone
        };
        printf("%c", output[i]);
    };
};