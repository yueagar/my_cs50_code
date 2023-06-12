#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // a small check for arguments
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE");
        return 1;
    };

    // open the input file
    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL)
    {
        printf("Cannot open the file");
        return 2;
    };

    // read and edit the input file
    uint8_t buffer[BLOCK_SIZE];
    int count = 0;
    char *filename = malloc(8 * sizeof(char));
    FILE *outputFile = NULL;
    while (fread(&buffer, sizeof(uint8_t), BLOCK_SIZE, inputFile) == BLOCK_SIZE)
    {
        // check the presence of JPEG header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // close old JPEG file if such file exists
            if (outputFile != NULL)
            {
                fclose(outputFile);
            };
            // create new JPEG file
            sprintf(filename, "%03i.jpg", count);
            outputFile = fopen(filename, "w");
            count++;
        };
        if (outputFile != NULL)
        {
            // write data
            fwrite(&buffer, sizeof(uint8_t), BLOCK_SIZE, outputFile);
        };
    };

    // close all files and free memory
    fclose(inputFile);
    free(filename);
    fclose(outputFile);
}