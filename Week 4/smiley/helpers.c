#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // RGB of Black: [0, 0, 0]
            if (image[h][w].rgbtRed == 0 && image[h][w].rgbtGreen == 0 && image[h][w].rgbtBlue == 0)
            {
                // RGB of Amber: [255, 191, 0]
                image[h][w].rgbtRed = 255;
                image[h][w].rgbtGreen = 191;
                image[h][w].rgbtBlue = 0;
            };
        };
    };
}
