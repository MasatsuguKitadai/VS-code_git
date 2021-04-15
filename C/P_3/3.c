/******************************************************************************
PROGRAM NAME : practice_3
AUTHER : Masatsugu Kitadai
DATE : 1/4/2021
Think a Bit , Code a Bit , Test a Bit
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>
#define x_grid 31                                        // number of grids in x direction
#define y_grid 31                                        // number of grids in y direction
const char grid_space = 1;                               // grid width
const char *output_data_file = "2dvec_vortex000001.dat"; // name of output file
double u[x_grid][y_grid];                                // u vector array
double v[x_grid][y_grid];                                // v vector array
double U[x_grid][y_grid];                                // absolute vector array
double omega[x_grid][y_grid];                            // vorticity array

double a[x_grid][y_grid];
double b[x_grid][y_grid];
double c[x_grid][y_grid];
double d[x_grid][y_grid];

FILE *output_file; // pointer for output file

const char *xxlabel = "{/Times-New-Roman:Italic=20 x} [pixel]";
const char *yylabel = "{/Times-New-Roman:Italic=20 y} [pixel]";
const char *cb_label = "{/Symbol:Italic=20 w}_{/Times-New-Roman:Italic=20 z} [sec]"; ///color bar range min

const double v_r = 1.0; ///magnified ratio for vector length

const int x_min = 0;   ///x range min
const int x_max = 30;  ///x range max
const int y_min = 0;   ///y range min
const int y_max = 30;  ///y range max
const int cb_min = -2; ///color bar range min
const int cb_max = 2;  ///color bar range max

const char *read_file_dir = "01_plot_vec_vortex";
const char *read_file_header = "2dvec_vortex";
const char *write_file_dir = "02_splot_2dvec_vortex_map";
const char *write_file_header = "2dvec_vortex_map";

//Graph parameters for GNU
char read_file[100];
void graph_GNU(); //png & eps
FILE *gp;         //gnuplot
FILE *infile;

int moveFile(const char *srcPath, const char *destPath)
{
    return !rename(srcPath, destPath);
}

/*********************************
MAIN
*********************************/
double main()
{
    int i, j;
    double PI = 4.0 * atan(1.0);

    // preparing for output file
    output_file = fopen(output_data_file, "w");

    // Array initialization
    for (i = 0; i < x_grid; i++)
    {
        for (j = 0; j < y_grid; j++)
        {
            u[i][j] = 0;
            v[i][j] = 0;
            U[i][j] = 0;
            omega[i][j] = 0;
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

            fprintf(output_file, "%d\t%d\t%3lf\t%.3lf\t%.3lf\t%3lf\n",
                    i * grid_space, j * grid_space, omega[i][j], u[i][j], v[i][j], U[i][j]);

            //Caution : just line breaking for printing this document

            /*
            printf("%d\t,%d\t,%.3lf\t,%.3lf\t,%.3lf\t,%.3lf\n",
                   i * grid_space, j * grid_space, omega[i][j], u[i][j], v[i][j], U[i][j]);
            */
        }
        fprintf(output_file, "\n");
        //printf("\n");
    }

    fclose(output_file);

    mode_t mode = S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;
    mkdir(read_file_dir, mode);
    mkdir(write_file_dir, mode);

    // transfer the result file to the specified folder

    if (moveFile("2dvec_vortex000001.dat", "01_plot_vec_vortex/2dvec_vortex000001.dat"))
    {
        puts("transferred the file");
    }
    else
    {
        puts("cannot transferred");
    }

    int k = 0;
    int UP = 0;
    while (UP == 0)
    {
        k++;
        sprintf(read_file, "%s//%s%06d.dat", read_file_dir, read_file_header, k);
        printf("%s//%s%06d.dat\n", read_file_dir, read_file_header, k);
        infile = fopen(read_file, "rb");

        if (infile == NULL)
        {
            printf("break!\n");
            break;
        }

        fclose(infile);

        if ((gp = popen("gnuplot", "w")) == NULL)
        {
            printf("gnuplot is not here!\n");
            exit(0);
        }

        //PNG image
        fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");
        fprintf(gp, "set output '%s//%s%06d.png'\n", write_file_dir, write_file_header, k);
        fprintf(gp, "set multiplot\n");     // <steps in scan>,<steps between scans>
        fprintf(gp, "unset key\n");         // <steps in scan>,<steps between scans>
        fprintf(gp, "set size ratio -1\n"); // <steps in scan>,<steps between scans>

        fprintf(gp, "set lmargin screen 0.15\n"); // <steps in scan>,<steps between scans>
        fprintf(gp, "set rmargin screen 0.85\n"); // <steps in scan>,<steps between scans>
        fprintf(gp, "set tmargin screen 0.85\n"); // <steps in scan>,<steps between scans>
        fprintf(gp, "set bmargin screen 0.15\n"); // <steps in scan>,<steps between scans>

        fprintf(gp, "set xrange [%d:%d]\n", x_min, x_max);       // <steps in scan>,<steps between scans>
        fprintf(gp, "set xlabel '%s'offset 0.0,0.5\n", xxlabel); // <steps in scan>,<steps between scans>
        fprintf(gp, "set yrange [%d:%d]\n", y_min, y_max);       // <steps in scan>,<steps between scans>
        fprintf(gp, "set ylabel '%s'offset 0.5,0.0\n", yylabel); // <steps in scan>,<steps between scans>

        fprintf(gp, "set cblabel '%s'offset 0.0,0.0\n", cb_label);
        fprintf(gp, "set cbrange['%d':'%d']\n", cb_min, cb_max);
        fprintf(gp, "set colorbox vertical user origin 0.8, 0.2 size 0.025,0.6\n");
        fprintf(gp, "set palette rgbformulae 22,13,-31\n");

        fprintf(gp, "set pm3d map\n"); // <steps in scan>,<steps between scans>
        fprintf(gp, "splot '%s//%s%06d.dat' using 2:1:3 with pm3d, '%s//%s%06d.dat' using 2:1:($1*0.0):(%lf*$5):(%lf*$4):($1*0.0) with vectors head filled lt 2 lc 'black' \n", read_file_dir, read_file_header, k, read_file_dir, read_file_header, k, v_r, v_r);

        fflush(gp); //Clean up Data

        fprintf(gp, "exit\n"); // Quit gnuplot

        pclose(gp);
    }

    return (0);
}