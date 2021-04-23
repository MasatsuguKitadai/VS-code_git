

/********************************************************************
PROGRAM NAME : image of particle
AUTHER : Shunya Aburatani
DATE : 2021 03 29
*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>
const char *output_image = "1000Particles_after.bmp";
const char *out_file_dir = "00graph";
const char *input_image = "6-3.bmp";
#define height 1024
#define width 1024
unsigned char header_buf[1078];
unsigned char image_in[height][width];
unsigned char image_out[height][width];
const int number = 1000;
const int light_intensity_min = 128;
const int light_intensity_max = 255;
const int average = 70;
const int standard_deviation = 20;
const double PI = 4 * atan(1.0);
FILE *infile;
FILE *outfile;
/********************************* MAIN *********************************/
double main()
{
    int i, j, k, m, n, p, q;
    int u[number]; //x座標
    int v[number]; //y座標
    //座標決め
    for (i = 0; i < number; i++)
    {
        u[i] = ((int)rand() % (width + 1));
        v[i] = ((int)rand() % (width + 1));
        printf("%d__%d\n", u[i], v[i]);
    }
    //box-Muller法(半径)
    double U1[number];     //一様乱数
    double U2[number];     //一様乱数
    double radius[number]; //粒子半径
    for (i = 0; i < number; i++)
    {
        U1[i] = ((double)rand() / (RAND_MAX));
        U2[i] = ((double)rand() / (RAND_MAX));
        radius[i] = average + standard_deviation *
                                  cos(2 * PI * U2[i]) * sqrt(-2 * log(U1[i]));
    }
    //ピーク光強度設定
    int copy[number]; //ピーク光強度
    unsigned char intensity[number];
    for (int i = 0; i < number; i++)
    {
        //128~255の乱数
        copy[i] = ((int)rand() % (light_intensity_max - light_intensity_min + 1) + light_intensity_min);
        intensity[i] = copy[i];
        printf("%d\n", intensity[i]);
    }
    //file読み込み(1024*1024,光度0)
    infile = fopen(input_image, "rb");
    if (infile == NULL)
    {
        printf("No such an input pmage!!\n");
        exit(0);
    }
    fread(header_buf, sizeof(unsigned char), 1078, infile);
    fread(image_in, sizeof(image_in), 1, infile);
    fclose(infile);
    int sum = 0;
    double abc;
    //粒子の配置
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            sum = 0;
            for (k = 0; k < number; k++)
            {
                abc = intensity[k] * exp(-100 * ((i - v[k]) * (i - v[k]) + (j - u[k]) * (j - u[k])) / (2 * radius[k] * (radius[k])));
                if (sum <= abc)
                {
                    sum = abc;
                }
            }
            if (255 < sum)
            {
                sum = 255;
            }
            else if (sum < 0)
            {
                sum = 0;
            }
            image_out[i][j] = image_in[i][j] + sum;
        }
    }
    printf("finish");
    // Write filtered image data
    outfile = fopen(output_image, "wb");
    fwrite(header_buf, sizeof(unsigned char), 1078, outfile); // Write Header
    fwrite(image_out, sizeof(image_out), 1, outfile);         // Write 8 bit image intensity
    fclose(outfile);
    return (0);
}
