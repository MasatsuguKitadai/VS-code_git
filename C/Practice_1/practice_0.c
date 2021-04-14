/******************************************************************************
PROGRAM NAME : practice_0
AUTHER : Masatsugu Kitadai
DATE : 13/12/2020
Think a Bit! , Code a Bit!! , Test a Bit!!!
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
const char *input_data_file = "input.dat"; // name of input file
const char *output_data_file = "test.dat"; // name of output file
const int data_long = 11;                  // length of data
double data_value = data_long;             // Array for data
FILE *input_file;                          // pointer of inputfile
FILE *output_file;                         // pointer of outputifle
/********************************* MAIN *************************************/
float main()
{
    int i;
    double value[11];

    // Prepare for inputdata file
    input_file = fopen(input_data_file, "r");
    if (input_file == NULL)
    {
        printf("Failure. I can't open the file. \n");
        exit(0);
    }
    else
    {
        printf("Successful! I can read the file. \n");
    }

    // Read input file
    printf("\n【 Input Data 】\n");
    for (i = 0; i < data_long; i++)
    {
        fscanf(input_file, "%lf", &value[i]);
        data_value = value[i];
        printf("[%i] \t %lf \n", i + 1, value[i]);
    }
    fclose(input_file);

    // Prepare for outputdata file
    output_file = fopen(output_data_file, "w");

    // Write output file
    printf("\n【 Output Data 】\n");
    fprintf(output_file, "【 Output Data 】\n");
    for (i = 0; i < data_long; i++)
    {
        fprintf(output_file, "[%i] \t %lf \n", i + 1, value[i]);
        printf("[%i] \t %lf \n", i + 1, value[i]);
    }
    fclose(output_file);
    return (0);
}