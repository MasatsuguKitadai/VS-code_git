/******************************************************************************
PROGRAM NAME:2-gnuplot.cpp
AUTHER: Masatsugu Kitadai
DATE:
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

const char *input_file_SPL = "f_SPL_8ch.dat"; //ファイル名　入力データ形式 f ch1 ch2 ch3 ch4 ch5 ch6 ch7 ch8
const char *fileout = "normal";               //ファイル名　入力データ形式 f ch1 ch2 ch3 ch4 ch5 ch6 ch7 ch8
const int min_SPL = 40;                       //SPLのレンジ最小値 [dB]
const int max_SPL = 85;                       //SPLのレンジ最大値 [dB]

/*変数の定義*/
char read_file[100]; /*連番ファイルの文字配列*/

/*gnuplot、入力ファイルへのポインタ*/
FILE *infile1; //入力ファイル
FILE *gp;      //gnuplot

/************************************************************************************************************/

int main()
{
    mkdir("png", 0755); //png画像保存フォルダ作成
    mkdir("eps", 0755); //eps画像保存フォルダ作成

    int i;
    double f_Hz, ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8;

    double deg[9];
    for (i = 0; i < 9; ++i)
    {
        deg[i] = 45 * i;
    }

    sprintf(read_file, "%s", input_file_SPL); //入力データ
    infile1 = fopen(read_file, "rb");
    if (infile1 == NULL)
    {
        printf("I can't open input file!!\n");
        exit(0);
    }

    int file_length = 0;
    while (fscanf(infile1, "%lf %lf %lf %lf %lf %lf %lf %lf %lf", &f_Hz, &ch1, &ch2, &ch3, &ch4, &ch5, &ch6, &ch7, &ch8) != EOF)
    {
        file_length++;
    }
    fclose(infile1);

    double *ff_Hz, *cch1, *cch2, *cch3, *cch4, *cch5, *cch6, *cch7, *cch8;
    cch1 = new double[file_length];
    cch2 = new double[file_length];
    cch3 = new double[file_length];
    cch4 = new double[file_length];
    cch5 = new double[file_length];
    cch6 = new double[file_length];
    cch7 = new double[file_length];
    cch8 = new double[file_length];
    ff_Hz = new double[file_length];

    /*出力連番ファイルの作成*/

    sprintf(read_file, "%s", input_file_SPL);
    infile1 = fopen(read_file, "rb");
    if (infile1 == NULL)
    {
        printf("I can't open input file!\n");
        exit(0);
    }

    for (i = 0; i < file_length; i++)
    {
        fscanf(infile1, "%lf %lf %lf %lf %lf %lf %lf %lf %lf", &f_Hz, &ch1, &ch2, &ch3, &ch4, &ch5, &ch6, &ch7, &ch8);
        ff_Hz[i] = f_Hz;
        cch1[i] = ch1;
        cch2[i] = ch2;
        cch3[i] = ch3;
        cch4[i] = ch4;
        cch5[i] = ch5;
        cch6[i] = ch6;
        cch7[i] = ch7;
        cch8[i] = ch8;
    }
    fclose(infile1);

    //png画像出力
    for (i = 0; i < file_length; i++)
    {
        if ((gp = popen("gnuplot", "w")) == NULL)
        {
            printf("gnuplot is not here!\n");
            exit(0); // gnuplotが無い場合、異常ある場合は終了
        }

        int fff_Hz = ff_Hz[i];
        printf("Saving SPL at f=%d [Hz] as png image\n", fff_Hz);
        fprintf(gp, "set size square\n");                      // 縦横を同じ比率の正方形
        fprintf(gp, "set polar\n");                            // 極座標
        fprintf(gp, "set rrange [%d:%d]\n", min_SPL, max_SPL); // 範囲の指定
        fprintf(gp, "unset key\n");                            //キャプションを非表示
        fprintf(gp, "unset border\n");                         //キャプションを非表示
        fprintf(gp, "unset xtics\n");                          //外枠x軸目盛り見出しを非表示にする
        fprintf(gp, "unset ytics\n");                          //外枠y軸目盛り見出しを非表示にする

        fprintf(gp, "set label 1 '[dB]' at graph 1.01,0.45\n");       //単位
        fprintf(gp, "set label 2 '90^o' at graph 1.01,0.5 left\n");   //接地面を0度として
        fprintf(gp, "set label 3 '135^o' at graph 0.8,0.85\n");       //反時計回りに
        fprintf(gp, "set label 4 '180^o' at graph 0.5,1.0 center\n"); //45度づつ
        fprintf(gp, "set label 5 '225^o' at graph 0.1,0.85\n");       //角度のキャプションを
        fprintf(gp, "set label 6 '270^o' at graph -0.01,0.5\n");      //入れてます
        fprintf(gp, "set label 7 '315^o' at graph 0.1,0.15\n");       //いちいち
        fprintf(gp, "set label 8 '0^o' at graph 0.5,0.0 center\n");   //設定が
        fprintf(gp, "set label 9 '45^o' at graph 0.8,0.15\n");        //面倒です
        //fprintf(gp, "set label 10 'f=%03d Hz' at graph 0.9,0.08 font 'Arial,15'\n",fff_Hz);//周波数の値です

        fprintf(gp, "set angles degrees\n"); //角度指定
        fprintf(gp, "set grid polar 45\n");  //角度指定

        fprintf(gp, "set terminal pngcairo \n");
        fprintf(gp, "set output 'png-plot%03d.png'\n", fff_Hz);
        fprintf(gp, "plot '-'  with linespoints pointtype 7 linewidth 3 lt rgb 'black'\n");
        fprintf(gp, "%f\t%f\n", deg[0], cch3[i]);
        fprintf(gp, "%f\t%f\n", deg[1], cch2[i]);
        fprintf(gp, "%f\t%f\n", deg[2], cch1[i]);
        fprintf(gp, "%f\t%f\n", deg[3], cch8[i]);
        fprintf(gp, "%f\t%f\n", deg[4], cch7[i]);
        fprintf(gp, "%f\t%f\n", deg[5], cch6[i]);
        fprintf(gp, "%f\t%f\n", deg[6], cch5[i]);
        fprintf(gp, "%f\t%f\n", deg[7], cch4[i]);
        fprintf(gp, "%f\t%f\n", deg[8], cch3[i]);

        fflush(gp);            // バッファに格納されているデータを吐き出す（必須）
        fprintf(gp, "exit\n"); // gnuplotの終了
        pclose(gp);
    }

    printf("\n");

    for (i = 0; i < file_length; i++)
    {
        if ((gp = popen("gnuplot", "w")) == NULL)
        {
            printf("gnuplot is not here!\n");
            exit(0); // gnuplotが無い場合、異常ある場合は終了
        }

        int fff_Hz = ff_Hz[i];
        printf("Saving SPL at f=%d [Hz] as eps image\n", fff_Hz);
        fprintf(gp, "set size square\n");                      // 縦横を同じ比率の正方形
        fprintf(gp, "set polar\n");                            // 極座標
        fprintf(gp, "set rrange [%d:%d]\n", min_SPL, max_SPL); // 範囲の指定
        fprintf(gp, "unset key\n");                            //キャプションを非表示
        fprintf(gp, "unset border\n");                         //キャプションを非表示
        fprintf(gp, "unset xtics\n");                          //外枠x軸目盛り見出しを非表示にする
        fprintf(gp, "unset ytics\n");                          //外枠y軸目盛り見出しを非表示にする

        fprintf(gp, "set label 1 '[dB]' at graph 1.01,0.45\n");       //単位
        fprintf(gp, "set label 2 '90^o' at graph 1.01,0.5 left\n");   //接地面を0度として
        fprintf(gp, "set label 3 '135^o' at graph 0.8,0.85\n");       //反時計回りに
        fprintf(gp, "set label 4 '180^o' at graph 0.5,1.0 center\n"); //45度づつ
        fprintf(gp, "set label 5 '225^o' at graph 0.1,0.85\n");       //角度のキャプションを
        fprintf(gp, "set label 6 '270^o' at graph -0.01,0.5\n");      //入れてます
        fprintf(gp, "set label 7 '315^o' at graph 0.1,0.15\n");       //いちいち
        fprintf(gp, "set label 8 '0^o' at graph 0.5,0.0 center\n");   //設定が
        fprintf(gp, "set label 9 '45^o' at graph 0.8,0.15\n");        //面倒です
        //fprintf(gp, "set label 10 'f=%03d Hz' at graph 0.9,0.08 font 'Arial,15'\n",fff_Hz);//周波数の値です

        fprintf(gp, "set angles degrees\n"); //角度指定
        fprintf(gp, "set grid polar 45\n");  //角度指定

        fprintf(gp, "set terminal postscript eps \n");
        fprintf(gp, "set output 'eps-%splot%03d.eps'\n", fileout, fff_Hz);
        fprintf(gp, "plot '-'  with linespoints pointtype 7 linewidth 3 lt rgb 'black'\n");
        fprintf(gp, "%f\t%f\n", deg[0], cch3[i]);
        fprintf(gp, "%f\t%f\n", deg[1], cch2[i]);
        fprintf(gp, "%f\t%f\n", deg[2], cch1[i]);
        fprintf(gp, "%f\t%f\n", deg[3], cch8[i]);
        fprintf(gp, "%f\t%f\n", deg[4], cch7[i]);
        fprintf(gp, "%f\t%f\n", deg[5], cch6[i]);
        fprintf(gp, "%f\t%f\n", deg[6], cch5[i]);
        fprintf(gp, "%f\t%f\n", deg[7], cch4[i]);
        fprintf(gp, "%f\t%f\n", deg[8], cch3[i]);

        fflush(gp);            // バッファに格納されているデータを吐き出す
        fprintf(gp, "exit\n"); // gnuplotの終了
        pclose(gp);
    }

    delete[] ff_Hz, cch1, cch2, cch3, cch4, cch5, cch6, cch7, cch8; // 動的配列のメモリは必ず開放しておく

    return 0;
}