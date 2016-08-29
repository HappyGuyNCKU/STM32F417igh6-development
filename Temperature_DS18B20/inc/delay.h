/**
  ******************************************************************************
  * @file    delay.h
  * @author   (modify by Hua)
  * @brief   This file define the delay function by Systick.
  ******************************************************************************
**/
#ifndef __DELAY_H
#define __DELAY_H
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"
#include "core_cm4.h"
 
void SysTick_Init(void);
void TimeTick_Decrement(void);
void delay_us(unsigned int us);
void delay_1ms(void);
void delay_ms(unsigned int ms);
 
#endif

