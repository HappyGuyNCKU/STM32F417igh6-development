#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

const uint16_t LEDS = GPIO_Pin_7 | GPIO_Pin_8;
const uint16_t LED[2] = {GPIO_Pin_7, GPIO_Pin_8};

void initLeds();
void LEDs();
void delay(uint32_t ms);
