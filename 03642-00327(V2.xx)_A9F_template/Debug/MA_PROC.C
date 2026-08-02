/*
FileName: ma_proc.c
Date: 2020-1-22
Time: 10:54:20
GUIDE version: 12.0.6.1567
*/

#include "ma_proc.h"
#include "ma_gbl.h"


/* USER code section begin */

void DM14_Recv_Data_Analyze(unsigned char* DM14_Recv_Data, DM14_MSG* data)
{
  data->Num_Req = ((DM14_Recv_Data[1] & 0xE0) << 3) + DM14_Recv_Data[0];
  data->Poi_Typ = (DM14_Recv_Data[1] >> 4) & 0x01;
  data->Command = (DM14_Recv_Data[1] >> 1) & 0x07;
  data->Address = (DM14_Recv_Data[4] <<16) + (DM14_Recv_Data[3] << 8) + DM14_Recv_Data[2];
  data->Key     = (DM14_Recv_Data[7] << 8) + DM14_Recv_Data[6];
}

void DM15_Send_Data_Make(unsigned char* DM15_Send_Data, DM15_MSG* data)
{
  DM15_Send_Data[0] = data->Num_Allow & 0xFF;
  DM15_Send_Data[1] = (((data->Num_Allow >> 8) & 0x07) << 5) + ((data->Status & 0x07) << 1) + 0x011;
  DM15_Send_Data[2] = data->EDC_Para & 0xFF;
  DM15_Send_Data[3] = (data->EDC_Para >> 8) & 0xFF;
  DM15_Send_Data[4] = (data->EDC_Para >> 16) & 0xFF;
  DM15_Send_Data[5] = data->EDCP_Ext;
  DM15_Send_Data[6] = data->Seed & 0xFF;
  DM15_Send_Data[7] = (data->Seed >> 8) & 0xFF;
}


void DM16_Send_Data_Make(unsigned char* DM16_Send_Data, unsigned char Num, unsigned char* data)
{
  int i;

  for(i = 0; i < Num; i++)
  {
    DM16_Send_Data[i] = data[i];
  }
}


void DM16_Recv_Data_Analyze(unsigned char* DM16_Recv_Data, DM16_MSG* data)
{
  int i;
  data->Num_Data = DM16_Recv_Data[0];

  for(i = 0; i < data->Num_Data; i++)
  {
    data->Bin_Data[i] = DM16_Recv_Data[data->Num_Data - i];
  }
}

unsigned int Seed_Make(unsigned int cnt)
{
  unsigned int seed;

  srand(cnt);
  seed = rand() & 0xFFFF;

  return seed;
}

int decrypt(int data)
{
  int key = 0x64326432;
  
  data = data ^ key;
  
  return data;
}

int encrypt(int data)
{
  int key = 0x64326432;
  
  data = data ^ key;
  
  return data;
}

int Error_Check_State0(DM14_MSG* msg, A_POINTER* poi)
{
  int ret;
  if(msg->Command == WRITE_REQ)
  {
    ret = Check_Write_Data(msg,poi);
    return ret;
  }
  else if(msg->Command == READ_REQ)
  {
    ret = Check_Read_Data(msg,poi);
    return ret;
  }
  else//Not support command
  {
    return 0x000001;
  }
}

int Error_Check_State1(DM14_MSG* msg)
{
  if(msg->Key == MA_Key)
  {
    return 0x000000;
  }
  else
  {
    return 0x001003;
  }
}

int Error_Check_State2(DM16_MSG* msg)
{

  if((MA_Write_Data >= MA_Write_Data_Min) && (MA_Write_Data <= MA_Write_Data_Max))
  {
    return 0x000000;
  }
  else
  {
    return 0x000109;
  }
}

int Error_Check_State3(unsigned int* data)
{
  if(*data == MA_Write_Data)
  {
    return 0x000000;
  }
  else
  {
    return 0x000023;
  }
}

int Error_Check_State4(DM14_MSG* msg, A_POINTER* poi)
{
  int ret;
  if(msg->Command == WRITE_REQ)
  {
    ret = Check_Write_Data(msg,poi);
    if(ret == 0)
    {
      MA_New_Req_Flg = ON; //New Req Flg ON
    }
    return ret;
  }
  else if(msg->Command == READ_REQ)
  {
    ret = Check_Read_Data(msg,poi);
    if(ret == 0)
    {
      MA_New_Req_Flg = ON; //New Req Flg ON
    }
    return ret;
  }
  else if(msg->Command == OPE_COMP)
  {
    return 0x000000;
  }
  else//Not support command
  {
    return 0x000001;
  }
}

int array2data(unsigned char num,unsigned char* arr)
{
  int ret;
  switch (num)
  {
    case 1://1Byte
      ret = (arr[0]);
      break;
    case 2://2Byte
      ret = (arr[0] <<  8) + arr[1];
      break;
    case 4://4Byte
      ret = (arr[0] << 24) + (arr[1] << 16) + (arr[2] << 8) + arr[3];
      break;
    default:
      break;
  }
  return ret;
}

void data2array(unsigned char num, int data, unsigned char* arr)
{
  int i;
  
  for(i = 0 ; i < num ; i++)
  {
    arr[i] = data & 0xFF;
    data = data >> 8;
  }
}

int Check_Write_Data(DM14_MSG* msg, A_POINTER* poi)
{
  int ret;
  int i;
  int j = 0;
  if(msg->Num_Req == 4) //Length=4 (Fixed)
  {
  for(i = 0; i < poi->Max_num; i++)
    {
    if (msg->Address == poi->Address[i])
      {
      MA_Num = msg->Num_Req;
      MA_Cmd = msg->Command;
      MA_Add = msg->Address;
      MA_Write_Data_Max = poi->Max[i];
      MA_Write_Data_Min = poi->Min[i];
      ret = 0x000000;

      j = 1;
      } 
    }
  if (j == 0)  //Not support address
    {
      ret = 0x000100;
    }
    else{}
 }
  else //Wrong data length
    {
      ret = 0x000102;
    }
  return ret;
}

int Check_Read_Data(DM14_MSG* msg, A_POINTER* poi)
{
  int ret;
  if((msg->Address > 0) && (msg->Address <= poi->Max_id) && (msg->Address%4 == 1))
  {
      if((msg->Num_Req > 0)
         && (msg->Num_Req <= ((poi->Max_num * DATA_SIZE) - (msg->Address - 1)))
         && (msg->Num_Req%4 == 0))
      {
        MA_Num = msg->Num_Req;
        MA_Cmd = msg->Command;
        MA_Add = msg->Address;
        MA_Item_Num = MA_Num / DATA_SIZE;
        ret = 0x000000;      
      }
      else//Wrong data length
      {
        ret = 0x000102;
      }
  }
  else//Not support address
  {
    ret = 0x000100;
  }
  return ret;
}


/* USER code section end */

