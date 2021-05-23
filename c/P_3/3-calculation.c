/******************************************************************************
PROGRAM NAME : 3-calculation.c
AUTHER : Masatsugu Kitadai
DATE : 1/4/2021
Think a Bit , Code a Bit , Test a Bit
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
        // printf("\n");
    }

    fclose(output_file);
    return (0);
}