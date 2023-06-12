#include <math.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            float avg = (image[h][w].rgbtRed + image[h][w].rgbtGreen + image[h][w].rgbtBlue) / 3.0;
            image[h][w].rgbtRed = round(avg);
            image[h][w].rgbtGreen = round(avg);
            image[h][w].rgbtBlue = round(avg);
        };
    };
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    // copy the 2D array
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            temp[h][w] = image[h][w];
        };
    };
    // reflection
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w] = temp[h][width - 1 - w];
        };
    };
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    // copy the 2D array
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            temp[h][w] = image[h][w];
        };
    };
    // blur
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int times = 0;
            float avgRed = 0;
            float avgGreen = 0;
            float avgBlue = 0;
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    if (!(h + i < 0 || h + i > height - 1 || w + j < 0 || w + j > height - 1))
                    {
                        times++;
                        avgRed += temp[h + i][w + j].rgbtRed;
                        avgGreen += temp[h + i][w + j].rgbtGreen;
                        avgBlue += temp[h + i][w + j].rgbtBlue;
                    };
                };
            };
            avgRed /= times;
            avgGreen /= times;
            avgBlue /= times;
            image[h][w].rgbtRed = round(avgRed);
            image[h][w].rgbtGreen = round(avgGreen);
            image[h][w].rgbtBlue = round(avgBlue);
        };
    };
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    // copy the 2D array
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            temp[h][w] = image[h][w];
        };
    };
    // process the 3x3 grid
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // Gx variables
            int GxRed = 0;
            int GxGreen = 0;
            int GxBlue = 0;
            // Gy variables
            int GyRed = 0;
            int GyGreen = 0;
            int GyBlue = 0;

            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    if (!(h + i < 0 || h + i > height - 1 || w + j < 0 || w + j > height - 1))
                    {
                        // Gx part
                        GxRed += temp[h + i][w + j].rgbtRed * j * (i == 0 ? 2 : 1);
                        GxGreen += temp[h + i][w + j].rgbtGreen * j * (i == 0 ? 2 : 1);
                        GxBlue += temp[h + i][w + j].rgbtBlue * j * (i == 0 ? 2 : 1);

                        // Gy part
                        GyRed += temp[h + i][w + j].rgbtRed * i * (j == 0 ? 2 : 1);
                        GyGreen += temp[h + i][w + j].rgbtGreen * i * (j == 0 ? 2 : 1);
                        GyBlue += temp[h + i][w + j].rgbtBlue * i * (j == 0 ? 2 : 1);
                    };
                };
            };
            // applying formula
            int finalRed = round(sqrt(GxRed * GxRed + GyRed * GyRed));
            int finalGreen = round(sqrt(GxGreen * GxGreen + GyGreen * GyGreen));
            int finalBlue = round(sqrt(GxBlue * GxBlue + GyBlue * GyBlue));

            // cap at 255
            if (finalRed > 255)
            {
                finalRed = 255;
            };
            if (finalGreen > 255)
            {
                finalGreen = 255;
            };
            if (finalBlue > 255)
            {
                finalBlue = 255;
            };

            // done
            image[h][w].rgbtRed = finalRed;
            image[h][w].rgbtGreen = finalGreen;
            image[h][w].rgbtBlue = finalBlue;
        };
    };
    return;
}
