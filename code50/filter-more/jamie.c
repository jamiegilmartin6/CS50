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
                int b = image[i][j].rgbtBlue;
                int g = image[i][j].rgbtGreen;
                int r = image[i][j].rgbtRed;

                image[i][j].rgbtBlue = image[i][width-j].rgbtBlue;
                image[i][j].rgbtGreen = image[i][width-j].rgbtGreen;
                image[i][j].rgbtRed = image[i][width-j].rgbtRed;

                image[i][width-j].rgbtBlue = b;
                image[i][width-j].rgbtGreen = g;
                image[i][width-j].rgbtRed = r;
            }
        }
        else
        {
            for (int j = 0; j < (width - 1) / (2); j++)
            {
                int b = image[i][j].rgbtBlue;
                int g = image[i][j].rgbtGreen;
                int r = image[i][j].rgbtRed;

                image[i][j].rgbtBlue = image[i][width-j].rgbtBlue;
                image[i][j].rgbtGreen = image[i][width-j].rgbtGreen;
                image[i][j].rgbtRed = image[i][width-j].rgbtRed;

                image[i][width-j].rgbtBlue = b;
                image[i][width-j].rgbtGreen = g;
                image[i][width-j].rgbtRed = r;
            }
        }


    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i<height; i++)
    {
        for (int j = 0; j<width; j++)
        {
            int blue = 0;
            int green = 0;
            int red = 0;
            int n = 0;
            int d = 0;
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
                        blue = blue + image[x][y].rgbtBlue;
                        green = green + image[x][y].rgbtGreen;
                        red = red + image[x][y].rgbtRed;

                        int avgb = (blue)/(d);
                        int avgg = (green)/(d);
                        int avgr = (red)/(d);

                        image[i][j].rgbtBlue = avgb;
                        image[i][j].rgbtGreen = avgg;
                        image[i][j].rgbtRed = avgr;

                }
            }
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    int gx[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
    int gy[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};

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
                    gyred = gxred + (image[i+x][j+y].rgbtRed * gy[x+1][y+1]);

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
