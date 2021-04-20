/*************************************************
PROGRAM NAME : 6-3.c
AUTHER : Masatsugu Kitadai
DATE :
Think a Bit , Code a Bit , Test a Bit
**************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define number 10000

double value[number];
const char *input_data_file = "output/output_data.dat";
FILE *read_file;

const char *output_data_file_sd = "output/output_data_sd.dat";
FILE *output_file;

//Graph parameters for GNU
char read_file_gnu[100];
void graph_GNU(); //png & eps
FILE *gp;         //gnuplot
FILE *infile;

const char *read_file_dir = "output";
const char *read_file_header = "output_data_sd";
const char *write_file_dir = "Graph";
const char *write_file_header = "verification";

const char *xxlabel = "";
const int x_min = 10;
const int x_max = 10000;
const char *yylabel = "";
const int y_min = 0;
const int y_max = 500;

/********************MAIN**************************/

// input data_file

double main()
{
    int i, j, k;
    int ch1;
    double ch2;

    read_file = fopen(input_data_file, "r");
    if (input_data_file == NULL)
    {
        printf("I can't open the file!\n");
        exit(0);
    }

    for (i = 0; i < number; i++)
    {
        fscanf(read_file, "%d\t %lf", &ch1, &ch2);
        value[i] = ch2;

        // check the programs
        // printf("value[%d] = %lf\n", i, value[i]);
    }

    fclose(read_file);

    double average, sum_1, sum_2;
    double s[1000];

    for (i = 0; i < number; i++)
    {
        for (j = 0; j < number / 10; j++)
        {
            if (9 + 10 * j == i)
            {
                sum_1 = 0;
                sum_2 = 0;

                for (k = 0; k < i + 1; k++)
                {
                    sum_1 = sum_1 + value[k];
                }

                average = sum_1 / (i + 1);

                // printf("sum_1[%d] = %lf\n", j * 10, sum_1);

                for (k = 0; k < i + 1; k++)
                {
                    sum_2 = sum_2 + (value[k] - average) * (value[k] - average);
                }

                s[j] = sum_2 / (i + 1);

                // printf("s[%d] = %.8lf\n", j * 10, s[j]);
            }
        }
    }

    output_file = fopen(output_data_file_sd, "w");

    for (i = 0; i < 1000; i++)
    {
        fprintf(output_file, "%d\t%.8lf\n", (i + 1) * 10, s[i]);
    }

    fclose(output_file);

    /***Gnuplot*********************************************************************************/

    sprintf(read_file_gnu, "%s//%s.dat", read_file_dir, read_file_header);
    infile = fopen(read_file_gnu, "rb");

    if ((gp = popen("gnuplot", "w")) == NULL)
    {
        printf("gnuplot is not here!\n");
        exit(0);
    }

    fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");
    fprintf(gp, "set output '%s//%s.png'\n", write_file_dir, write_file_header);
    fprintf(gp, "unset key\n"); // <steps in scan>,<steps between scans>

    fprintf(gp, "set lmargin screen 0.15\n"); // <steps in scan>,<steps between scans>
    fprintf(gp, "set rmargin screen 0.85\n"); // <steps in scan>,<steps between scans>
    fprintf(gp, "set tmargin screen 0.85\n"); // <steps in scan>,<steps between scans>
    fprintf(gp, "set bmargin screen 0.15\n"); // <steps in scan>,<steps between scans>

    fprintf(gp, "set xrange [%d:%d]\n", x_min, x_max); // <steps in scan>,<steps between scans>
    fprintf(gp, "set logscale x\n");
    fprintf(gp, "set xlabel '%s'offset 0.0,0.5\n", xxlabel);  // <steps in scan>,<steps between scans>
    fprintf(gp, "set yrange [%d:%d]\n", y_min, y_max);        // <steps in scan>,<steps between scans>
    fprintf(gp, "set ylabel '%s'offset -0.5,0.0\n", yylabel); // <steps in scan>,<steps between scans>
    fprintf(gp, "plot '%s//%s.dat' using 1:2 with lines\n", read_file_dir, read_file_header);

    fflush(gp); //Clean up Data

    pclose(gp);

    fclose(infile);

    return (0);
}
