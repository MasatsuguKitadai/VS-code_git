/******************************************************************************
PROGRAM NAME :case_4.c
AUTHER       :Masatsugu Kitadai
DATE         :2021/4/21
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define num 10000

int i;
double x, y, f, s1, s2, a, b, PI;
double r[num];
double A[num];
unsigned int rand_max = RAND_MAX;
/****************************** MAIN *************************************/

double main()
{
    srand(time(NULL));
    PI = 4.0 * atan(1.0);

    for (i = 0; i < num; i++)
    {
        r[i] = fabs((double)rand() / (rand_max + 1));
    }

    for (i = 0; i < num; i++)
    {
        x = r[i];
        y = r[i + 1];

        /**********************************************************/

        f = x * x;

        /**********************************************************/

        if (f > y)
        {
            s1 = s1 + 1;
        }
        else if (f < y)
        {
            s2 = s2 + 1;
        }

        a = 1.0 * (s1 / num);
        b = 1.0 * (s2 / num);

        A[i] = a;
    }

    printf("a_f>y = %lf\n", A[num - 1]);

    return (0);
}