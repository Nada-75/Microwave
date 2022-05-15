//# include "tm4c123gh6pm.h"
//# include "stdint.h"
#include "lcd.h"
#include "timer.h"
#include "button driver.h"

unsigned char noPressed=0xFF;
unsigned char  array [4][4]={{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}};
void Port_Init(unsigned char portname);
unsigned char ReadPin (unsigned char portName,unsigned pinNum);
void Set_portDir(unsigned char port_name,unsigned char dierction);
void enable_PullUP (unsigned char port_name ,unsigned char pin_number);
void write_lownibble(unsigned char port_name,unsigned char data);
void writePin(unsigned char portName,unsigned char pinNumber,unsigned char data);

	
void Keypad_init(unsigned char portName)
{ 
	Port_Init('A');
	Set_portDir('A',0x0F);
	enable_PullUP ('A', 4);
	enable_PullUP ('A', 5);
	enable_PullUP ('A', 6);
	enable_PullUP ('A', 7);
	
}

unsigned char KeypadScan()
{
    unsigned char x,y,i;
	while(1) {
	for (x=0;x<4;x++)
		{ 	 write_lownibble('A',0x0F);
					writePin('A',x,0);
		
			for (y=0;y<4;y++)
		{
				i=ReadPin ('A',y+4);
					if(i==0) 
					return array[x][y];
		}
	}				return noPressed;
						 
}	
	 
}		


//This function get the numeric input from keypad and return its integer value
unsigned int KeypadConversionDigit()
{ unsigned int a;
	unsigned char x = KeypadScan();
 if ((x!= 'A' )& (x!= 'B') &( KeypadScan()!= 'C') & (x!= 'D') & (x!= '#' )& (x!= '*' ) ){	//input '0'is will be handled
 a= x-'0'; 
	return a ;}
else {
lcd_send_string("Err");//
genericDelay(2000);//delay 2 sec
Clear_display();//***********************************************************************************
 KeypadConversionDigit();
}
return 0;
}

//the function will take inputs for D, ddetermine minutes and seconds then display the countdown
void cookingtime_D(){ 
	unsigned int arr[4] = {0,0,0,0};
	int i ;
	while( Button_read( 'F',  4)!=0)//sw1 not pressed
	{
		for(i = 3 ; i>=0; i--)
		{		
			arr[i] = KeypadConversionDigit();	//we don't know if they(function and for loop) are in sync	
		}
	}
	int min = arr[1] + arr[0] * 10; //get minutes from the array
	int sec = arr[3] + arr[2] * 10; //get seconds from the array
	statesDelay(D_delay (sec, min)); //get the delay for custom and display the countdown
}


