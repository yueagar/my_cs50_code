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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // sepia filter formula
            float sepiaRed = .393 * image[h][w].rgbtRed + .769 * image[h][w].rgbtGreen + .189 * image[h][w].rgbtBlue;
            float sepiaGreen = .349 * image[h][w].rgbtRed + .686 * image[h][w].rgbtGreen + .168 * image[h][w].rgbtBlue;
            float sepiaBlue = .272 * image[h][w].rgbtRed + .534 * image[h][w].rgbtGreen + .131 * image[h][w].rgbtBlue;
            // capped at 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            };
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            };
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            };
            image[h][w].rgbtRed = round(sepiaRed);
            image[h][w].rgbtGreen = round(sepiaGreen);
            image[h][w].rgbtBlue = round(sepiaBlue);
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
