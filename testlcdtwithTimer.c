#include "lcd.h"

int main(void){
	SYSCTL_RCGCGPIO_R|=0x03;
	while(!(SYSCTL_PRGPIO_R&0x03));
	GPIO_PORTA_LOCK_R=0X4C4F434B;
	GPIO_PORTA_CR_R=0xFF;
	GPIO_PORTA_DEN_R=0xFF;
	GPIO_PORTA_AMSEL_R&=~0xFF;
	GPIO_PORTA_AFSEL_R&=~0xFF;
	GPIO_PORTA_PCTL_R&=~0xFFFFFF00;
	
	GPIO_PORTB_LOCK_R=0X4C4F434B;
	GPIO_PORTB_CR_R=0xFF;
	GPIO_PORTB_DEN_R|=0xFF;
	GPIO_PORTB_AMSEL_R&=~0xFF;
	GPIO_PORTB_AFSEL_R&=~0xFF;
	GPIO_PORTB_PCTL_R&=~0xFFFF; 
	
	GPIO_PORTB_DIR_R=0xFF;
	GPIO_PORTA_DIR_R=0xFF;
	
	
	init_LCD();
	genericDelay(100);
	LCD_cmd(CursOff_DisON);
	genericDelay(100);
	
		//LCD_WriteStr("popcorn");
	  //genericDelay(100);
	
   statesDelay(D_delay(10,1));

}
