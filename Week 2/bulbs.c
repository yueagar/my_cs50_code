#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    char message[BITS_IN_BYTE];
    // Ask user to input message to be encoded in binary
    printf("Message: ");
    fgets(message, BITS_IN_BYTE, stdin);

    // Encode every character in the message
    for (int i = 0; i < strlen(message); i++)
    {
        int reverseBinaryBits[BITS_IN_BYTE];
        // zeros as default, i.e. [0, 0, 0, 0, 0, 0, 0, 0]
        for (int j = 0; j < BITS_IN_BYTE; j++)
        {
            reverseBinaryBits[j] = 0;
        };
        int bitPlace = 0;
        int charCode = message[i];
        // determine the position of ones
        while (charCode > 1)
        {
            if (charCode % 2 == 1)
            {
                reverseBinaryBits[bitPlace] = 1;
            };
            charCode /= 2;
            bitPlace++;
        };
        reverseBinaryBits[bitPlace] = 1;
        // reverse the order of ones and zeros to get the correct encoded character
        for (int k = 0; k < BITS_IN_BYTE; k++)
        {
            print_bulb(reverseBinaryBits[BITS_IN_BYTE - k - 1]);
        };
        printf("\n");
    };
};

void print_bulb(int bit)
{
    if (bit == 0)
    {
        printf("X");
    }
    else if (bit == 1)
    {
        printf("O");
    };
};
