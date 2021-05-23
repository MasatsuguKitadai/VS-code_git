/******************************************************************************
PROGRAM NAME :case_4.c
AUTHER       :Masatsugu Kitadai
DATE         :2021/4/21
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define num 500

int i;
double x, y, f, s1, s2, a, b, PI;
double r[num];
double A[num];
unsigned int rand_max = RAND_MAX;

const char *output_data_file = "output/case_3.dat";
FILE *output_file;

//Graph parameters for GNU
char read_file_gnu[100];
void graph_GNU(); //png & eps
FILE *gp;         //gnuplot
FILE *infile;

const char *read_file = "output/case_3.dat";
const char *write_file = "Graph/case_3.png";

const char *xxlabel = "";
const int x_min = 0;
const int x_max = num - 1;
const char *yylabel = "";
const int y_min = 0;
const int y_max = 1;

/****************************** MAIN *************************************/

double
main()
{
    srand(time(NULL));
    PI = 4.0 * atan(1.0);

    for (i = 0; i < num + 1; i++)
    {
        r[i] = fabs((double)rand() / (rand_max + 1));
        // printf("%lf\n", r[i]);
    }

    s1 = 0;
    s2 = 0;

    for (i = 0; i < num; i++)
    {
        x = r[i];
        y = r[i + 1];

        /**********************************************************/

        f = cos(PI / 2.0 * x);

        /**********************************************************/

        if (f > y)
        {
            s1 = s1 + 1;
        }
        else if (f < y)
        {
            s2 = s2 + 1;
        }

        a = (s1 / (i + 1));
        b = (s2 / (i + 1));

        A[i] = a;
        // printf("[%d] %lf,%lf,%lf,%lf\n", i, x, f, y, A[i]);
    }

    printf("a_f>y = %lf\n", A[num - 1]);

    output_file = fopen(output_data_file, "w");

    for (i = 0; i < num + 1; i++)
    {
        fprintf(output_file, "%d\t%lf\n", i + 1, A[i]);
    }

    fclose(output_file);

    /***Gnuplot*********************************************************************************/

    sprintf(read_file_gnu, "%s", read_file);
    infile = fopen(read_file_gnu, "rb");

    if ((gp = popen("gnuplot", "w")) == NULL)
    {
        printf("gnuplot is not here!\n");
        exit(0);
    }

    fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");
    fprintf(gp, "set output '%s'\n", write_file);
    fprintf(gp, "unset key\n");

    fprintf(gp, "set lmargin screen 0.15\n");
    fprintf(gp, "set rmargin screen 0.85\n");
    fprintf(gp, "set tmargin screen 0.85\n");
    fprintf(gp, "set bmargin screen 0.15\n");

    fprintf(gp, "set xrange [%d:%d]\n", x_min, x_max);
    fprintf(gp, "set xlabel '%s'offset 0.0,0.5\n", xxlabel);
    fprintf(gp, "set yrange [%d:%d]\n", y_min, y_max);
    fprintf(gp, "set ylabel '%s'offset -0.5,0.0\n", yylabel);
    fprintf(gp, "plot '%s' using 1:2 with lines lc 'black'\n", read_file);

    fflush(gp);            //Clean up Data
    fprintf(gp, "exit\n"); // Quit gnuplot
    pclose(gp);

    fclose(infile);

    return (0);
}