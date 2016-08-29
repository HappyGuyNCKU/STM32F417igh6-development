/**
  ******************************************************************************
  * @file    DS18B20.c
  * @author  ligh (modify by Hua)
  * @brief   This file contains all the functions prototypes for the DS18B20 circuit
  ******************************************************************************
**/
    
#include "DS18B20.h"  
  
#define EnableINT()    
#define DisableINT()   
  
#define DS_PORT      GPIOI  
#define DS_IO_PIN    GPIO_Pin_2  
#define DS_RCC_PORT  RCC_AHB1Periph_GPIOI  
#define DS_PRECISION 0x3f //precision 1f=9bits; 3f=10bits; 5f=11bits; 7f=12bits;  
#define DS_AlarmTH   0x64  
#define DS_AlarmTL   0x00  
#define DS_CONVERT_TICK 1000  
  
#define ResetDQ() GPIO_ResetBits(DS_PORT,DS_IO_PIN)  
#define SetDQ()   GPIO_SetBits(DS_PORT,DS_IO_PIN)  
#define GetDQ()   GPIO_ReadInputDataBit(DS_PORT,DS_IO_PIN)  
   
   
static unsigned char TempX_TAB[16]={0x00,0x01,0x01,0x02,0x03,0x03,0x04,0x04,0x05,0x06,0x06,0x07,0x08,0x08,0x09,0x09};  
   
unsigned char ResetDS18B20(void)  
{  
	unsigned char resport;  
	SetDQ();  
	delay_us(50);  
	ResetDQ();  
	delay_us(500);  //500us (480~960us)  
	SetDQ();  
//	delay_us(60);  //40us  
 
	while(GetDQ()); 
	delay_us(500);  //500us  
	SetDQ();  
	return resport;  
}  
  
void DS18B20WriteByte(unsigned char Dat)  
{  
	unsigned char i;  
	for( i=8; i>0; i--){  
		ResetDQ();     
		delay_us(5);

		if(Dat & 0x01){  
			SetDQ();  
		}else{  
			ResetDQ();
		} 
 
		delay_us(65);
		SetDQ();
		delay_us(2); //must more than 1us between 2 bits  
		Dat >>= 1;   
	}   
}  
  
  
unsigned char DS18B20ReadByte(void)  
{  
	unsigned char i,Dat;  
	SetDQ();  
	delay_us(5);  
	for( i=8; i>0; i--){
		Dat >>= 1;  
		ResetDQ();  
		delay_us(5);
		SetDQ();  
		delay_us(5);
  
		if(GetDQ()){  
			Dat|=0x80;
		}else{
			Dat&=0x7f;
		}  

		delay_us(65);  
		SetDQ();  
	}  
	return Dat;  
}  
  
  
void ReadRom(unsigned char *Read_Addr)  
{  
	unsigned char i;  
  
	DS18B20WriteByte(ReadROM);  
    
	for( i=8; i>0; i--){  
		*Read_Addr=DS18B20ReadByte();  
		Read_Addr++;  
	}  
}  
  
  
void DS18B20Init(unsigned char Precision,unsigned char AlarmTH,unsigned char AlarmTL)  
{  
	DisableINT();  
	ResetDS18B20();  
	DS18B20WriteByte(SkipROM);   
	DS18B20WriteByte(WriteScratchpad);  
	DS18B20WriteByte(AlarmTL);  
	DS18B20WriteByte(AlarmTH);  
	DS18B20WriteByte(Precision);  
  
	ResetDS18B20();  
	DS18B20WriteByte(SkipROM);   
	DS18B20WriteByte(CopyScratchpad);  
	EnableINT();  
	while(!GetDQ());  //waiting DS18B20 
}  
  
  
void DS18B20StartConvert(void)  
{  
	DisableINT();  
	ResetDS18B20();  
	DS18B20WriteByte(SkipROM);   
	DS18B20WriteByte(StartConvert);   
	EnableINT();  
}  
  
void DS18B20_Configuration(void)  
{  
	GPIO_InitTypeDef GPIO_InitStructure;     
	RCC_AHB1PeriphClockCmd(DS_RCC_PORT, ENABLE);  
  
	GPIO_InitStructure.GPIO_Pin = DS_IO_PIN;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	GPIO_Init(DS_PORT, &GPIO_InitStructure);
}  
  
  
void DS18B20_start(void)  
{  
	DS18B20_Configuration();  
	DS18B20Init(DS_PRECISION, DS_AlarmTH, DS_AlarmTL);  
	DS18B20StartConvert();  
}  
  
  
unsigned short DS18B20_read(void)  
{  
	unsigned char TemperatureL,TemperatureH;  
	unsigned int  Temperature;  
  
	DisableINT();  
	ResetDS18B20();  
	DS18B20WriteByte(SkipROM);   
	DS18B20WriteByte(ReadScratchpad);  
	TemperatureL = DS18B20ReadByte();  
	TemperatureH = DS18B20ReadByte();   
	ResetDS18B20();  
	EnableINT();  
  
	if(TemperatureH & 0x80){  
		TemperatureH=(~TemperatureH) | 0x08;  
		TemperatureL=~TemperatureL+1;  
		if(TemperatureL==0)  
		TemperatureH+=1;  
	}  
  
	TemperatureH=(TemperatureH<<4)+((TemperatureL&0xf0)>>4);  
	TemperatureL=TempX_TAB[TemperatureL&0x0f];  
  
	//bit0-bit7 => decimal，bit8-bit14 => interger，bit15 sign bit  
	Temperature=TemperatureH;  
	Temperature=(Temperature<<8) | TemperatureL;   
  
	DS18B20StartConvert();  
  
	return  Temperature;  
}
