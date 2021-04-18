/*************************************************
PROGRAM NAME : 6-1.c
AUTHER : Masatsugu Kitadai
DATE :
Think a Bit , Code a Bit , Test a Bit
**************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define number 10000
#define sigma 20e-6
#define myu 70e-6
#define split 10e-6
#define n 15

double random_1[number];
double random_2[number];
double nd[number];
double z[numbe];

int histgram[n];

FILE *output_file;                                // pointer for output file
const char *output_data_file = "output_data.dat"; // name of output file

/********************MAIN**************************/
double main()

{
    int i, j;
    double PI;
    PI = 4.0 * atan(1.0);
    // printf("RAND_MAX = %d\n", RAND_MAX);

    // generate random numbers

    for (i = 0; i < number; i++)
    {
        random_1[i] = (double)rand() / (RAND_MAX + 1.0);
        random_2[i] = (double)rand() / (RAND_MAX + 1.0);

        // printf("[%d] = %lf %lf\n", i, random_1[i], random_2[i]);
    }

    // create normal distribution

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

    // calculate Average and Distribution

    double sum_1, sum_2, average, deviation;

    // 1. Average

    sum_1 = 0;

    for (i = 0; i < number; i++)
    {
        sum_1 = sum_1 + z[i];
    }

    average = sum_1 / number;

    // 2. Distribution

    sum_2 = 0;

    for (i = 0; i < number; i++)
    {
        sum_2 = sum_2 + (z[i] - average) * (z[i] - average);
    }

    deviation = sqrt(sum_2 / number);

    // output　calculation results

    printf("Avrage\t\t= %lf\n", average);
    printf("Deviation\t= %lf\n", deviation);

    // Sort

    double tmp;

    for (i = 0; i < number; ++i)
    {
        for (j = i + 1; j < number; ++j)
        {
            if (z[i] > z[j])
            {
                tmp = z[i];
                z[i] = z[j];
                z[j] = tmp;
            }
        }
    }

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

    // wirte output_data file

    output_file = fopen(output_data_file, "w");

    for (i = 0; i < n; i++)
    {
        fprintf(output_file, "%d\t %d\n", i * 10, histgram[i]);
    }

    fclose(output_file);

    return (0);
}