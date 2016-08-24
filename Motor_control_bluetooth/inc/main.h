#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "usart.h"

const uint16_t TX = GPIO_Pin_9;
const uint16_t RX = GPIO_Pin_10;

const uint16_t motor_out = GPIO_Pin_3 | GPIO_Pin_5;
const uint16_t motor_in  = GPIO_Pin_7 | GPIO_Pin_8;

/*0:OPEN, 1:CLOSE, 2:FULL_OPENED, 3:FULL_CLOESD*/
const uint16_t ctrl[4] = {GPIO_Pin_3, GPIO_Pin_5, GPIO_Pin_7, GPIO_Pin_8};


void init_motor_gpio();
void rotate();
void delay();
