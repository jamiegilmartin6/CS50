#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float b = image[i][j].rgbtBlue;
            float g = image[i][j].rgbtGreen;
            float r = image[i][j].rgbtRed;

            float avg = round((b + g + r)/(3));
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //int half = (width)/(2);
    for (int i = 0; i < height; i++)
    {
        if (width % 2 == 0)
        {
            for (int j = 0; j < (width)/(2); j++)
            {
                RGBTRIPLE temp[height][width];
                temp[i][j] = image[i][j];
                image[i][j] = image[i][width - 1 - j];
                image[i][width - 1 - j] = temp[i][j];
            }
        }
        else
        {
            for (int j = 0; j < (width - 1) / (2); j++)
            {
                RGBTRIPLE temp[height][width];
                temp[i][j] = image[i][j];
                image[i][j] = image[i][width - 1 - j];
                image[i][width - 1 - j] = temp[i][j];
            }
        }


    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i<height; i++)
    {
        for (int j = 0; j<width; j++)
        {
            float blue = 0;
            float green = 0;
            float red = 0;
            float d = 0;

            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    if ((i + x < 0)||(i + x > height - 1))
                    {
                        continue;
                    }
                    if ((j + y < 0)||(j + y > width - 1))
                    {
                        continue;
                    }

                        d = d + 1;
                        blue = blue + image[i + x][j + y].rgbtBlue;
                        green = green + image[i + x][j + y].rgbtGreen;
                        red = red + image[i + x][j + y].rgbtRed;

                        //float avgb = round((blue)/(d));
                        //float avgg = round((green)/(d));
                        //float avgr = round((red)/(d));

                }
            }
            temp[i][j].rgbtBlue = round(blue / d);
            temp[i][j].rgbtGreen = round(green / d);
            temp[i][j].rgbtRed = round(red / d);
        }


    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    int gx[3][3] = {{-1, 0, 1},{-2, 0, 2},{-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1},{0, 0, 0},{1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gxblue = 0;
            int gyblue = 0;
            int gxgreen = 0;
            int gygreen = 0;
            int gxred = 0;
            int gyred = 0;

            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {

                    if ((i + x < 0)||(i + x > height - 1))
                    {
                        continue;
                    }
                    if ((j + y < 0)||(j + y > width - 1))
                    {
                        continue;
                    }

                    gxblue = gxblue + (image[i+x][j+y].rgbtBlue * gx[x+1][y+1]);
                    gxgreen = gxgreen + (image[i+x][j+y].rgbtGreen * gx[x+1][y+1]);
                    gxred = gxred + (image[i+x][j+y].rgbtRed * gx[x+1][y+1]);
                    gyblue = gyblue + (image[i+x][j+y].rgbtBlue * gy[x+1][y+1]);
                    gygreen = gygreen + (image[i+x][j+y].rgbtGreen * gy[x+1][y+1]);
                    gyred = gyred + (image[i+x][j+y].rgbtRed * gy[x+1][y+1]);

                }
            }
            int blue = round(sqrt(gxblue * gxblue + gyblue * gyblue));
            int green = round(sqrt(gxgreen * gxgreen + gygreen * gygreen));
            int red = round(sqrt(gxred * gxred + gyred * gyred));

            temp[i][j].rgbtBlue = (blue > 255) ? 255 : blue;
            temp[i][j].rgbtGreen = (green > 255) ? 255 : green;
            temp[i][j].rgbtRed = (red > 255) ? 255 : red;

        }

    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }
    return;
}
