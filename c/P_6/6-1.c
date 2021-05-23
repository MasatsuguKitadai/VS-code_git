/*************************************************
PROGRAM NAME : 6-1.c
AUTHER : Masatsugu Kitadai
DATE :
Think a Bit , Code a Bit , Test a Bit
**************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>
#include <time.h>
#define number 10000
#define sigma 20
#define myu 70
#define split 10
#define n 15

double random_1[number];
double random_2[number];
double nd[number];
double z[number];

int histgram[n];

FILE *output_file_01; // pointer for output file
FILE *output_file_02;
const char *output_data_file_01 = "output/output_data_histgram.dat"; // name of output file
const char *output_data_file_02 = "output/output_data.dat";
const char *output_file_dir = "output";

/********************MAIN**************************/
double main()

{
    int i, j;
    double PI;
    PI = 4.0 * atan(1.0);

    // generate random numbers

    srand(time(NULL));
    int rand_max = RAND_MAX;

    for (i = 0; i < number; i++)
    {
        random_1[i] = fabs((double)rand() / (rand_max + 1));
        random_2[i] = fabs((double)rand() / (rand_max + 1));

        printf("[%d] = %lf %lf\n", i, random_1[i], random_2[i]);
    }

    // create normal variance

    for (i = 0; i < number; i++)
    {
        nd[i] = sqrt(-2.0 * log(random_1[i])) * cos(2.0 * PI * random_2[i]);

        // printf("[%d] = %lf\n", i, ND[i]);
    }

    // linear transformation

    for (i = 0; i < number; i++)
    {
        z[i] = myu + sigma * nd[i];

        // printf("[%d]\t= %lf\n", i, z[i]);
    }

    // wirte output_data file

    output_file_02 = fopen(output_data_file_02, "w");

    for (i = 0; i < number; i++)
    {
        fprintf(output_file_02, "%d\t %lf\n", i, z[i]);
    }

    fclose(output_file_02);
    // calculate Average and Variance

    double sum_1, sum_2, average, variance;

    // 1. Average

    sum_1 = 0;

    for (i = 0; i < number; i++)
    {
        sum_1 = sum_1 + z[i];
    }

    average = sum_1 / number;

    // 2. Variance

    sum_2 = 0;

    for (i = 0; i < number; i++)
    {
        sum_2 = sum_2 + (z[i] - average) * (z[i] - average);
    }

    variance = sqrt(sum_2 / number);

    // output　calculation results

    printf("Avrage\t\t= %lf\n", average);
    printf("Variance\t= %lf\n", variance);

    // classification

    int rank;

    for (i = 0; i < n; i++)
    {
        histgram[i] = 0;
    }

    for (i = 0; i < number; i++)
    {
        rank = (int)(z[i] / split);
        histgram[rank] = histgram[rank] + 1;
        // printf("rank[%d] = %d\n", i, rank);
    }

    /*
    for (i = 0; i < n; i++)
    {
        printf("histgram[%d] = %d\n", i, histgram[i]);
    }
*/

    // create the new directries

    mode_t mode = S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;
    mkdir(output_file_dir, mode);

    // wirte output_data file for histgram

    output_file_01 = fopen(output_data_file_01, "w");

    for (i = 0; i < n; i++)
    {
        fprintf(output_file_01, "%d %d\n", i * 10, histgram[i]);
    }

    fclose(output_file_01);

    return (0);
}