#include "tm4c123gh6pm.h"

#define DataPins GPIO_PORTA_DATA_R
#define CTRLPins GPIO_PORTB_DATA_R
//macros of CTRLPins
#define E  0
#define RS 1
#define RW 2

//Macros of commands
#define ClrDisplay 0x01
//#define Return_curs   0x02
#define RShift_curs   0x06
#define Turn_On       0x0F
#define Curs_1stRow   0x80
#define Curs_2ndRow   0xc0
#define Set_4bit      0x28
#define Set_8bit      0x38
#define CursOff_DisON 0x0c

//Functions Prototype
void genericDelay(unsigned long time);
void lcd_send_cmd(unsigned char cmd);
void lcd_Init(void);
void lcd_send_char(unsigned char chr);
void lcd_send_string(char *str);
void lcd_move_curs(unsigned char row,unsigned char col);
