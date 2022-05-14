#include "lcd.h"
#include "timer.h"

int main(void){

	LCD_Init();
	LCD4bits_Cmd(lcd_clear);
	LCD4bits_Cmd(Curs_1stRow);
	lcd_send_string("popcorn"); //display the string 
	//statesDelay(62000);
	
}
