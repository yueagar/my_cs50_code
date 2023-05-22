#include <stdio.h>

//void swap(int a, int b);
void swap(int *a,int *b);

int main(void)
{
    int x = 1;
    int y = 2;

    printf("x is %i, y is %i\n", x, y);
    //swap(x, y);
    swap(&x, &y); // addresses of x and y
    printf("x is %i, y is %i\n", x, y);
};

/*void swap (int a, int b)
{
    int tmp = a;
    a = b;
    b = tmp; // doesn't swap x and y in main due to different scopes.
};*/

void swap (int *a, int *b) // a and b are pointers pointing to the addresses of x and y.
{
    int tmp = *a;
    *a = *b;
    *b = tmp; // swapping the values in the addresses of x and y, effectively swapping x and y.
};