#include <stdio.h>

int get_size(void);
void print_grid(int size);

int main(void)
{
    // Get size of grid
    int n = get_size();

    // Print grid of bricks
    print_grid(n);
};

int get_size(void)
{
    int n;
    printf("Size: ");
    do
    {
        scanf("%d", &n);
    }
    while (n < 1);
};

void print_grid(int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("#");
        }
        printf("\n");
    };
};