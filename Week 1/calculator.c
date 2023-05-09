#include <stdio.h>

int main(void)
{
    long x, y;
    printf("x: ");
    scanf("%ld", &x);
    printf("y: ");
    scanf("%ld", &y);

    double z = (double) x / (double) y;

    printf("%.20f\n", z);
};