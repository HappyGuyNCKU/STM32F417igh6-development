#ifndef USART_h
#define USART_h

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_usart.h"
#include "misc.h"
#include <stdio.h>

#define MAX_STRLEN 50

void GPIO_Configuration(uint16_t TX, uint16_t RX);
void USART_Configuration();
void NVIC_Configuration();

void SendData(USART_TypeDef *USARTx, volatile char str[]);

#endif
