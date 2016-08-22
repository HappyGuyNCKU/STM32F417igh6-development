#include "usart.h"
/*
    STM32F417igh6
    PA2  (UART1 Tx)
    PA3  (UART1 Rx)
*/

volatile unsigned char received_string[MAX_STRLEN]; //hold the recieved string
unsigned char Receive_data;
uint8_t Receive_String_Ready = 0;

/*****************************************************************
* Function Name  : GPIO_Configuration
* Description    : Configures the different GPIO ports
******************************************************************/
void GPIO_Configuration(uint16_t TX, uint16_t RX){

    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

/*	GPIO_InitStructure.GPIO_Pin = TX | RX;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); */

    /* TX */
    GPIO_InitStructure.GPIO_Pin = TX;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_Init(GPIOA, &GPIO_InitStructure); 

    /* RX */
    GPIO_InitStructure.GPIO_Pin = RX;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;// floating 
    GPIO_Init(GPIOA, &GPIO_InitStructure);  

    /* define alternative function */
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);	

}

/*****************************************************************
* Function Name  : USART_Configuration
* Description    : Configures the USART2
******************************************************************/
void USART_Configuration(){	
	
    USART_InitTypeDef USART_InitStructure;	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	/* USART2 */
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART2, &USART_InitStructure);
	
    USART_Cmd(USART2, ENABLE);

	USART_ITConfig(USART2, USART_IT_RXNE,ENABLE);
}

/*****************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures the nested vectored interrupt controller.
******************************************************************/
void NVIC_Configuration(){
	
	NVIC_InitTypeDef NVIC_InitStructure;

	/* USART2 interrupt channel */
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}

/*****************************************************************
* Function Name  : SendData
* Description    : Sending data  
******************************************************************/
void SendData(USART_TypeDef *USARTx, volatile unsigned char str[])
{
	while(*str) {
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
		USART_SendData(USARTx, *str);
		str++;
	}
}

/*****************************************************************
* Function Name  : USART2_IRQHandler
* Description    : usart2 interrupt handler
******************************************************************/
void USART2_IRQHandler(){
	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) {
        SendData(USART2, "ininder");
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);
    }
}

/*	if(USART_GetITStatus(USART2, USART_IT_RXNE)) {

//		Receive_data = USART_ReceiveData(USART2);
		
		static uint8_t cnt = 0;

		if(cnt < MAX_STRLEN) {
			received_string[cnt] = Receive_data;
			if(received_string[cnt] != NULL){
				Receive_String_Ready = 1;
				cnt = 0;
			}
			else{
				cnt ++;
			}			
		}
		else{
			Receive_String_Ready = 1;
			cnt =0;
		}
		if(Receive_String_Ready){
			SendData(USART2, received_string);
			Receive_String_Ready = 0;
			int i = 0;
			for(;i<MAX_STRLEN;i++){
				received_string[i] = 0;
			}
		}
	}
}*/
