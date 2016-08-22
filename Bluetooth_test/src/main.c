#include "main.h"

int main() {

	/* initialization */
	GPIO_Configuration(TX, RX);
	USART_Configuration();
	NVIC_Configuration();

	char a[]="Hello, this is STM32F417.";

	/* recive and send data */
	SendData(USART1, a);

	while(1);

}

void _init(void) {return;}
