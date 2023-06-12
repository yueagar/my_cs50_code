#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // 3 arg
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav");
        return 1;
    };
    // file type
    int len = strlen(argv[1]);
    char *inputFileType = &argv[1][len - 4];
    if (strcmp(inputFileType, ".wav") != 0)
    {
        printf("Input is not a WAV file.");
        return 1;
    };

    // Open input file for reading
    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL)
    {
        printf("Cannot open the file.");
        return 1;
    };

    // Read header
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, inputFile);

    // Use check_format to ensure WAV format
    if (check_format(header) != 1)
    {
        printf("Incorrect header");
        return 1;
    };

    // Open output file for writing
    FILE *outputFile = fopen(argv[2], "w");

    // Write header to file
    if (outputFile != NULL)
    {
        fwrite(&header, sizeof(WAVHEADER), 1, outputFile);
        // int offset = ftell(outputFile);
        // printf("%d\n", offset); // returns 44
    };

    // Use get_block_size to calculate size of block
    int blockSize = get_block_size(header);

    // Write reversed audio to file
    fseek(inputFile, blockSize, SEEK_END);

    if (outputFile != NULL)
    {
        BYTE buffer[blockSize];
        while (ftell(inputFile) > 44 + blockSize)
        {
            if (fseek(inputFile, -2 * blockSize, SEEK_CUR) != 0)
            {
                return 1;
            };
            fread(&buffer, blockSize, 1, inputFile);
            fwrite(&buffer, blockSize, 1, outputFile);
        };
    };

    fclose(inputFile);
    fclose(outputFile);
}

int check_format(WAVHEADER header)
{
    if ((char)header.format[0] == 'W' && (char)header.format[1] == 'A' && (char)header.format[2] == 'V'
        && (char)header.format[3] == 'E')
    {
        return 1;
    };
    return 0;
}

int get_block_size(WAVHEADER header)
{
    return header.numChannels * header.bitsPerSample / 8;
}