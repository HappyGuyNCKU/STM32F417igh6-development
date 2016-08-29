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

    /* TX & RX */
    GPIO_InitStructure.GPIO_Pin = TX | RX;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);  

    /* define alternative function */
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);	
	
}

/*****************************************************************
* Function Name  : USART_Configuration
* Description    : Configures the USART1
******************************************************************/
void USART_Configuration(){

    USART_InitTypeDef USART_InitStructure;	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	/* USART1 */
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART1, &USART_InitStructure);
	
    USART_Cmd(USART1, ENABLE);

	USART_ITConfig(USART1, USART_IT_RXNE,ENABLE);
}

/*****************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures the nested vectored interrupt controller.
******************************************************************/
void NVIC_Configuration(){
	
	NVIC_InitTypeDef NVIC_InitStructure;

	/* USART1 interrupt channel */

	NVIC_EnableIRQ(USART1_IRQn);

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}

/*****************************************************************
* Function Name  : SendData
* Description    : Sending data  
******************************************************************/
void SendData(USART_TypeDef *USARTx, volatile char str[])
{
	while(*str != '\0') {
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
		USART_SendData(USARTx, *str);
		str++;
	}
}

/*****************************************************************
* Function Name  : USART1_IRQHandler
* Description    : usart1 interrupt handler
******************************************************************/
void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
		SendData(USART1, "Interrupt trigger"); 
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }
}
