/******************************************************************************
PROGRAM NAME:Histgram by GNU plot
AUTHER: Yohsuke Tanaka
DATE: 2018.01.09
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

//out-input file name
const char *write_file01 = "output_data.dat"; //Input file
const char *write_file_dir = "Graph";         //Output file
const char *output_graph = "histgram";        //Output file

//Graph parameters for GNU
void graph_GNU(); //histgram at png & eps
FILE *gp;         //gnuplot

/*********************************   MAIN   *********************************/
double main()
{
    mode_t mode = S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;
    mkdir(write_file_dir, mode);
    graph_GNU();

    return (0);
}

void graph_GNU()
{
    if ((gp = popen("gnuplot", "w")) == NULL)
    {
        printf("gnuplot is not here!\n");
        exit(0);
    }

    //PNG image
    fprintf(gp, "set terminal pngcairo \n");
    fprintf(gp, "set output '%s//%s.png'\n", write_file_dir, output_graph);

    fprintf(gp, "plot '%s' using 1:2 with boxes\n", write_file01);
    fflush(gp); //Clean up Data

    fprintf(gp, "exit\n"); // Quit gnuplot

    pclose(gp);

    if ((gp = popen("gnuplot", "w")) == NULL)
    {
        printf("gnuplot is not here!\n");
        exit(0);
    }

    // EPS image
    fprintf(gp, "set terminal postscript eps  'Arial' 25\n");
    fprintf(gp, "set output '%s//%s.eps'\n", write_file_dir, output_graph);

    fprintf(gp, "plot '%s' using 1:2 with boxes\n", write_file01);
    fflush(gp); //Clean up Data

    fprintf(gp, "exit\n"); // Quit gnuplot

    pclose(gp);
}
