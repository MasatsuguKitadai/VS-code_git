/******************************************************************************
PROGRAM NAME:sq-file-input.cpp
AUTHER: Yohsuke TANAKA
DATE: 2016 11/28
235.CSV�̘A�ԃt�@�C���ǂݍ��݃v���O����
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* read_file = "235.CSV"; 
const int CH = 8; //���̓`�����l����
const int data_long = 60000;//NR500�̃f�[�^��

double wave_value[data_long][CH];//CH���Ƃ̑���l
char date[100];

FILE *input_file01;

/*********************************   MAIN   *********************************/
main(){

int i,tim;
double ch1,ch2,ch3,ch4,ch5,ch6,ch7,ch8;

input_file01=fopen(read_file,"r");if(read_file==NULL){printf("I can't open infile!\n");exit(0);}

//CSV�̂���Ȃ��s�����̃f�[�^�ǂݍ��ݑO�ɓǂݔ�΂��R�[�h��ǉ����Ă��������B
		
for(i=0;i<data_long;i++){
	fscanf(input_file01,"%[^,], %d, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf",date, &tim, &ch1, &ch2, &ch3, &ch4, &ch5, &ch6, &ch7, &ch8);//csv��CH���Ƃ̑���l��ǂݍ���
	wave_value[i][0]=ch1;wave_value[i][1]=ch2;
	wave_value[i][2]=ch3;wave_value[i][3]=ch4;
	wave_value[i][4]=ch5;wave_value[i][5]=ch6;
	wave_value[i][6]=ch7;wave_value[i][7]=ch8;
}
fclose(input_file01);

return(0);
}

