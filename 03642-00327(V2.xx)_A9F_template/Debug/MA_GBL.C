/*
FileName: ma_gbl.c
Date: 2020-1-30
Time: 11:16:35
GUIDE version: 12.0.6.1567
*/

#include "ma_gbl.h"
#include "ma_proc.h"

/* USER code section begin */

//Global Define------------------
unsigned int MA_State;
unsigned int MA_Num;
unsigned int MA_Key;
unsigned int MA_Seed;
unsigned int MA_Cmd;
unsigned int MA_Add;
unsigned int MA_Wait_Key_Timer;
unsigned int MA_Wait_Data_Timer;
unsigned int MA_Wait_Next_Req_Timer;
int MA_Write_Data;
int MA_Write_Data_Max;
int MA_Write_Data_Min;
char MA_New_Req_Flg;
unsigned int MA_Item_Num;
unsigned int MA_Read_Cnt;
unsigned char MA_Read_Data[MAX_DATA_NUM];
unsigned int MA_Read_ID;

/* USER code section end */

