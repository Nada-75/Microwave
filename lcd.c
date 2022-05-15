//LATER I WIILL ADD DELAY FUNCTION IN TIMER.H AFTER TESTING
#include "tm4c123gh6pm.h"
#include "lcd.h"
 
void delay_micro(int n){
int i,j;
for(i=0;i<n;i++)
for(j=0;j<3;j++)
{}
}
 
//systick delay functions
void SysTick_Wait(unsigned long delay) // delay = number of ticks
{
NVIC_ST_CTRL_R = 0X00;
NVIC_ST_RELOAD_R = delay - 1;
NVIC_ST_CURRENT_R = 0;
NVIC_ST_CTRL_R = 0X05; // ENABLE TIMER AND CLK SRC
while((NVIC_ST_CTRL_R&0x00010000)==0) 
{
//wait for count flag
}
}
 
void SysTick_Wait1ms()
{
SysTick_Wait(16000);
}
void systick_delay_msec(int t) //delay by milli seconds.
{
int i; 
for(i=0; i<t; i++)
{
SysTick_Wait1ms();
}
}
 
void LCD_Write4bits(unsigned char data, unsigned char control) //control is RS value , data coming will be in the format of 1234 0000
{
	data &= 0xF0;                       		   	//clear lower 4-bits for control 
	control &= 0x0F;                    				//clear upper 4-bits for data
	GPIO_PORTB_DATA_R = data | control;         //Include RS value (command or data ) with data 
	GPIO_PORTB_DATA_R  = data | control | EN;   //pulse EN
	delay_micro(0);													    //delay for pulsing EN
	GPIO_PORTB_DATA_R  = data | control;				//Turn off the pulse EN
	GPIO_PORTB_DATA_R  = 0;                     //Clear the Data 
}
 
void LCD4bits_Data(unsigned char data)
{
	LCD_Write4bits(data & 0xF0 , RS);   //send the Upper 4-bits
	LCD_Write4bits(data << 4 , RS);     //then the Lower 4-bits
	delay_micro(40);		    //Delay for LCD 
}
 
void lcd_send_string(char * str)
{  
	volatile int i = 0;          	//i must be pulled from memory 
	while(*(str+i) != '\0')       	//Continue until you find the Null-Terminating Character.
	{
		LCD4bits_Data(*(str+i)); //Print each character of the string on the LCD
		i++;                        
	}
}
 
void LCD4bits_Cmd(unsigned char command)
{
	LCD_Write4bits(command & 0xF0 , 0);    //upper 4-bits first
	LCD_Write4bits(command << 4 , 0);      //then lower 4-bits
 
	if(command < 4)
		systick_delay_msec(2);          //commands 1 and 2 need around ~1.64ms (Check LCD Delays Table)
	else
		delay_micro(40);      //other commands take 40 us
}
 
void LCD_Init(void)
{
	SYSCTL_RCGCGPIO_R |= 0x02;    //enable clock for PORT B
	systick_delay_msec(10);       //Wait 10 ms to enable the clock of PORTB
  GPIO_PORTB_DIR_R |= 0xFF;     //Set Port B Pins as Output Pins
	GPIO_PORTB_DEN_R |= 0xFF;     //Enable Port B Digital
	LCD4bits_Cmd(0x28);          //2 lines and 5x7 character (4-bit data, D4 to D7) 
	LCD4bits_Cmd(0x06);          //Automatic Increment cursor (shift cursor to right)
	LCD4bits_Cmd(lcd_clear);		 //Clear display screen
	LCD4bits_Cmd(0x0F);          //Cursor Blink
}
