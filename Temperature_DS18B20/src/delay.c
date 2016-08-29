/**
  ******************************************************************************
  * @file    delay.c
  * @author   (modify by Hua)
  * @brief   This file define the delay function by Systick.
  ******************************************************************************
**/

#include "delay.h"

static volatile unsigned int sysTickCounter;
 
/***************************************
 *	SystemFrequency/1000      1ms      *
 *	SystemFrequency/100000    10us     *
 *	SystemFrequency/1000000   1us      *
 ***************************************/

void SysTick_Init(void) {
	while (SysTick_Config(168000000/1000000) != 0) {
	}
}
 
void TimeTick_Decrement(void) {
	if (sysTickCounter != 0x00) {
		sysTickCounter--;
	}
}
 
void delay_us(unsigned int us) {
	sysTickCounter = us;
	while (sysTickCounter != 0) {
	}
}
 
void delay_1ms(void) {
	sysTickCounter = 1000;
	while (sysTickCounter != 0) {
	}
}
 
void delay_ms(unsigned int ms) {
	while (ms--) {
		delay_1ms();
	}
}

void SysTick_Handler(void) {
	TimeTick_Decrement();
}
