/* This is the driver for  our Input output usage
   It contains functions to help managing ports' inialization 
	 and deal with registers
*/
//Included files 
#include "lcd.h"
#include "tm4c123gh6pm.h"
#include "timer.h"


//macros 
#define SET_BIT(REG,BIT) REG|=1<<BIT
#define CLR_BIT(REG, BIT) REG&=~(1<<BIT)
#define TOG_BIT(REG,BIT)  REG^= 1<<BIT
//Macros and prototypes for keypad
#define SET_BIT(REG,BIT) REG|=1<<BIT
#define CLR_BIT(REG, BIT) REG&=~(1<<BIT)
#define READ_BIT(REG,BIT) (REG&(1<<BIT))>>BIT
void RGBLEDS_Init(void);

void Keypad_init();
unsigned char noPressed =0xFF;
unsigned char KeypadScan();

unsigned char  array [4][4]={{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}};

//Functions
void Port_Init(unsigned char portname){
	switch(portname)
	{
		case 'A':
		case 'a':
		{
			SET_BIT(SYSCTL_RCGCGPIO_R,0);
			while(!(READ_BIT(SYSCTL_PRGPIO_R,0)));
			GPIO_PORTA_LOCK_R=0X4C4F434B;
			GPIO_PORTA_CR_R=0xFF;
			GPIO_PORTA_DEN_R=0xFF;
			break;
		}
		case 'B':
		case 'b':
		{
			SET_BIT(SYSCTL_RCGCGPIO_R,1);
			while(!(READ_BIT(SYSCTL_RCGCGPIO_R,1)));
			GPIO_PORTB_LOCK_R=0X4C4F434B;
			GPIO_PORTB_CR_R=0xFF;
			GPIO_PORTB_DEN_R=0xFF;
			break;
		}
		case 'C':
		case 'c':
		{
			SET_BIT(SYSCTL_RCGCGPIO_R,2);
			while(!(READ_BIT(SYSCTL_RCGCGPIO_R,2)));
			GPIO_PORTC_LOCK_R=0X4C4F434B;
			GPIO_PORTC_CR_R=0xFF;
			GPIO_PORTC_DEN_R=0xFF;
			break;
		}
		case 'D':
		case 'd':
		{
			SET_BIT(SYSCTL_RCGCGPIO_R,3);
			while(!(READ_BIT(SYSCTL_RCGCGPIO_R,3)));
			GPIO_PORTD_LOCK_R=0X4C4F434B;
			GPIO_PORTD_CR_R=0xFF;
			GPIO_PORTD_DEN_R=0xFF;
			break;
		}
		case 'E':
		case 'e':
		{
			SET_BIT(SYSCTL_RCGCGPIO_R,4);
			while(!(READ_BIT(SYSCTL_RCGCGPIO_R,4)));
			GPIO_PORTE_LOCK_R=0X4C4F434B;
			GPIO_PORTE_CR_R=0xFF;
			GPIO_PORTE_DEN_R=0xFF;
			break;
		}
		case 'F':
		case 'f':
		{
			SET_BIT(SYSCTL_RCGCGPIO_R,5);
			while(!(READ_BIT(SYSCTL_RCGCGPIO_R,5)));
			GPIO_PORTF_LOCK_R=0X4C4F434B;
			GPIO_PORTF_CR_R=0xFF;
			GPIO_PORTF_DEN_R=0xFF;
			break;
		}
	}
}
// a function read the values of any port 
unsigned char ReadPort(unsigned char portname){
	switch(portname){
		// port A
		case'A':
		case'a':
		{
			return GPIO_PORTA_DATA_R;
		}
		break;
		// port B		
		case'B':
		case'b':
		{
			return GPIO_PORTB_DATA_R;
		}
		break;
		// port C		
		case'C':
		case'c':
		{
			return GPIO_PORTC_DATA_R;
		}
		break;
		// port D		
		case'D':
		case'd':
		{
			return GPIO_PORTD_DATA_R;
		}
		break;
		// port E		
		case'E':
		case'e':
		{
			return GPIO_PORTE_DATA_R;
		}
		break;
		// port F		
		case'F':
		case'f':
		{
			return GPIO_PORTF_DATA_R;	
		}
		break;
		}
}
unsigned char ReadPin (unsigned char portName,unsigned pinNum)
{ while(1){

		switch(portName)
			
{   case 'A' :
	 return READ_BIT(GPIO_PORTA_DATA_R,pinNum);
    case 'B' :
	  return READ_BIT(GPIO_PORTB_DATA_R,pinNum);
		case 'C' :
	  return READ_BIT(GPIO_PORTC_DATA_R,pinNum);
		case 'D' :
	 return READ_BIT(GPIO_PORTD_DATA_R,pinNum);
		case 'E' :
	  return READ_BIT(GPIO_PORTE_DATA_R,pinNum);
		case 'F' :
	  return READ_BIT(GPIO_PORTF_DATA_R,pinNum);
}
}}
void writePin(unsigned char portName,unsigned char pinNumber,unsigned char data)
{
	switch (portName)
			
{   case 'A' :
		{if(data ==1)
		{SET_BIT(GPIO_PORTA_DATA_R,pinNumber);
		 break;
		}
		else
			{CLR_BIT(GPIO_PORTA_DATA_R,pinNumber);
		 break;
		} 
		}
		case 'B' :
	  {if(data ==1)
		{SET_BIT(GPIO_PORTB_DATA_R,pinNumber);
		 break;
		}
		else
			{CLR_BIT(GPIO_PORTB_DATA_R,pinNumber);
		 break;
		} 
		}
		case 'C' :
	 {if(data ==1)
		{SET_BIT(GPIO_PORTC_DATA_R,pinNumber);
		 break;
		}
		else
			{CLR_BIT(GPIO_PORTC_DATA_R,pinNumber);
		 break;
		} 
		}
		case 'D' :
	 {if(data ==1)
		{SET_BIT(GPIO_PORTD_DATA_R,pinNumber);
		 break;
		}
		else
			{CLR_BIT(GPIO_PORTD_DATA_R,pinNumber);
		 break;
		} 
		}
		case 'E' :
	  {if(data ==1)
		{SET_BIT(GPIO_PORTE_DATA_R,pinNumber);
		 break;
		}
		else
			{CLR_BIT(GPIO_PORTE_DATA_R,pinNumber);
		 break;
		} 
		}
		case 'F':
{if(data ==1)
		{SET_BIT(GPIO_PORTA_DATA_R,pinNumber);
		 break;
		}
		else
			{CLR_BIT(GPIO_PORTA_DATA_R,pinNumber);
		 break;
		} 
		}
}
}

//Pull up pin function 
void enable_PullUP (unsigned char port_name, unsigned char pin_num){ //set the  pullup pin in the wanted port to 1 
	switch (port_name){
		//A
		case 'A':
		case 'a': 
		{SET_BIT(GPIO_PORTA_PUR_R, pin_num);
		 break;
		}
	  //B
		case 'B':
		case 'b': 
		{SET_BIT(GPIO_PORTB_PUR_R, pin_num);
		 break;
		}
	  //C
		case 'C':
		case 'c': 
		{SET_BIT(GPIO_PORTC_PUR_R, pin_num);
		 break;
		}
	 //D
		case 'D':
		case 'd': 
		{SET_BIT(GPIO_PORTD_PUR_R, pin_num);
		 break;
		}
	//E
		case 'E':
		case 'e': 
		{SET_BIT(GPIO_PORTE_PUR_R, pin_num);
		 break;
		}
   //F
		case 'F':
		case 'f': 
		{SET_BIT(GPIO_PORTF_PUR_R, pin_num);
		 break;
		}
	}

}


// set the direction of pin
void Set_pinDirection (unsigned char port_name, unsigned char pin_num, unsigned char direction){ //set the bin in the wanted port to 1 or 0
	switch (port_name){
		//A
		case 'A':
		case 'a': 
		{if(direction ==1)
		{SET_BIT(GPIO_PORTA_DIR_R, pin_num);
		 break;
		}
		else
			{CLR_BIT(GPIO_PORTA_DIR_R, pin_num);
		 break;
		} }
		//B
		case 'B':
		case 'b': 
		{if(direction ==1)
		{SET_BIT(GPIO_PORTB_DIR_R, pin_num);
		 break;
		}
		else
			{CLR_BIT(GPIO_PORTB_DIR_R, pin_num);
		 break;
		} }
		//C
		case 'C':
		case 'c': 
		{if(direction ==1)
		{SET_BIT(GPIO_PORTC_DIR_R, pin_num);
		 break;
		}
		else
			{CLR_BIT(GPIO_PORTC_DIR_R, pin_num);
		 break;
		} }	
		//D
		case 'D':
		case 'd': 
		{if(direction ==1)
		{SET_BIT(GPIO_PORTD_DIR_R, pin_num);
		 break;
		}
		else
			{CLR_BIT(GPIO_PORTD_DIR_R, pin_num);
		 break;
		} }	
			//E
		case 'E':
		case 'e': 
		{if(direction ==1)
		{SET_BIT(GPIO_PORTE_DIR_R, pin_num);
		 break;
		}
		else
			{CLR_BIT(GPIO_PORTE_DIR_R, pin_num);
		 break;
		} }	
		//F
		case 'F':
		case 'f': 
		{if(direction ==1)
		{SET_BIT(GPIO_PORTF_DIR_R, pin_num);
		 break;
		}
		else
			{CLR_BIT(GPIO_PORTF_DIR_R, pin_num);
		 break;
		} 
		}	

	} 
  }



// write functions 
void write_port(unsigned char port_name,unsigned char data){
  
	switch(port_name){
		case'A':
		case'a':
		{	GPIO_PORTA_DATA_R  =data ;	
		}
	case'B':
		case'b':
		{	GPIO_PORTB_DATA_R  =data ;	
		}break;
		case'C':
		case'c':
		{	GPIO_PORTC_DATA_R  =data ;	
		}break;
		case'D':
		case'd':
		{	GPIO_PORTD_DATA_R  =data ;	
		}break;
		case'E':
		case'e':
		{	GPIO_PORTE_DATA_R  =data ;	
		}break;
		case'F':
		case'f':
		{	GPIO_PORTF_DATA_R  =data ;	
		}break;
	}
}



void write_highnibble(unsigned char port_name,unsigned char data){
  data= data<<4;
	switch(port_name){
		case'A':
		case'a':
		{ GPIO_PORTA_DATA_R  &=0x0F;
			GPIO_PORTA_DATA_R  |=data ;	
		}break;
	  case'B':
		case'b':
		{	GPIO_PORTB_DATA_R  &=0x0F;
			GPIO_PORTB_DATA_R  |=data ;	
		}break;
		case'C':
		case'c':
		{	GPIO_PORTC_DATA_R  &=0x0F;
			GPIO_PORTC_DATA_R  |=data ;	
		}break;
		case'D':
		case'd':
		{	GPIO_PORTD_DATA_R  &=0x0F;
			GPIO_PORTD_DATA_R  |=data ;	
		}break;
		case'E':
		case'e':
		{	GPIO_PORTE_DATA_R  &=0x0F;
			GPIO_PORTE_DATA_R  |=data ;	
		}break;
		case'F':
		case'f':
		{	GPIO_PORTF_DATA_R  &=0x0F;
			GPIO_PORTF_DATA_R  |=data ;	
		}break;
	}
}
	


void write_lownibble(unsigned char port_name,unsigned char data){
  
	switch(port_name){
		case'A':
		case'a':
		{ GPIO_PORTA_DATA_R  &=0xF0;
			GPIO_PORTA_DATA_R  |=data ;	
		}break;
	        case'B':
		case'b':
		{	GPIO_PORTB_DATA_R  &=0xF0;
			GPIO_PORTB_DATA_R  |=data ;	
		}break;
		case'C':
		case'c':
		{	GPIO_PORTC_DATA_R  &=0xF0;
			GPIO_PORTC_DATA_R  |=data ;	
		}break;
		case'D':
		case'd':
		{	GPIO_PORTD_DATA_R  &=0xF0;
			GPIO_PORTD_DATA_R  |=data ;	
		}break;
		case'E':
		case'e':
		{	GPIO_PORTE_DATA_R  &=0xF0;
			GPIO_PORTE_DATA_R  |=data ;	
		}break;
		case'F':
		case'f':
		{	GPIO_PORTF_DATA_R  &=0xF0;
			GPIO_PORTF_DATA_R  |=data ;	
		}break;
	}
}
void Set_portDir(unsigned char port_name,unsigned char direction)
{
	switch(port_name){
		case'A':
		case'a':
		{
			GPIO_PORTA_DIR_R=direction;
		}
		break;
   	case'B':
		case'b':
		{
			GPIO_PORTA_DIR_R=direction;
		}
		break;
		case'C':
		case'c':
		{
			GPIO_PORTA_DIR_R=direction;
		}
		break;
		case'D':
		case'd':
		{
			GPIO_PORTA_DIR_R=direction;
		}
		break;
		case'E':
		case'e':
		{
			GPIO_PORTA_DIR_R=direction;
		}
		break;
		case'F':
		case'f':
		{
			GPIO_PORTA_DIR_R=direction;
		}
		break;
	}

}


// toggel the bin direction 
void TOG_BinData (unsigned char port_name, unsigned char bin_num)
{
	switch(port_name){
		case'A':
		case'a':
		{
			TOG_BIT(GPIO_PORTA_DATA_R , bin_num);
		}
		break;
   	case'B':
		case'b':
		{
			void TOG_BinData (unsigned char port_name, unsigned char bin_num);
		}
		break;
		case'C':
		case'c':
		{
			void TOG_BinData (unsigned char port_name, unsigned char bin_num);
		}
		break;
		case'D':
		case'd':
		{
			void TOG_BinData (unsigned char port_name, unsigned char bin_num);
		}
		break;
		case'E':
		case'e':
		{
			void TOG_BinData (unsigned char port_name, unsigned char bin_num);
		}
		break;
		case'F':
		case'f':
		{
			void TOG_BinData (unsigned char port_name, unsigned char bin_num);
		}
		break;
	}
}
//########################################################KEYPAD FUNCTIONS#################################################################################

//keypad initilization in port C and E
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

//Keypad  general scan 
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



//Keypad digit scan
int KeypadConversionDigit()
{ int a;
	unsigned char x = KeypadScan(); 
 if ((x!= 'A' )& (x!= 'B') &( KeypadScan()!= 'C') & (x!= 'D') & (x!= '#' )& (x!= '*' ) ){	//input '0'is will be handled
   a = (int) x-'0'; //********************************************
	return a ;}
else {
LCD_WriteStr("Err"); //
genericDelay(2000);//delay 2 sec
LCD_cmd(CLR_display );
 KeypadConversionDigit();
}
return 0;
}


//the function will take inputs for D in keypad, ddetermine minutes and seconds then display the countdown
void cookingtime_D(){ 
	 unsigned char noPressed =0xFF;
   int arr[4] = {0,0,0,0};
	int number=0x00; //the 16 bit digit
	int i=0;
	int j;
 	int min;
	int sec;
	int s1;
	int s2;
	int m1;
	int m2;
	LCD_cmd(CLR_display);
	LCD_cmd(Curs_1stRow);
	LCD_cmd(CursOff_DisON);
	for(j = 3 ; j>=0; j--)
	//sw1 not pressed
	{
		while(KeypadScan()==noPressed) genericDelay(5000); 
		while(KeypadScan()!='*')
		{	
			while(KeypadScan()==noPressed) genericDelay(5000);
			arr[j] = KeypadConversionDigit();	//take the input every 
			if(KeypadScan()=='#') continue;
			
			LCD_write(arr[j]+'0');
			LCD_cmd(RShiftCurs);
			genericDelay(2000);
			//number = (number<<4) | i; 
			//arr[i] = KeypadConversionDigit();	//we don't know if they(function and for loop) are in sync	
		}
	}
/*	s1=number&~0xFFF0;
	s2=number&~0xFF0F;
	m1=number&~0xF0FF;
	m2=number&~0x0FFF;
	//sec = number | 0xF + (number | 0xF0)*10; 
	sec = s1+ s2*10; 
	min = m1+ m2*10;
	
	//int min = arr[1] + arr[0] * 10; //get minutes from the array
	//int sec = arr[3] + arr[2] * 10; //get seconds from the array
	statesDelay(D_delay (sec, min)); //get the delay for custom and display the countdown */
}


void keypad_store4character(){
	int g;
	unsigned char  count_array1[4]={0,0,0,0};
	unsigned char  count_array[4];
	int array_int[4];
	    
    	
	 for(g=0;g<4;g++)
		{ while(KeypadScan()==0xff);
			count_array1[0]=KeypadScan();
			count_array1[0]=count_array1[1];
			count_array1[1]=count_array1[2];
		  count_array1[2]=count_array1[3];			
			LCD_write(count_array[g]);
			genericDelay(500);
		  count_array[g]=count_array1[g];
		} 
		//conver char to int
	  array_int[0]=count_array1[0]-'0';
		array_int[1]=count_array1[0]-'0';
		array_int[2]=count_array1[0]-'0';
		array_int[3]=count_array1[3]-'0';
		int sec=(array_int[3]+array_int[2]*10);
		int min =(array_int[3]+array_int[2]*10);
		statesDelay(D_delay (sec,min));
		
   } 