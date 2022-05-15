#include "lcd.h"

/*void SysTick_wait(unsigned long delay){
	NVIC_ST_CTRL_R =0x00;
	NVIC_ST_RELOAD_R= delay-1;
	NVIC_ST_CURRENT_R=0;
	NVIC_ST_CTRL_R =0x05;
	while((NVIC_ST_CTRL_R & 0x00010000)==0){//wait for count flag
	} 
}*/

/*void genericDelay(unsigned long time){
	int i;
	for(i=0; i<time ;i++){
		SysTick_wait(16000); //1msec
	}
}*/
void LCD_cmd(unsigned char cmd){
	GPIO_PORTB_DATA_R=cmd;
	writePin('A',RS,0);
	writePin('A',RW,0);
	writePin('A',E,1);
	genericDelay(2);
	writePin('A',E,0);
}

void init_LCD(void){
	
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
