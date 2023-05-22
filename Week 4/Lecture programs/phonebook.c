// Saves names and numbers to a CSV file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    FILE *file = fopen("phonebook.csv", "a");

    char *name = malloc(10 * sizeof(char));
    printf("Name: ");
    scanf("%s", name);
    char *number = malloc(30 * sizeof(char));
    printf("Number: ");
    scanf("%s", number);

    fprintf(file, "%s,%s\n", name, number);

    fclose(file);
};