/******************************************************************************
PROGRAM NAME : practice_4
AUTHER : Masatsugu Kitadai
DATE : 8/4/2021
Think a Bit , Code a Bit , Test a Bit
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>
#define x_grid 31 // number of grids in x direction
#define y_grid 31 // number of grids in y direction
#define filenumbers 2

const char grid_space = 1;    // grid width
double u[x_grid][y_grid];     // u vector array
double v[x_grid][y_grid];     // v vector array
double U[x_grid][y_grid];     // absolute vector array
double omega[x_grid][y_grid]; // vorticity array
double OMEGA[x_grid][y_grid];

FILE *output_file; // pointer for output file

const char *xxlabel = "{/Times-New-Roman:Italic=20 x} [pixel]";
const char *yylabel = "{/Times-New-Roman:Italic=20 y} [pixel]";
const char *cb_label_1 = "{/Symbol:Italic=20 w}_{/Times-New-Roman:Italic=20 z} [sec]";                      ///color bar range min
const char *cb_label_2 = "{/Symbol:Italic=20 D}{/Symbol:Italic=20 w}_{/Times-New-Roman:Italic=20 z} [sec]"; ///color bar range min

const double v_r = 1.0; ///magnified ratio for vector length

const int x_min = 0;           ///x range min
const int x_max = 30;          ///x range max
const int y_min = 0;           ///y range min
const int y_max = 30;          ///y range max
const int cb_min_1 = -2;       ///color bar range min
const int cb_max_1 = 2;        ///color bar range max
const double cb_min_2 = 0.000; ///color bar range min
const double cb_max_2 = 0.016; ///color bar range max

const char *output_data_file = "output_data.dat"; // name of output file

const char *read_file_dir = "output";
const char *read_file_header = "output_data";
const char *write_file_dir_1 = "practice(3)";
const char *write_file_header_1 = "Vorticity_map";
const char *write_file_dir_2 = "practice(4)";
const char *write_file_header_2 = "Difference_map";

//Graph parameters for GNU
char read_file[100];
void graph_GNU(); //png & eps
FILE *gp;         //gnuplot
FILE *infile;

int moveFile(const char *srcPath, const char *destPath)
{
    return !rename(srcPath, destPath);
}

// 0<x<30 or 0<y<30
double pd_1(double A1, double A2)
{
    double pd_1[x_grid][y_grid];
    pd_1[x_grid][y_grid] = 1.0 / 2.0 * (A1 - A2);
    return pd_1[x_grid][y_grid];
}

// x=0 or y=0
double pd_2(double B1, double B2, double B3)
{
    double pd_2[x_grid][y_grid];
    pd_2[x_grid][y_grid] = 1.0 / 2.0 * (-B1 + 4 * B2 - 3 * B3);
    return pd_2[x_grid][y_grid];
}

// x=30 or y=30
double pd_3(double C1, double C2, double C3)
{
    double pd_3[x_grid][y_grid];
    pd_3[x_grid][y_grid] = 1.0 / 2.0 * (3 * C1 - 4 * C2 + C3);
    return pd_3[x_grid][y_grid];
}

/*** MAIN *******************************************************************************************************/

double main()
{
    int i, j;
    double PI = 4.0 * atan(1.0);

    // Array initialization
    for (i = 0; i < x_grid; i++)
    {
        for (j = 0; j < y_grid; j++)
        {
            u[i][j] = 0;
            v[i][j] = 0;
            U[i][j] = 0;
            omega[i][j] = 0;
            OMEGA[i][j] = 0;
        }
    }

    // Calc.2D velocity vector and absolute value of velocity field, vorticity field

    for (i = 0; i < x_grid; i++)
    {
        for (j = 0; j < y_grid; j++)
        {
            //  velocity vector field and absolute value of vector
            u[i][j] = cos(2.0 * PI / x_grid * i) * sin(2.0 * PI / y_grid * j);
            v[i][j] = -sin(2.0 * PI / x_grid * i) * cos(2.0 * PI / y_grid * j);
            U[i][j] = sqrt(u[i][j] * u[i][j] + v[i][j] * v[i][j]);

            // value of vorticity field
            omega[i][j] = -2 * cos(2.0 * PI / x_grid * i) * cos(2.0 * PI / y_grid * j);
        }
    }

    double M;
    M = (x_grid / (2 * PI));

    // case1 : 0<x<30   0<y<30
    for (i = 1; i < x_grid - 1; i++)
    {
        for (j = 1; j < y_grid - 1; j++)
        {
            OMEGA[i][j] = M * (pd_1(v[i + 1][j], v[i - 1][j]) - pd_1(u[i][j + 1], u[i][j - 1]));
        }
    }

    // case2 : 0<x<30   y=0
    j = 0;
    for (i = 1; i < x_grid - 1; i++)
    {
        OMEGA[i][j] = M * (pd_1(v[i + 1][j], v[i - 1][j]) - pd_2(u[i][j + 2], u[i][j + 1], u[i][j]));
    }

    // case3 : 0<x<30   y=30
    j = 30;
    for (i = 1; i < x_grid - 1; i++)
    {
        OMEGA[i][j] = M * (pd_1(v[i + 1][j], v[i - 1][j]) - pd_3(u[i][j], u[i][j - 1], u[i][j - 2]));
    }

    // case4 : x=0      0<y<30
    i = 0;
    for (j = 1; j < y_grid - 1; j++)
    {
        OMEGA[i][j] = M * (pd_2(v[i + 2][j], v[i + 1][j], v[i][j]) - pd_1(u[i][j + 1], u[i][j - 1]));
    }

    // case5 : x=30     0<y<30
    i = 30;
    for (j = 1; j < y_grid - 1; j++)
    {
        OMEGA[i][j] = M * (pd_3(v[i][j], v[i - 1][j], v[i - 2][j]) - pd_1(u[i][j + 1], u[i][j - 1]));
    }

    // case6 : x=0      y=0
    i = 0;
    j = 0;
    OMEGA[i][j] = M * (pd_2(v[i + 2][j], v[i + 1][j], v[i][j]) - pd_2(u[i][j + 2], u[i][j + 1], u[i][j]));

    // case7 : x=30     y=0
    i = 30;
    j = 0;
    OMEGA[i][j] = M * (pd_3(v[i][j], v[i - 1][j], v[i - 2][j]) - pd_2(u[i][j + 2], u[i][j + 1], u[i][j]));

    // case8 : x=0      y=30
    i = 0;
    j = 30;
    OMEGA[i][j] = M * (pd_2(v[i + 2][j], v[i + 1][j], v[i][j]) - pd_3(u[i][j], u[i][j - 1], u[i][j - 2]));

    // case9 : x=30     y=30
    i = 30;
    j = 30;
    OMEGA[i][j] = M * (pd_3(v[i][j], v[i - 1][j], v[i - 2][j]) - pd_3(u[i][j], u[i][j - 1], u[i][j - 2]));

    // write out the calculated data
    /*
    printf("【theory】\t【Difference】\n");
    for (i = 0; i < x_grid; i++)
    {
        for (j = 0; j < y_grid; j++)
        {
            printf("%lf\t%lf\n", omega[i][j], omega_[i][j]);
        }
    }
    */

    // difference between solution and culculation

    double D[x_grid][y_grid];
    for (i = 0; i < x_grid; i++)
    {
        for (j = 0; j < y_grid; j++)
        {
            D[i][j] = fabs(omega[i][j] - OMEGA[i][j]);

            // check the programs

            //printf("D[%d][%d] = %lf\n", i, j, D[i][j]);
        }
    }

    // culculate RMS error

    double sum, RMS;

    sum = 0;
    RMS = 0;

    for (i = 0; i < x_grid; i++)
    {
        for (j = 0; j < y_grid; j++)
        {
            sum = sum + D[i][j] * D[i][j];
        }
    }

    RMS = sqrt(1.0 / (x_grid * y_grid) * sum);

    // printf("sum = %lf\n", sum);
    printf("RMS = %lf\n", RMS);

    /*** data output on files *********************************************************/

    // create the new directries

    mode_t mode = S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;
    mkdir(read_file_dir, mode);
    mkdir(write_file_dir_1, mode);
    mkdir(write_file_dir_2, mode);

    // create the new files

    output_file = fopen(output_data_file, "w");

    for (i = 0; i < x_grid; i++)
    {
        for (j = 0; j < y_grid; j++)
        {
            fprintf(output_file, "%d\t%d\t%3lf\t%3lf\n", i * grid_space, j * grid_space, OMEGA[i][j], D[i][j]);
        }
        fprintf(output_file, "\n");
    }

    fclose(output_file);

    // transfer the result file to the specified folder

    if (moveFile("output_data.dat", "output/output_data.dat"))
    {
        printf("transferred scussesful\n");
    }
    else
    {
        printf("cannot transferred");
    }

    /*** Gnuplot ************************************************************************/

    // create the png file

    sprintf(read_file, "%s//%s.dat", read_file_dir, read_file_header);
    infile = fopen(read_file, "rb");
    //printf("%s.dat\n", read_file_header);

    // create the vorcity field image from the culculated data

    if ((gp = popen("gnuplot", "w")) == NULL)
    {
        printf("gnuplot is not here!\n");
        exit(0);
    }

    fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");
    fprintf(gp, "set output '%s//%s.png'\n", write_file_dir_1, write_file_header_1);
    fprintf(gp, "set multiplot\n");     // <steps in scan>,<steps between scans>
    fprintf(gp, "unset key\n");         // <steps in scan>,<steps between scans>
    fprintf(gp, "set size ratio -1\n"); // <steps in scan>,<steps between scans>

    fprintf(gp, "set lmargin screen 0.15\n"); // <steps in scan>,<steps between scans>
    fprintf(gp, "set rmargin screen 0.85\n"); // <steps in scan>,<steps between scans>
    fprintf(gp, "set tmargin screen 0.85\n"); // <steps in scan>,<steps between scans>
    fprintf(gp, "set bmargin screen 0.15\n"); // <steps in scan>,<steps between scans>

    fprintf(gp, "set xrange [%d:%d]\n", x_min, x_max);        // <steps in scan>,<steps between scans>
    fprintf(gp, "set xlabel '%s'offset 0.0,0.5\n", xxlabel);  // <steps in scan>,<steps between scans>
    fprintf(gp, "set yrange [%d:%d]\n", y_min, y_max);        // <steps in scan>,<steps between scans>
    fprintf(gp, "set ylabel '%s'offset -0.5,0.0\n", yylabel); // <steps in scan>,<steps between scans>

    fprintf(gp, "set cblabel '%s'offset 0.0,0.0\n", cb_label_1);
    fprintf(gp, "set cbrange['%d':'%d']\n", cb_min_1, cb_max_1);
    fprintf(gp, "set colorbox vertical user origin 0.8, 0.2 size 0.025,0.6\n");
    fprintf(gp, "set palette rgbformulae 22,13,-31\n");

    fprintf(gp, "set pm3d map\n"); // <steps in scan>,<steps between scans>

    fprintf(gp, "splot '%s//%s.dat' using 2:1:3 with pm3d\n", read_file_dir, read_file_header);
    fflush(gp); //Clean up Data

    pclose(gp);

    // create the difference image

    gp = popen("gnuplot", "w");

    fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");
    fprintf(gp, "set output '%s//%s.png'\n", write_file_dir_2, write_file_header_2);
    fprintf(gp, "set multiplot\n");     // <steps in scan>,<steps between scans>
    fprintf(gp, "unset key\n");         // <steps in scan>,<steps between scans>
    fprintf(gp, "set size ratio -1\n"); // <steps in scan>,<steps between scans>

    fprintf(gp, "set lmargin screen 0.15\n"); // <steps in scan>,<steps between scans>
    fprintf(gp, "set rmargin screen 0.85\n"); // <steps in scan>,<steps between scans>
    fprintf(gp, "set tmargin screen 0.85\n"); // <steps in scan>,<steps between scans>
    fprintf(gp, "set bmargin screen 0.15\n"); // <steps in scan>,<steps between scans>

    fprintf(gp, "set xrange [%d:%d]\n", x_min, x_max);        // <steps in scan>,<steps between scans>
    fprintf(gp, "set xlabel '%s'offset 0.0,0.5\n", xxlabel);  // <steps in scan>,<steps between scans>
    fprintf(gp, "set yrange [%d:%d]\n", y_min, y_max);        // <steps in scan>,<steps between scans>
    fprintf(gp, "set ylabel '%s'offset -0.5,0.0\n", yylabel); // <steps in scan>,<steps between scans>

    fprintf(gp, "set cblabel '%s'offset 0.5,0.0\n", cb_label_2);
    fprintf(gp, "set cbrange['%lf':'%lf']\n", cb_min_2, cb_max_2);
    fprintf(gp, "set colorbox vertical user origin 0.8, 0.2 size 0.025,0.6\n");
    fprintf(gp, "set palette rgbformulae 22,13,-31\n");

    fprintf(gp, "set pm3d map\n"); // <steps in scan>,<steps between scans>

    fprintf(gp, "splot '%s//%s.dat' using 2:1:4 with pm3d\n", read_file_dir, read_file_header);
    fflush(gp); //Clean up Data

    fprintf(gp, "exit\n"); // Quit gnuplot

    pclose(gp);

    fclose(infile);

    return (0);
}
