#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int blue = image[h][w].rgbtBlue;
            int green = image[h][w].rgbtGreen;
            int red = image[h][w].rgbtRed;
            int average = round(((float) blue + green + red)/3);
            image[h][w].rgbtBlue = average;
            image[h][w].rgbtGreen = average;
            image[h][w].rgbtRed = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w <= (width - 1)/2; w++)
        {
            RGBTRIPLE temp = image[h][w];
            image[h][w] = image[h][width - 1 - w];
            image[h][width - 1 - w] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imageCopy[height][width];
    int totalBlue = 0, totalGreen = 0, totalRed = 0, count = 0;

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            imageCopy[h][w] = image[h][w];
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            for (int a = h - 1; a <= h + 1; a++)
            {
                if (a < 0 || a > (height - 1))
                {
                    continue;
                }
                for (int k = w - 1; k <= w + 1; k++)
                {
                    if (k < 0 || k > (width - 1))
                    {
                        continue;
                    }
                    count++;
                    totalBlue += imageCopy[a][k].rgbtBlue;
                    totalGreen += imageCopy[a][k].rgbtGreen;
                    totalRed += imageCopy[a][k].rgbtRed;
                }
            }
            image[h][w].rgbtBlue = round(((float) totalBlue)/count);
            image[h][w].rgbtGreen = round(((float) totalGreen)/count);
            image[h][w].rgbtRed = round(((float) totalRed)/count);
            totalBlue = 0, totalGreen = 0, totalRed = 0, count = 0;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int GxBlue = 0, GxGreen = 0, GxRed = 0, count = 0;
    int GyBlue = 0, GyGreen = 0, GyRed = 0, total = 0;
    int Gx[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int Gy[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    RGBTRIPLE imageCopy[height][width];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            imageCopy[h][w] = image[h][w];
        }
    }
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            for (int a = h - 1; a <= h+1; a++)
            {
                if (a < 0 || a > (height - 1))
                {
                    count += 3;
                    continue;
                }
                for (int k = w - 1; k <= w + 1; k++)
                {
                    if (k < 0 || k > (width - 1))
                    {
                        count++;
                        continue;
                    }
                    GxBlue += imageCopy[a][k].rgbtBlue * Gx[count];
                    GxGreen += imageCopy[a][k].rgbtGreen * Gx[count];
                    GxRed += imageCopy[a][k].rgbtRed * Gx[count];
                    GyBlue += imageCopy[a][k].rgbtBlue * Gy[count];
                    GyGreen += imageCopy[a][k].rgbtGreen * Gy[count];
                    GyRed += imageCopy[a][k].rgbtRed * Gy[count];
                    count++;
                }
            }

            total = round(sqrt((float) GxBlue * GxBlue + GyBlue * GyBlue));
            image[h][w].rgbtBlue = (total < 255) ? total : 255;
            total = round(sqrt((float) GxGreen * GxGreen + GyGreen * GyGreen));
            image[h][w].rgbtGreen = (total < 255) ? total : 255;
            total = round(sqrt((float) GxRed * GxRed + GyRed * GyRed));
            image[h][w].rgbtRed = (total < 255) ? total : 255;


            GxBlue = 0, GxGreen = 0, GxRed = 0, count = 0;
            GyBlue = 0, GyGreen = 0, GyRed = 0; total = 0;
        }
    }
    return;
}
