#include <stdio.h>

int main(void)
{
    // Prompt for start size
    int startPopSize;
    do
    {
        printf("Start size: ");
        scanf("%d", &startPopSize);
    }
    while (startPopSize < 9);

    // Prompt for end size
    int endPopSize;
    do
    {
        printf("End size: ");
        scanf("%d", &endPopSize);
    }
    while (endPopSize < startPopSize);

    // Calculate number of years until we reach threshold
    int currentPopSize = startPopSize;
    int years = 0;
    while (currentPopSize < endPopSize)
    {
        currentPopSize = currentPopSize + currentPopSize/3 - currentPopSize/4;
        years++;
    };

    // Print number of years
    printf("Years: %d\n", years);
};
