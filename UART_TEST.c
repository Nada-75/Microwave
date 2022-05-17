#include "tm4c123gh6pm.h"
#include "stdint.h"
#include "string.h"

void UART0_INIT(){
 SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R0;
 SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;

UART0_CTL_R &= ~ UART_CTL_UARTEN;
UART0_IBRD_R = 104;  
UART0_FBRD_R = 11;
UART0_LCRH_R |= (UART_LCRH_WLEN_8 | UART_LCRH_FEN)  ;
UART0_CTL_R = (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN);
  
GPIO_PORTA_AFSEL_R |= 0x03;
GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R &= ~0xFF)|(GPIO_PCTL_PA1_U0TX|GPIO_PCTL_PA0_U0RX);
GPIO_PORTA_DEN_R |= 0x03;
GPIO_PORTA_AMSEL_R &= ~0x03;  
}
void RGBLED_Init(void){
SYSCTL_RCGCGPIO_R |= 0x20;             //Port F Clock enable
while((SYSCTL_PRGPIO_R & 0x20)==0){};  //Delay
GPIO_PORTF_DIR_R |= 0x0E;              //Enable Output
GPIO_PORTF_AFSEL_R &= ~(0x0E);         //No alternate function
GPIO_PORTF_PCTL_R &= ~(0x0000FFF0);    //Clear PCTL bit
GPIO_PORTF_DEN_R |= 0x0E;              //Enable Digital Pins 3 2 1 
GPIO_PORTF_AMSEL_R &= ~(0x0E);         //Disable Analog Mode
GPIO_PORTF_DATA_R &= ~(0x0E);          //Initialize LEDS to be off  
}

void RGB_set(uint8_t mask){
  mask &= 0x0E;
  GPIO_PORTF_DATA_R |= mask;
}
void RGB_clear(uint8_t mask){
  mask &= 0x0E;
  GPIO_PORTF_DATA_R &= ~mask;
}


uint8_t UART0_Available(){
  return ((UART0_FR_R &UART_FR_RXFE)==UART_FR_RXFE)? 0:1;
}
char UART0_read(){
   while(UART0_Available() !=1){};
    return (char) (UART0_DR_R & 0xFF);
    }

void UART0_write(char data){
  while((UART0_FR_R & UART_FR_TXFF)==UART_FR_TXFF){};
    UART0_DR_R = data;
}

void getCommand(char *str,uint8_t maxLen){
  char c;
  int8_t i;
  for(i =0;i<maxLen;i++){
    c = UART0_read();
    if(c=='\n' || c=='\r'){ break;
    }
    else str[i]=c;
    UART0_write(c);
    
  }
  
}
void printstr(char *str){
  while(*str){
    UART0_write(*str);
    str++;
  }
}




int main(){
  const uint8_t bufferLen = 9;
  char command[bufferLen]={0};
  UART0_INIT();
  RGBLED_Init();
  while(1){
    printstr("Enter Command:\n");
   getCommand(command,bufferLen);
    if(strcmp(command, "RedOn")==0){
      RGB_set(0x02);
    }
    else if(strcmp(command, "RedOff")==0){
      RGB_clear(0x02);
    }
    else if(strcmp(command, "BlueOn")==0){
      RGB_set(0x04);
    }
    else if(strcmp(command, "BlueOff")==0){
      RGB_clear(0x04);
    }
    else if(strcmp(command, "GreenOn")==0){
      RGB_set(0x08);
    }
    else if(strcmp(command, "GreenOff")==0){
      RGB_clear(0x08);
    }
    else{
      RGB_clear(0x0E);
    }
    memset(command,0,bufferLen);
    UART0_write('\n');  
  }
}