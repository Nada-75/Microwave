# include "C:\Keil\Labware\inc\tm4c123gh6pm.h"
# include "stdint.h"
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
unsigned int KeypadConversionWeight()
{ unsigned int a;
	unsigned char x = KeypadScan();
	 a= x-'0';
	return a ;
}

unsigned int KeypadConversionDigit()
{ unsigned int a;
	unsigned char x = KeypadScan();
 if ((x!= 'A' )& (x!= 'B') &( KeypadScan()!= 'C') & (x!= 'D') & (x!= '#' )& (x!= '*' ) ){	//input '0'is will be handled
 a= x-'0';
	return a ;}
else {
lcd_send_string("Err");//
genericDelay(2000);//delay 2 sec
Clear_display();
 KeypadConversionDigit();
}

}
unsigned long cookingtime_D(){
unsigned int arr=[4];
for
while( Button_read( F,  4)!=0)//sw1 not pressed
{KeypadConversionDigit();
arr[0]=
