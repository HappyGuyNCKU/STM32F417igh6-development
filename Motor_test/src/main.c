#include "main.h"

int main() {

    initgpio();
    rotate();

   return 0;

}


void initgpio() {

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef gpio;
    GPIO_StructInit(&gpio);
    gpio.GPIO_Mode = GPIO_Mode_OUT;
    gpio.GPIO_Pin = motor_out;
    GPIO_Init(GPIOB, &gpio);

    gpio.GPIO_Mode = GPIO_Mode_IN;
    gpio.GPIO_Pin = motor_in;
    GPIO_Init(GPIOB, &gpio);
}

/*0:OPEN, 1:CLOSE, 2:FULL_OPENED, 3:FULL_CLOESD*/

void rotate(){


    GPIO_ResetBits(GPIOB, ctrl[0]);
    GPIO_SetBits(GPIOB, ctrl[1]);


    while(1){
	
	if(GPIO_ReadInputDataBit(GPIOB, ctrl[2])){

	    GPIO_ResetBits(GPIOB, ctrl[0]);
	    GPIO_SetBits(GPIOB, ctrl[1]);

	}else if(GPIO_ReadInputDataBit(GPIOB, ctrl[3])){

	    GPIO_ResetBits(GPIOB, ctrl[1]);
	    GPIO_SetBits(GPIOB, ctrl[0]);

	}
    }

}

void _init(void) {return;}
