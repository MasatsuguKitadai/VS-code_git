/******************************************************************************
PROGRAM NAME:2-1.c
AUTHER: Masatsugu Kitadai
DATE:
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CH 8
#define data_long 20
const char *read_file = "235.CSV";
double wave_value[data_long][CH];
char date[20];
int omit = 57; // Number of lines to skip
char buf[128]; //
FILE *input_file01;

/*********************************   MAIN   *********************************/
double main()
{
    int i, j, k, l, tim;
    double ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8;

    // Array initialization
    for (j = 0; j < data_long; j++)
    {
        for (k = 0; k < CH; k++)
        {
            wave_value[j][k] = 0;
        }
    }

    input_file01 = fopen(read_file, "r");
    if (read_file == NULL)
    {
        printf("I can't open the file!\n");
        exit(0);
    }

    // Transrate the point of pointer
    for (j = 0; j < omit; j++)
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
        wave_value[i][6] = ch6;
        wave_value[i][7] = ch7;

        // comfirm the programs
        printf("%s , %d , %lf , %lf , %lf , %lf , %lf , %lf , %lf , %lf", date, tim, ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8);
    }
    fclose(input_file01);

    return (0);
}
