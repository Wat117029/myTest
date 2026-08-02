/*
FileName: ma_gbl.h
Date: 2020-1-30
Time: 11:16:35
GUIDE version: 12.0.6.1567
*/

#ifndef __MA_GBL_H__
#define __MA_GBL_H__

#include "ma_proc.h"

/* USER code section begin */

extern unsigned int MA_State;
extern unsigned int MA_Num;
extern unsigned int MA_Key;
extern unsigned int MA_Seed;
extern unsigned int MA_Cmd;
extern unsigned int MA_Add;
extern unsigned int MA_Wait_Key_Timer;
extern unsigned int MA_Wait_Data_Timer;
extern unsigned int MA_Wait_Next_Req_Timer;
extern int MA_Write_Data;
extern int MA_Write_Data_Max;
extern int MA_Write_Data_Min;
extern char MA_New_Req_Flg;
extern unsigned int MA_Item_Num;
extern unsigned int MA_Read_Cnt;
extern unsigned char MA_Read_Data[MAX_DATA_NUM];
extern unsigned int MA_Read_ID;

/* USER code section end */


#endif

