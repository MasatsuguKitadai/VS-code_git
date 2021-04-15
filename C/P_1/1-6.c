/******************************************************************************
PROGRAM NAME:1-6.c
AUTHER: Masatsugu Kitadai
DATE:
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
const char *input_data_file = "input.dat";                   // name of input file
const char *output_data_file_1 = "Sum_2.dat";                // name of output file_1
const char *output_data_file_2 = "Average_2.dat";            // name of output file_2
const char *output_data_file_3 = "Standard_Deviation_2.dat"; // name of output file_3
const char *output_data_file_4 = "Median.dat_2";             // name of output file_4
const char *output_data_file_all = "All_Data.dat_2";         // name of output file_all
const int data_long = 11;                                    // length of data
double data_value = data_long;                               // Array for data
FILE *input_file;                                            // pointer of inputfile
FILE *output_file;                                           // pointer of outputifle
/********************************* MAIN *************************************/
float main()
{
    int i, j, k, tmp;
    double value[11];
    double sum;
    double average;
    double standard_deviation;
    double value_2[11];
    double sum_2;
    double sort_numbers;
    double median;

    // Prepare for inputdata file
    input_file = fopen(input_data_file, "r");
    if (input_file == NULL)
    {
        printf(" Failure. I can't open the file. \n\n ");
        exit(0);
    }
    else
    {
        printf(" Successful! I can read the file. \n\n ");
    }

    // Read input file
    /* printf("\n【 Input Data 】\n"); */
    for (i = 0; i < data_long; i++)
    {
        fscanf(input_file, "%lf", &value[i]);
        data_value = value[i];
        // Test program_1 : Check the input data
        /* printf(" [%i] \t %lf \n", i + 1, value[i]); */
    }
    fclose(input_file);

    // calculate!!!
    // [1] Sum

    sum = 0;

    for (i = 0; i < data_long; i++)
    {
        sum = sum + value[i];
    }

    // [2] Average
    average = sum / i;

    // [3] Standard_Deviation
    sum_2 = 0;

    for (i = 0; i < data_long; i++)
    {
        value_2[i] = (value[i] - average);
        value_2[i] = pow(value_2[i], 2);
        sum_2 = sum_2 + value_2[i];

        // Test program_2 : Check the square value
        /* printf(" [%i] \t %lf \n ", i + 1, value_2[i]); */
    }

    // Test program_3 : Check the sum value in sqrt
    /* printf(" [SUM_2] \t %lf \n ", sum_2); */

    standard_deviation = sqrt(sum_2 / i);

    // [4] Sort out Numbers

    for (i = 0; i < data_long; i++)
    {
        for (j = i + 1; j < data_long; j++)
        {
            if (value[i] > value[j])
            {
                tmp = value[i];
                value[i] = value[j];
                value[j] = tmp;
            }
        }
    }

    // Test program_4 : Write sorted out numbers
    /*{
        printf(" \n Wirte sorted out numbers.\n ");
        for (i = 0; i < data_long; i++)
        {
            printf("[%i] \t %lf \n ", i + 1, value[i]);
        }
    }*/

    k = 0;
    if (i % 2 == 0)
    {
        k = i / 2 - 0.5;
        median = (value[k] + value[k + 1]) / 2;
    }
    else
    {
        k = i / 2;
        median = value[k];
    }

    // Write the output data
    printf("【 OUTPUT DATA 】\n\n");

    // Prepare for outputdata file_1
    output_file = fopen(output_data_file_1, "w");

    // Write output file_1
    fprintf(output_file, "【 OUTPUT DATA 】\n\n");
    fprintf(output_file, " [Sum] \n %lf \n\n", sum);
    printf(" [Sum] \n %lf \n\n", sum);
    fclose(output_file);

    // Prepare for outputdata file_2
    output_file = fopen(output_data_file_2, "w");

    // Write output file_2
    fprintf(output_file, "【 OUTPUT DATA 】\n\n");
    fprintf(output_file, " [Average] \n %lf \n\n", average);
    printf(" [Average] \n %lf \n\n", average);
    fclose(output_file);

    // Prepare for outputdata file_3
    output_file = fopen(output_data_file_3, "w");

    // Write output file_3
    fprintf(output_file, "【 OUTPUT DATA 】\n\n ");
    fprintf(output_file, " [Standard Deviation] \n %lf \n\n ", standard_deviation);
    printf(" [Standard Deviation] \n %lf \n\n", standard_deviation);
    fclose(output_file);

    // Prepare for outputdata file_4
    output_file = fopen(output_data_file_4, "w");

    // Write output file_4
    fprintf(output_file, "【 OUTPUT DATA 】\n\n ");
    fprintf(output_file, " [Median] \n %lf \n\n ", median);
    printf(" [Median] \n %lf \n\n", median);
    fclose(output_file);

    // end the program
    return (0);
}