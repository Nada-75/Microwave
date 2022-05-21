#include "tm4c123gh6pm.h"
#include "IO.h"
#include "timer.h"
#include "lcd.h"

void LCD_cmd(unsigned char cmd){
	GPIO_PORTB_DATA_R=cmd;
	writePin('A',RS,0);
	writePin('A',RW,0);
	writePin('A',E,1);
	genericDelay(2);
	writePin('A',E,0);
}

void init_LCD(void){
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
	
	LCD_cmd(Set_8bit); //8-bit mode
	genericDelay(1);
	LCD_cmd(CLR_display); //Clear LCD display screen
	genericDelay(1);
	LCD_cmd(Return_Home); //Return home
	genericDelay(1);
	LCD_cmd(RShiftCurs); //increment cursor
	genericDelay(1);
	LCD_cmd(Curs_1stRow); //go to zero position
	genericDelay(1);
}
void LCD_write(unsigned char data){
	GPIO_PORTB_DATA_R=data; //send data to portB
	writePin('A',RS,1);
	writePin('A',RW,0);
	writePin('A',E,1);
	genericDelay(2);
	writePin('A',E,0);
}
void LCD_WriteStr(char * str)
{  
	volatile int i = 0;          	//i must be pulled from memory 
	while(*(str+i) != '\0')       	//Continue until you find the Null-Terminating Character.
	{
		LCD_write(*(str+i)); //Print each character of the string on the LCD
		i++;                        
	}
}
