#include <stdio.h>
#include <stdbool.h>

bool isValidCardNo(long n);
void printCardType(long n);

int main(void)
{
    long n;
    do {
        printf("Number: ");
        scanf("%ld", &n);
    }
    while (n < 0); // Rejects input number less than 0.
    if (isValidCardNo(n))
    {
        printCardType(n);
    }
    else
    {
        printf("INVALID\n");
    };
};

bool isValidCardNo(long n)
{
    // printf("So your card number is %ld\n", n);
    long cardNo = n; // a local variable of the card number, which will be changed during checking
    int checksum = 0;
    int checked = 0; // checked for how many times
    while (cardNo > 0)
    {
        if (checked % 2 == 0)
        {
            int x = cardNo % 10;
            // printf("Remaining digit: %d\n", x);
            checksum += x;
        }
        else if (checked % 2 == 1)
        {
            int x = cardNo % 10 * 2;
            // printf("Every other digit: %d (%d)\n", x % 10 + x / 10, x);
            checksum += x % 10 + x / 10; // if x > 10, we break it down into 2 digits.
        };
        cardNo /= 10;
        checked++;
        // printf("Checked %d\n", checked);
    };
    // printf("Checksum: %d\n", checksum);
    if (checksum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    };
};

void printCardType(long n)
{
    long handledDigits = n;
    int firstOneDigit, firstTwoDigits, totalDigits = 0;
    while (handledDigits > 100)
    {
        handledDigits /= 10;
        totalDigits++;
    };
    totalDigits += 2; // add 2 to obtain the accurate total number of digits of the card number
    firstTwoDigits = handledDigits;
    firstOneDigit = firstTwoDigits / 10;
    // printf("%d %d %d\n", totalDigits, firstTwoDigits, firstOneDigit);
    if ((totalDigits == 13 || totalDigits == 16) && firstOneDigit == 4)
    {
        printf("VISA\n");
    }
    else if (totalDigits == 15 && (firstTwoDigits == 34 || firstTwoDigits == 37))
    {
        printf("AMEX\n");
    }
    else if (totalDigits == 16 && firstTwoDigits > 50 && firstTwoDigits < 56)
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    };
};