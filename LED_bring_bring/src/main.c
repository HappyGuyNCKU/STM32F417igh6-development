#include "main.h"

int main() {

    initLeds();
    LEDs();

   return 0;

}


void initLeds() {

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef gpio;
    GPIO_StructInit(&gpio);
    gpio.GPIO_Mode = GPIO_Mode_OUT;
    gpio.GPIO_Pin = LEDS;
    GPIO_Init(GPIOB, &gpio);

}

void LEDs(){

    uint32_t counter = 0;

    while(1){

        GPIO_SetBits(GPIOB, LED[counter % 2]);
	delay(1000);
        GPIO_ResetBits(GPIOB, LEDS);

	counter++;
    }

}

void delay(uint32_t ms) {
    ms *= 3360;
    while(ms--) {
        __NOP();
    }
}

void _init(void) {return;}
