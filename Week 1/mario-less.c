#include <stdio.h>

int getSize(void);
void printPyramid(int size);

int main(void)
{
    // Get size of pyramid
    int size = getSize();

    // Print the pyramid;
    printPyramid(size);
}

int getSize(void)
{
    int n;
    do
    {
        printf("Size: ");
        scanf("%d", &n);
    }
    while (n < 1 || n > 8); // rejects n that is smaller than 1 or greater than 8.
    return n;
}

void printPyramid(int size)
{
    for (int i = 0; i < size; i++) // handles the vertical component of the pyramid
    {
        for (int j = 0; j < size; j++) // handles the horizontal component of the pyramid
        {
            if (i + j < size - 1)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("\n");
    };
};