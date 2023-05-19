#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    const int N = 2;

    typedef struct
    {
        char *name;
        char *number;
    }
    person;

    /*char *names[] = {"Carter", "David"};
    char *numbers[] = {"+1-617-495-1000", "+1-949-468-2750"};*/

    person people[N];

    people[0].name = "Carter";
    people[0].number = "+1-617-495-1000";

    people[1].name = "David";
    people[1].number = "+1-949-468-2750";

    // char *name; // not working
    char *name = malloc(50 * sizeof(char));
    printf("Name: ");
    scanf("%s", name);

    //printf("%s\n", name);

    for (int i = 0; i < N; i++)
    {
        if (strcmp(people[i].name, name) == 0)
        {
            printf("Found %s\n", people[i].number);
            free(name);
            return 0;
        };
    };
    printf("Not found\n");
    free(name);
    return 1;
};