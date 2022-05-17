#include "UART.h"
#include "tm4c123gh6pm.h"
#include "stdint.h"
#include "string.h"

void UART0Init(){
	
	SYSCTL_RCGCUART_R|=SYSCTL_RCGCUART_R0;
	SYSCTL_RCGCGPIO_R|=SYSCTL_RCGCGPIO_R0;
	UART0_CTL_R&=~UART_CTL_UARTEN;
	UART0_IBRD_R=104;
	UART0_FBRD_R=11;
	UART0_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
	UART0_CTL_R|=(UART_CTL_UARTEN|UART_CTL_RXE|UART_CTL_TXE);
	GPIO_PORTA_AFSEL_R|=0x03;
	GPIO_PORTA_PCTL_R =(GPIO_PORTA_PCTL_R& ~0XFF)|(GPIO_PCTL_PA0_U0RX|GPIO_PCTL_PA1_U0TX);
	GPIO_PORTA_DEN_R |=0x03;
}


uint8_t UART0_READAvailable(){
  return ((UART0_FR_R &UART_FR_RXFE)==UART_FR_RXFE)? 0:1;
}

char UART0_READ(){
	while(UART0_READAvailable() !=1){};
    return (char) (UART0_DR_R & 0xFF);
}
void UART0_WRITE(char c){
  	while((UART0_FR_R & UART_FR_TXFE) ==UART_FR_TXFF);
	UART0_DR_R =c;
}

void getCommand(char *str, uint8_t maxlen){
	char c;
	int8_t i;
	for(i=0;i<maxlen;i++){
		c = UART0_READ();
		if(c=='\n'||c=='\r')
		{
			break;
		}
		else str[i]=c;
		UART0_WRITE(c);
	}
}
void UART_printStr(char *str){
	uint8_t i=0;
	while(str[i])
	{
		UART0_WRITE(str[i]);
		i++;
	}
}

