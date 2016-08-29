/**
  ******************************************************************************
  * @file    DS18B20.h
  * @author  ligh (modify by Hua)
  * @brief   This file contains all the functions prototypes for the DS18B20 circuit
  ******************************************************************************
**/  
  
#ifndef __DS18B20_H  
#define __DS18B20_H  

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "delay.h"
#include "usart.h"
  
#define  SkipROM    0xCC
#define  SearchROM  0xF0
#define  ReadROM    0x33
#define  MatchROM   0x55
#define  AlarmROM   0xEC
  
#define  StartConvert    0x44  
#define  ReadScratchpad  0xBE  //read 9 bytes in registers 
#define  WriteScratchpad 0x4E  //write waring temperature TH/TL into register  
#define  CopyScratchpad  0x48  //copy waring temperature to EEPROM
#define  RecallEEPROM    0xB8  //copy waring temperature to register
#define  ReadPower       0xB4  //read power supply mode:0 parasite power
							   // 0 => parasite power, 1 => external power
  
  
void DS18B20_start(void);  
unsigned short DS18B20_read(void);  
  
  
#endif  
