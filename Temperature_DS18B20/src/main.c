#include "main.h"

int main() {

	/* initialization */
	GPIO_Configuration(TX, RX);
	USART_Configuration();
	NVIC_Configuration();
	SysTick_Init();
	DS18B20_start();

	char a[] = "Hello, this is STM32F417.\n";
	uint16_t data;
	char b, c;
	char cold[5];

	cold[4] = '\0';
	cold[2] = '.';

	/* recive and send data */
	SendData(USART1, a);

	while(1){
		data = DS18B20_read();
		b = data >> 8;
		c = data & 0b0000000011111111;
		cold[0] = (b / 10) + 48;
		cold[1] = (b % 10) + 48;
		cold[3] = (c % 10) + 48;
//		delay_ms(500);
		SendData(USART1, cold);
		SendData(USART1, "\n");
		delay_ms(650);
	};
}

void _init(void) {return;}
