/*
FileName: ma_proc.h
Date: 2020-1-22
Time: 10:54:21
GUIDE version: 12.0.6.1567
*/

#ifndef __MA_PROC_H__
#define __MA_PROC_H__


/* USER code section begin */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>


//Const Define----------------------
#define MAX_DATA_NUM 1785
#define PROCEED      0
#define BUSY         1
#define WRITE_REQ    2
#define READ_REQ     1
#define OPE_COMP     4
#define OPE_FAIL     5
#define ON           1
#define OFF          0
#define WAIT_KEY_TIME_OUT     10000  //10sec(program period base is 1ms)
#define WAIT_DATA_TIME_OUT     10000  //10sec(program period base is 1ms)
#define WAIT_NEXT_REQ_TIME_OUT 100 //100msec(program period base is 1ms)

#define CURR_PROC_WRITE_REQ  0x000012
//#define MAX_ID      0x6D
//#define MAX_ITEM_NUM  28 // (0x6D+3)/4=28 
#define DATA_SIZE    4


//Struct Define-------------------

typedef struct
{
  unsigned int Num_Req;
  char Poi_Typ;
  unsigned int Command;
  unsigned long Address;
  unsigned int Key;
}DM14_MSG;

typedef struct
{
  unsigned int Num_Allow;
  int Status;
  long EDC_Para;
  char EDCP_Ext;
  unsigned int Seed;
}DM15_MSG;

typedef struct
{
  unsigned char Num_Data;
  unsigned char Bin_Data[MAX_DATA_NUM];  
}DM16_MSG;

typedef struct
{
  unsigned int Max_id;
  unsigned int Max_num;
  unsigned int Address[100]; 
  unsigned int Max[100]; 
  unsigned int Min[100];  
}A_POINTER;

//Function Define-------------------
void DM14_Recv_Data_Analyze(unsigned char* DM14_Recv_Data, DM14_MSG* data);
void DM16_Recv_Data_Analyze(unsigned char* DM16_Recv_Data, DM16_MSG* data);
void DM15_Send_Data_Make(unsigned char* DM15_Send_Data, DM15_MSG* data);
void DM16_Send_Data_Make(unsigned char* DM16_Send_Data, unsigned char Num, unsigned char* data);
unsigned int Seed_Make();
unsigned int Key_Make(unsigned int seed);
int decrypt(int data);
int encrypt(int data);
int Error_Check_State0(DM14_MSG* msg, A_POINTER* poi);
int Error_Check_State1(DM14_MSG* msg);
int Error_Check_State2(DM16_MSG* msg);
int Error_Check_State3(unsigned int* data);
int Error_Check_State4(DM14_MSG* msg, A_POINTER* poi);
int array2data(unsigned char num,unsigned char* arr);
void data2array(unsigned char num, int data, unsigned char* arr);
int Check_Write_Data(DM14_MSG* msg, A_POINTER* poi);
int Check_Read_Data(DM14_MSG* msg, A_POINTER* poi);
/* USER code section end */


#endif
