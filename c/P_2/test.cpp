/******************************************************************************
PROGRAM NAME: SPL
AUTHER: Kohtaro Matsui
DATE: 2021 3/23
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
const char *read_file = "235.CSV";
const char *read_file02 = "C_v_p_1k_ono.dat"; // 校正データ
const char *read_file03 = "C_lab_ono.dat";    // 校正データ
const char *write_file = "kadai2_f_SPL_8ch.dat";
const int CH = 8;
const int data_long = 60000;
const int f_Hz = 235; // [Hz], 音響加振
double wave_value[data_long][CH];
char date[100];
double f(int x, int CH) // 時系列データの二乗平均
{
    return wave_value[x][CH] * wave_value[x][CH] / data_long;
}
double simpsons_rule(int CH) // shimpson則
{
    int i;
    double value = 0.0;
    for (i = 1; i <= data_long; i++)
    {
        if (i == 1 || i == data_long)
            value += f(i, CH);
        else if (i % 2 == 1)
            value += 4 * f(i, CH);
        else
            value += 2 * f(i, CH);
    }
    value = value / 3;
    return value;
}
FILE *input_file01;
FILE *input_file02;
FILE *input_file03;
FILE *output_file;
/*********************************   MAIN   *********************************/
int main()
{
    int i, tim;
    double ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8;
    char bff[100];
    int omit = 57;
    input_file01 = fopen(read_file, "r");
    if (input_file01 == NULL)
    {
        printf("I can't open infile!\n");
        exit(0);
    }
    //不必要な行を読み飛ばす
    for (i = 0; i <= omit; i++)
    {
        fgets(bff, sizeof(bff), input_file01);
    }
    for (i = 1; i <= data_long; i++)
    {
        fscanf(input_file01, "%[^,], %d, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf", &date, &tim, &ch1, &ch2, &ch3, &ch4, &ch5, &ch6, &ch7, &ch8); //csvのCHごとの測定値を読み込み
        wave_value[i][1] = ch1;
        wave_value[i][2] = ch2;
        wave_value[i][3] = ch3;
        wave_value[i][4] = ch4;
        wave_value[i][5] = ch5;
        wave_value[i][6] = ch6;
        wave_value[i][7] = ch7;
        wave_value[i][8] = ch8;
    }
    fclose(input_file01);
    printf("wave_value[1][1]=%lf\n", wave_value[1][1]);                           //最初のデータチェック
    printf("wave_value[%d][%d]=%lf\n", data_long, CH, wave_value[data_long][CH]); //最後のデータチェック
    input_file02 = fopen(read_file02, "r");
    if (input_file02 == NULL)
    {
        printf("I can't open infile!\n");
        exit(0);
    }
    double C_v_p_1k_ono;
    fscanf(input_file02, "%lf", &C_v_p_1k_ono);
    fclose(input_file02);
    printf("C_v_p_1k_ono=%lf\n", C_v_p_1k_ono); //校正データチェック
    input_file03 = fopen(read_file03, "r");
    if (input_file03 == NULL)
    {
        printf("I can't open infile!\n");
        exit(0);
    }
    double C_lab_ono[CH];
    double kosei_value3;
    for (i = 1; i <= CH; i++)
    {
        fscanf(input_file03, "%lf", &kosei_value3);
        C_lab_ono[i] = kosei_value3;
    }
    fclose(input_file03);
    for (i = 1; i <= CH; i++) //校正データチェック
    {
        printf("C_lab_ono[%d]=%lf\n", i, C_lab_ono[i]);
    };

    output_file = fopen(write_file, "w");
    fprintf(output_file, "%d\n", f_Hz);
    double SPL[CH];
    for (i = 1; i <= CH; i++)
    {
        SPL[i] = 10 * log10(C_v_p_1k_ono * C_lab_ono[i] * simpsons_rule(i) / 400 * 1000000000000);
        printf("SPL[%d]=%lf\n", i, SPL[i]);
        fprintf(output_file, "%lf\n", SPL[i]);
    };
    fclose(output_file);
    printf("C_v_p_1k_ono=%lf\n", C_v_p_1k_ono); //校正データチェック
    for (i = 1; i <= CH; i++)                   //校正データチェック
    {
        printf("C_lab_ono[%d]=%lf\n", i, C_lab_ono[i]);
    };
    for (i = 1; i <= CH; i++)
    {
        printf("CH%d : %lf\n", i, simpsons_rule(i));
    }
    return 0;
}
