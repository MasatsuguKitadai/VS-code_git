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
const int thred = 128;
const char *input_image = "photo-imagej.bmp";    // name of input file
const char *output_image = "filtered_photo.bmp"; // name of output file
unsigned char header_buf[1078];
unsigned char image_in[width][height];
unsigned char image_out[width][height];
FILE *infile;
FILE *outfile;
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
    for (j = 0; j < height; j++)
    {
        for (i = 0; i < width; i++)
        {
            // printf("image_in[%d][%d] = %d\n", i, j, image_in[i][j]);
            if (image_in[i][j] > thred)
            {
                image_out[i][j] = 255;
            }
            else
            {
                image_out[i][j] = 0;
            }
        }
    }
    // Write filtered image data
    outfile = fopen(output_image, "wb");
    fwrite(header_buf, sizeof(unsigned char), 1078, outfile); // Write Header
    fwrite(image_out, sizeof(image_out), 1, outfile);         // Write 8 bit image intensity
    fclose(outfile);
    return (0);
}