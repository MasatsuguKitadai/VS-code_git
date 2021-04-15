/*************************************************
PROGRAM NAME : filtered_face . cpp
AUTHER : Yohsuke Tanaka
DATE :2014.12.18
Think a Bit , Code a Bit , Test a Bit
**************************************************/
#include <stdio.h>
#include <stdlib.h>
#define width 960
#define height 540
const int thred = 120;
const char *input_image = "photo_imagej.bmp";              // name of input
const char *output_image = "filtered_photo_Laplacian.bmp"; // name of output file
const char *output_image_test = "photo_test.bmp";
unsigned char header_buf[1078];
unsigned char image_in[width][height];
unsigned char image_out[width][height];
unsigned char image_out_test[width][height];
double Laplacian[width][height];
FILE *infile;
FILE *outfile;

// 0 < x < width 0 < y <  height
double f1(unsigned char A1, unsigned char A2, unsigned char A3)
{
    double f1[width][height];
    f1[width][height] = A1 - 2 * A2 + A3;
    return f1[width][height];
}

// x = 0 or y = 0
double f2(unsigned char B1, unsigned char B2, unsigned char B3, unsigned char B4)
{
    double f2[width][height];
    f2[width][height] = -2 * B1 + 5 * B2 - 4 * B3 + B4;
    return f2[width][height];
}

// x = width or y = height
double f3(unsigned char C1, unsigned char C2, unsigned char C3, unsigned char C4)
{
    double f3[width][height];
    f3[width][height] = 2 * C1 - 5 * C2 + 4 * C3 - C4;
    return f3[width][height];
}

/********************MAIN**************************/
int main()
{
    int i, j;
    // Read image data
    infile = fopen(input_image, "rb");
    if (infile == NULL)
    {
        printf(" No such an input_image! \n ");
        return (0);
    }
    fread(header_buf, sizeof(unsigned char), 1078, infile); // Read Header
    fread(image_in, sizeof(image_in), 1, infile);           // Read 8 bit image intensity
    fclose(infile);

    /*
    // check the programs
    for (j = 0; j < height; j++)
    {
        for (i = 0; i < width; i++)
        {
            printf("image_in[%d][%d] = %d\n", i, j, image_in[i][j]);
        }
    }
*/

    // Laplacian Filter

    for (j = 0; j < height; j++)
    {
        for (i = 0; i < width; i++)
        {
            Laplacian[i][j] = 0;
        }
    }

    // case1: 0<x<width, 0<y<height

    for (i = 1; i < width - 1; i++)
    {
        for (j = 1; j < height - 1; j++)
        {
            Laplacian[i][j] = -4 * image_in[i][j] + image_in[i + 1][j] + image_in[i][j + 1] + image_in[i - 1][j] + image_in[i][j - 1];
        }
    }

    // case2: x=0, 0<y<height

    i = 0;
    for (j = 1; j < height - 1; j++)
    {
        Laplacian[i][j] = f2(image_in[i][j], image_in[i + 1][j], image_in[i + 2][j], image_in[i + 3][j]) + f1(image_in[i][j + 1], image_in[i][j], image_in[i][j - 1]);
    }

    // case3: x=width, 0<y<height

    i = width - 1;
    for (j = 1; j < height - 1; j++)
    {
        Laplacian[i][j] = f3(image_in[i][j], image_in[i - 1][j], image_in[i - 2][j], image_in[i - 3][j]) + f1(image_in[i][j + 1], image_in[i][j], image_in[i][j - 1]);
    }

    // case4: 0<x<width, y=0

    j = 0;
    for (i = 1; i < width - 1; i++)
    {
        Laplacian[i][j] = f1(image_in[i + 1][j], image_in[i][j], image_in[i - 1][j]) + f2(image_in[i][j], image_in[i][j + 1], image_in[i][j + 2], image_in[i][j + 3]);
    }

    // case5: 0<x<width, y=height

    j = height - 1;
    for (i = 1; i < width - 1; i++)
    {
        Laplacian[i][j] = 128 + f1(image_in[i + 1][j], image_in[i][j], image_in[i - 1][j]) + f3(image_in[i][j], image_in[i][j - 1], image_in[i][j - 2], image_in[i][j - 3]);
    }

    // case6: x=0, y=0

    i = 0;
    j = 0;

    Laplacian[i][j] = f2(image_in[i][j], image_in[i + 1][j], image_in[i + 2][j], image_in[i + 3][j]) + f2(image_in[i][j], image_in[i][j + 1], image_in[i][j + 2], image_in[i][j + 3]);

    // case7: x=width, y=0

    i = width - 1;
    j = 0;

    Laplacian[i][j] = f3(image_in[i][j], image_in[i - 1][j], image_in[i - 2][j], image_in[i - 3][j]) + f2(image_in[i][j], image_in[i][j + 1], image_in[i][j + 2], image_in[i][j + 3]);

    // case8: x=0, y=height

    i = 0;
    j = height - 1;

    Laplacian[i][j] = f2(image_in[i][j], image_in[i + 1][j], image_in[i + 2][j], image_in[i + 3][j]) + f3(image_in[i][j], image_in[i][j - 1], image_in[i][j - 2], image_in[i][j - 3]);

    // case9 : x=width, y=height

    i = width - 1;
    j = height - 1;

    Laplacian[i][j] = f3(image_in[i][j], image_in[i - 1][j], image_in[i - 2][j], image_in[i - 3][j]) + f3(image_in[i][j], image_in[i][j - 1], image_in[i][j - 2], image_in[i][j - 3]);

    for (j = 0; j < height; j++)
    {
        for (i = 0; i < width; i++)
        {
            // printf("Laplacian[%d][%d] = %lf\n", i, j, Laplacian[i][j]);

            if (Laplacian[i][j] > 255.0)
            {
                image_out[i][j] = 255;
            }
            else if (Laplacian[i][j] < 0.0)
            {
                image_out[i][j] = 0;
            }
            else
            {
                image_out[i][j] = Laplacian[i][j];
            }

            printf("Laplacian[%d][%d] = %lf\n", i, j, Laplacian[i][j]);
            printf("image_out[%d][%d] = %d\n", i, j, image_out[i][j]);
        }
    }
    // Write filtered image data
    outfile = fopen(output_image, "wb");
    fwrite(header_buf, sizeof(unsigned char), 1078, outfile); // Write Header
    fwrite(image_out, sizeof(image_out), 1, outfile);         // Write 8 bit image intensity
    fclose(outfile);

    // Check image data

    outfile = fopen(output_image_test, "wb");
    fwrite(header_buf, sizeof(unsigned char), 1078, outfile); // Write Header
    fwrite(image_in, sizeof(image_in), 1, outfile);           // Write 8 bit image intensity
    fclose(outfile);

    return (0);
}