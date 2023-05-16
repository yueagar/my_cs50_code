#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(char text[]);
int count_words(char text[]);
int count_sentences(char text[]);

int main(void)
{
    char text[8192];
    printf("Text: ");
    fgets(text, 8192, stdin);
    //printf("%s\n", text);

    int numberOfLetters = count_letters(text);
    int numberOfWords = count_words(text);
    int numberOfSentences = count_sentences(text);

    double index = 0.0588 * numberOfLetters / numberOfWords * 100 - 0.296 * numberOfSentences / numberOfWords * 100 - 15.8;
    //printf("%f\n", index);

    int grade = llrintf(index); // round off the index
    //printf("%d\n", grade);

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", grade);
    };
};

int count_letters(char text[])
{
    int numberOfLetters = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        text[i] = tolower(text[i]);
        // checks if the character is a lowercase English letter
        if (islower(text[i]))
        {
            numberOfLetters++;
        };
    };
    //printf("%d letters\n", numberOfLetters);
    return numberOfLetters;
};

int count_words(char text[])
{
    int numberOfWords = 1;
    for (int i = 0; i < strlen(text); i++)
    {
        // check if the character is a space and whether there are multiple spaces
        if (text[i] == 32 && text[i - 1] != 32 && text[i + 1] != 32)
        {
            numberOfWords++;
        };
    };
    //printf("%d words\n", numberOfWords);
    return numberOfWords;
};

int count_sentences(char text[])
{
    int numberOfSentences = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        // check if the character is either . or ! or ? and whether there is ...
        if ((text[i] == 33 || text[i] == 46 || text[i] == 63) && (text[i - 1] != 46 || text[i + 1] != 46))
        {
            numberOfSentences++;
        };
    };
    //printf("%d sentences\n", numberOfSentences);
    return numberOfSentences;
};