/******************************************************************************
PROGRAM NAME:sq-file-input.cpp
AUTHER: Masatsugu Kitadai
DATE: 2020/4/4
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define CH 8
#define data_long 60000
const char *read_file_01 = "235.CSV";
const char *read_file_02 = "C_lab_ono.dat";
const char *read_file_03 = "C_v_p_1k_ono.dat";
const char *output_data_file = "f_SPL_8ch.dat";
double wave_value[data_long][CH];
double part[CH];
double sum[CH];
double Rms[CH];
double A[CH];
double SPL[CH];
char date[20];
int omit = 57; // Number of lines to skip
char buf[128]; //
FILE *input_file01;
FILE *input_file02;
FILE *input_file03;
FILE *output_file;
/*********************************   MAIN   *********************************/
double main()
{
    int i, j, tim;
    double ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8;

    // Array initialization
    for (i = 0; i < data_long; i++)
    {
        for (j = 0; j < CH; j++)
        {
            wave_value[i][j] = 0;
        }
    }

    input_file01 = fopen(read_file_01, "r");
    if (read_file_01 == NULL)
    {
        printf("I can't open the file!\n");
        exit(0);
    }

    // Transrate the point of pointer
    for (i = 0; i < omit; i++)
    {
        fgets(buf, sizeof(buf), input_file01);
    }

    for (i = 0; i < data_long; i++)
    {
        fscanf(input_file01, "%[^,], %d, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf", date, &tim, &ch1, &ch2, &ch3, &ch4, &ch5, &ch6, &ch7, &ch8);
        wave_value[i][0] = ch1;
        wave_value[i][1] = ch2;
        wave_value[i][2] = ch3;
        wave_value[i][3] = ch4;
        wave_value[i][4] = ch5;
        wave_value[i][5] = ch6;
        wave_value[i][6] = ch7;
        wave_value[i][7] = ch8;

        // check the programs
        // printf("%s , %d , %lf , %lf , %lf , %lf , %lf , %lf , %lf , %lf", date, tim, ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8);
    }
    // printf("\n");

    fclose(input_file01);

    // Simpson Law

    double f_Hz;
    f_Hz = 20.0E-6;

    for (j = 0; j < CH; j++)
    {
        part[j] = 0;
        sum[j] = 0;

        for (i = 0; i < data_long; i = i + 2)
        {
            part[j] = f_Hz / 3.0 * (wave_value[i][j] * wave_value[i][j] + 4 * wave_value[i + 1][j] * wave_value[i + 1][j] + wave_value[i + 2][j] * wave_value[i + 2][j]);
            sum[j] = (sum[j] + part[j]);

            //printf("wave_value[%d][%d]=%lf\t", i, j, wave_value[i][j]);
            //printf("part[%d]=%lf\tsum[%d]=%lf\n", j, part[j], j, sum[j]);
        }

        // printf("sum[%d][%d]=%lf\n", i, j, sum[j]);
    }

    for (i = 0; i < CH; i++)
    {
        Rms[i] = 1.0 / (data_long * f_Hz) * sum[i];
        printf("Rms[%d]=%lf\n", i, Rms[i]);
    }

    //

    input_file02 = fopen(read_file_02, "r");
    if (read_file_02 == NULL)
    {
        printf("I can't open the file!\n");
        exit(0);
    }

    double a1, a2, a3, a4, a5, a6, a7, a8;

    fscanf(input_file02, "%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf", &a1, &a2, &a3, &a4, &a5, &a6, &a7, &a8);
    A[0] = a1;
    A[1] = a2;
    A[2] = a3;
    A[3] = a4;
    A[4] = a5;
    A[5] = a6;
    A[6] = a7;
    A[7] = a8;

    /*
    for (i = 0; i < CH; i++)
    {
        printf("A[%d]=%lf\n", i, A[i]);
    }
*/

    input_file03 = fopen(read_file_03, "r");
    if (read_file_03 == NULL)
    {
        //printf("I can't open the file!\n");
        exit(0);
    }

    fclose(input_file02);

    double B;

    fscanf(input_file03, "%lf", &B);

    fclose(input_file03);

    // printf("B=%lf\n", B);

    // check the programs

    double P_0, P;
    P_0 = 20.0E-6;
    P = P_0 * P_0;

    output_file = fopen(output_data_file, "w");

    fprintf(output_file, "%lf ", f_Hz);

    for (i = 0; i < CH; i++)
    {
        SPL[i] = 10.0 * log10(A[i] * B * Rms[i] / P);
        printf("SPL[%d]=%lf\n", i, SPL[i]);
        fprintf(output_file, "%lf ", SPL[i]);
    }

    fclose(output_file);

    return (0);
}
