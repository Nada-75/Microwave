//# include "tm4c123gh6pm.h"
//# include "stdint.h"
#include "lcd.h"
#include "timer.h"
#include "button driver.h"
#include "IO.h"
#include "keypad driver.h"

#define noPressed  0xFF  


/*void Port_Init(unsigned char portname);
unsigned char ReadPin (unsigned char portName,unsigned pinNum);
void Set_portDir(unsigned char port_name,unsigned char dierction);
void enable_PullUP (unsigned char port_name ,unsigned char pin_number);
void write_lownibble(unsigned char port_name,unsigned char data);
void writePin(unsigned char portName,unsigned char pinNumber,unsigned char data);*/

	
void Keypad_init()
{ Port_Init('C');
	Port_Init('E');
	Set_pinDirection('C',4,0); //C4-C7 input
	Set_pinDirection('C',5,0);
	Set_pinDirection('C',6,0);
	Set_pinDirection('C',7,0);
	
	Set_pinDirection('E',0,1); //E0-E3 output
	Set_pinDirection('E',1,1);
	Set_pinDirection('E',2,1);
	Set_pinDirection('E',3,1); 
	
	enable_PullUP ('C', 4);   
	enable_PullUP ('C', 5);
	enable_PullUP ('C', 6);
	enable_PullUP ('C', 7);
	
}

unsigned char KeypadScan()
{	unsigned char returnvalue = noPressed;
	unsigned char  array [4][4]={{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}};
	unsigned char x,y,i;

	for (x=0;x<4;x++)
		{ 
		     	writePin( 'E',0, 1);
			    writePin( 'E',1, 1);
			     writePin( 'E',2, 1);
			   writePin( 'E',3, 1);
					writePin('E',x,0);
		
			for (y=0;y<4;y++)
		{
				i=ReadPin ('C',y+4);
					if(i==0) {
					returnvalue = array[x][y];
					return returnvalue; }
		}
	}				return returnvalue;
						 
}

//This function get the numeric input from keypad and return its integer value
unsigned int KeypadConversionDigit()
{ unsigned int a;
	unsigned char x = KeypadScan();
 if ((x!= 'A' )& (x!= 'B') &( KeypadScan()!= 'C') & (x!= 'D') & (x!= '#' )& (x!= '*' ) ){	//input '0'is will be handled
   a= x-'0'; //********************************************
	return a ;}
else {
LCD_WriteStr("Err"); //
genericDelay(2000);//delay 2 sec
LCD_cmd(CLR_display );//***********************DONE***************************************
 KeypadConversionDigit();
}
return 0;
}

//the function will take inputs for D, ddetermine minutes and seconds then display the countdown
void cookingtime_D(){ 
//	unsigned int arr[4] = {0,0,0,0};
	int number=0; //the 16 bit digit
	int i=0;
	int j;
 	
	while(KeypadScan()!='A')//sw1 not pressed
	{
		for(j = 3 ; j>=0; j--)
		{	
			i = KeypadConversionDigit();	//take the input every cycle
			number = (number<<4) | i; 
			//arr[i] = KeypadConversionDigit();	//we don't know if they(function and for loop) are in sync	
		}
	}
	int sec= number | 0xF + (number | 0xF0)*10; 
	int min= number | 0xF00+ (number | 0xF000)*10;
	
	//int min = arr[1] + arr[0] * 10; //get minutes from the array
	//int sec = arr[3] + arr[2] * 10; //get seconds from the array
	statesDelay(D_delay (sec, min)); //get the delay for custom and display the countdown
}

void cookingtime_Dtest(){ 
	 
char arr[4] = {'0','0','0','0'};
int i;
init_LCD();
do
{ while(keypadscan()==nopressed);
	arr[3]=KeypadConversionDigit();
	while(keypadscan()==nopressed);
	arr[2]=keypadscan();
	while(keypadscan()==nopressed);
	arr[1]=keypadscan();
	while(keypadscan()==nopressed);
	arr[0]=keypadscan();
	LCD_WriteStr(arr);

}
