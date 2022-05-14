#define RS 0x01				 	//RS -> PB0 (0x01)
#define EN 0x04  		 	 	//EN -> PB2 (0x04)
#define lcd_clear 0x01
#include "tm4c123gh6pm.h"

//Macros of commands
#define CLR_display   0x01
#define RShiftCurs    0x06
#define Turn_On       0x0F
#define Curs_1stRow   0x80
#define Curs_2ndRow   0xc0
#define Set_4bit      0x28
#define Set_8bit      0x38
#define CursOff_DisON 0x0c

void delay_micro(int n);
void LCD_Write4bits(unsigned char data, unsigned char control);
void LCD4bits_Data(unsigned char data);
void lcd_send_string(char *str);
void LCD4bits_Cmd(unsigned char command);
void LCD_Init(void);
void systick_delay_msec(int t);
