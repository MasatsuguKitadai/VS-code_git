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
double image_in;
int image_out[y_grid][x_grid];
int image_tmp;
unsigned int rand_max = RAND_MAX;
int x[num];
int y[num];
int brightness[num];
double r[num];

const char *input_image = "6-3.bmp";
const char *output_image = "particle.bmp";
unsigned char header_buf[1078];
FILE *infile;
FILE *outfile;

/********************MAIN**************************/
double main()
{
    infile = fopen(input_image, "rb");
    if (infile == NULL)
    {
        printf(" No such an input_image! \n ");
        return (0);
    }

    fread(header_buf, sizeof(unsigned char), 1078, infile); // Read Header
    fclose(infile);

    srand(time(NULL));

    int i, j, k;

    // give random size

    double nd, size;
    double rand_1;
    double rand_2;
    double PI;
    PI = 4.0 * atan(1.0);

    // image array

    int r;
    int x, y, brightness;

    for (i = 0; i < y_grid; i++)
    {
        for (j = 0; j < x_grid; j++)
        {
            image_out[i][j] = 0;
        }
    }

    for (k = 0; k < num; k++)
    {
        x = fabs(((double)rand() / (rand_max + 1)) * 1024);
        y = fabs(((double)rand() / (rand_max + 1)) * 1024);
        brightness = rand() % 128 + 128;
        rand_1 = fabs((double)rand() / (rand_max + 1));
        rand_2 = fabs((double)rand() / (rand_max + 1));
        nd = sqrt(-2.0 * log(rand_1)) * cos(2.0 * PI * rand_2);
        size = myu + sigma * nd;
        r[i] = size / 2.0;
    }

    for (i = 0; i < num; i++)
    {
        printf("%d\t%d\t%d\t%lf\n", x[i], y[i], brightness[i], r[i]);
    }

    // printf("image_out[%d][%d]\t=\t%d\n", x, y, image_out[x][y]);

    for (i = 0; i < y_grid; i++)
    {
        for (j = 0; j < x_grid; j++)
        {
            image_tmp = 0;

            for (k = 0; k < num; k++)
            {

                image_in = brightness[k] * exp(-100 * ((j - x[k]) * (j - x[k]) + (i - y[k]) * (i - y[k])) / (2 * r[k] * r[k]));

                if (image_tmp < image_in)
                {
                    image_tmp = image_in;
                }
            }
            if (image_tmp > 255.0)
            {
                image_tmp = 255;
            }
            else if (image_tmp < 0.0)
            {
                image_tmp = 0;
            }

            image_out[i][j] = image_tmp;
            // printf("%d\n", image_tmp);
        }
    }

    // Write filtered image data
    outfile = fopen(output_image, "wb");
    fwrite(header_buf, sizeof(unsigned char), 1078, outfile); // Write Header
    fwrite(image_out, sizeof(image_out), 1, outfile);         // Write 8 bit image intensity
    fclose(outfile);

    return (0);
}