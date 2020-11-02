// My solution for the filter problem - specifically the helpers.c file
//An algorithms that take an 2D array (an image) made out of pixels (their RGB values) as an input
//And outputs the same image with the given "filter on"

#include "helpers.h"
#include <stdio.h>
#include <math.h>



// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int blue;
    int green;
    int red;
    int average;

    //Go through every pixel (every item in the image array)
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            //Find out the what the values of red, greed and blue are in the pixel
            blue = image[i][k].rgbtBlue;
            green = image[i][k].rgbtGreen;
            red = image[i][k].rgbtRed;
            //Find out their rounded up average value
            average = round(((float)(blue + green + red)) / 3);

            //Assign this value to the pixel's red,green and blue values
            image[i][k].rgbtBlue = average;
            image[i][k].rgbtGreen = average;
            image[i][k].rgbtRed = average;


        }

    }
    return;
}




// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width / 2; k++)
        {
            //Switch the current pixel with the pixel opposite of him in the same row
            temp = image[i][k];
            image[i][k] = image[i][width - 1 - k ];
            image[i][width - 1 - k] = temp;
        }
    }
    return;
}



//Part of the blur function
void find_averages(int i, int k, int height, int width, RGBTRIPLE image_copy[height][width], int *avrg_blue, int *avrg_green,
                   int *avrg_red)
{
    int pixel_count = 0;
    int blue = 0;
    int red = 0;
    int green = 0;

    //every pixel within 1 row 1 column radius
    for (int a = i - 1; a < i + 2; a++)
    {
        for (int b = k - 1; b < k + 2; b++)
        {
            //Corner cases
            if (a >= height || a < 0 || b >= width || b < 0)
            {
                continue;
            }

            //add the separate color values all together
            pixel_count++;
            blue += image_copy[a][b].rgbtBlue;
            green += image_copy[a][b].rgbtGreen;
            red += image_copy[a][b].rgbtRed;

        }
    }

    //divide the separate color values that you added all together with the number of pixel that are in the "pixel box"(around the original pixel in blur func)
    //make an average value out of them
    *avrg_blue = round((float)blue / pixel_count);
    *avrg_green = round((float)green / pixel_count);
    *avrg_red = round((float)red / pixel_count);

    return;
}


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int avrg_blue;
    int avrg_green;
    int avrg_red;

    //Make a copy of the original image 2D array
    RGBTRIPLE image_copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            image_copy[i][k] = image[i][k];
        }
    }

    //For every pixel
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            //Find and average value of blue, green and red in his 3x3 pixel box
            find_averages(i, k, height, width, image_copy, &avrg_blue, &avrg_green, &avrg_red);

            //Then assing these values to the actual pixel (the one in the middle of the pixel box)
            image[i][k].rgbtBlue = avrg_blue;
            image[i][k].rgbtGreen = avrg_green;
            image[i][k].rgbtRed = avrg_red;
        }
    }


    return;
}



//Part of the edge function
void find_Sobel_algorithm_values(int i, int k, int height, int width, RGBTRIPLE image_copy[height][width], int *blue_value,
                                 int *green_value, int *red_value)
{
    int Gx_blue = 0;
    int Gx_red = 0;
    int Gx_green = 0;

    int Gy_blue = 0;
    int Gy_green = 0;
    int Gy_red = 0;

    int Gx_kernel[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int Gy_kernel[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};

    //every pixel within 1 row 1 column radius
    for (int a = i - 1, count1 = 0; a < i + 2; a++, count1++)
    {
        for (int b = k - 1, count2 = 0; b < k + 2; b++, count2++)
        {
            //Corner cases - they behave like zeros (Ox000000) (black pixels)
            if (a >= height || a < 0 || b >= width || b < 0)
            {
                //So they don't change the Gx(y)_*color* value
                continue;
            }

            //add the values (of the pixels in the pixel box) all together - Gx kernel
            Gx_blue += (image_copy[a][b].rgbtBlue) * Gx_kernel[(count1 * 3) + count2];
            Gx_green += (image_copy[a][b].rgbtGreen) * Gx_kernel[(count1 * 3) + count2];
            Gx_red += (image_copy[a][b].rgbtRed) * Gx_kernel[(count1 * 3) + count2];

            //add the values (of the pixels in the pixel box) all together - Gy kernel
            Gy_blue += (image_copy[a][b].rgbtBlue) * Gy_kernel[(count1 * 3) + count2];
            Gy_green += (image_copy[a][b].rgbtGreen) * Gy_kernel[(count1 * 3) + count2];
            Gy_red += (image_copy[a][b].rgbtRed) * Gy_kernel[(count1 * 3) + count2];

        }
    }



    //Square the value of Gx and Gy of the individual color and add them all togerher
    //Then your final value for the given color is the rounded of square root of the sum explained above
    *blue_value = round(sqrt((float)(Gx_blue * Gx_blue + Gy_blue * Gy_blue)));
    *green_value = round(sqrt((float)(Gx_green * Gx_green + Gy_green * Gy_green)));
    *red_value = round(sqrt((float)(Gx_red * Gx_red + Gy_red * Gy_red)));

    //cap the values at 255
    if (*blue_value > 255)
    {
        *blue_value = 255;
    }
    if (*green_value > 255)
    {
        *green_value = 255;
    }
    if (*red_value > 255)
    {
        *red_value = 255;
    }

    return;
}


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int blue_value;
    int green_value;
    int red_value;

    //Make a copy of the original image 2D array
    RGBTRIPLE image_copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            image_copy[i][k] = image[i][k];
        }
    }

    //For every pixel
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            //Find the Sobel algorithm values of blue, green and red of this individial pixel[i][k] in his 3x3 pixel box
            find_Sobel_algorithm_values(i, k, height, width, image_copy, &blue_value, &green_value, &red_value);

            //Then assing these values to the actual pixel (the one in the middle of the pixel box)
            image[i][k].rgbtBlue = blue_value;
            image[i][k].rgbtGreen = green_value;
            image[i][k].rgbtRed = red_value;
        }
    }


    return;
}
