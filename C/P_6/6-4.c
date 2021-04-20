/*************************************************
PROGRAM NAME : 6-4.c
AUTHER : Masatsugu Kitadai
DATE :
Think a Bit , Code a Bit , Test a Bit
**************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>
#include <time.h>

#define num 100
#define myu 70
#define sigma 20
#define x_grid 1024
#define y_grid 1024

double size;
int image_in[x_grid][y_grid];
int image_out[x_grid][y_grid];
unsigned int rand_max = RAND_MAX;

const char *input_image = "6-3.bmp";
const char *output_image = "particle.bmp";
unsigned char header_buf[1078];
FILE *infile;
FILE *outfile;

/********************MAIN**************************/
double main()
{
    srand(time(NULL));

    int i, j, k;

    // give random size

    double nd;
    double rand_1;
    double rand_2;
    double PI;
    PI = 4.0 * atan(1.0);

    // image array

    double A, r;
    int x, y, brightness;

    for (k = 0; k < num; k++)
    {
        x = fabs(((double)rand() / (rand_max + 1)) * 1024);
        y = fabs(((double)rand() / (rand_max + 1)) * 1024);
        brightness = 128 + fabs(((double)rand() / (rand_max + 1)) * 127);
        rand_1 = fabs((double)rand() / (rand_max + 1));
        rand_2 = fabs((double)rand() / (rand_max + 1));
        nd = sqrt(-2.0 * log(rand_1)) * cos(2.0 * PI * rand_2);
        size = myu + sigma * nd;
        r = size / 2.0;

        image_out[x][y] = brightness;
        printf("image_out[%d][%d]\t=\t%d\n", x, y, image_out[x][y]);

        for (i = 0; i < y_grid; i++)
        {
            for (j = 0; j < x_grid; j++)
            {
                A = ((j - x) * (j - x) + (i - y) * (i - y)) / (2.0 * r * r);
                image_in[i][j] = brightness * exp(-1.0 * A);

                if (image_in[i][j] > image_out[i][j])
                {
                    image_out[i][j] = image_in[i][j];

                    if (image_out[i][j] > 255.0)
                    {
                        image_out[i][j] = 255;
                    }
                }
                // printf("%d\t%d\t%d\n", i, j, image_out[i][j]);
            }
        }
    }

    infile = fopen(input_image, "rb");
    if (infile == NULL)
    {
        printf(" No such an input_image! \n ");
        return (0);
    }
    fread(header_buf, sizeof(unsigned char), 1078, infile); // Read Header
    fclose(infile);

    // Write filtered image data
    outfile = fopen(output_image, "wb");
    fwrite(header_buf, sizeof(unsigned char), 1078, outfile); // Write Header
    fwrite(image_out, sizeof(image_out), 1, outfile);         // Write 8 bit image intensity
    fclose(outfile);

    return (0);
}