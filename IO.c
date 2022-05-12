/* This is the driver for  our Input output usage
   It contains functions to help managing ports' inialization 
	 and deal with registers
*/
//Included files 
#include "tm4c123gh6pm.h"

//macros 
#define SET_BIT(REG,BIT) REG|=1<<BIT
#define CLR_BIT(REG, BIT) REG&=~(1<<BIT)
#define TOG_BIT(REG,BIT)  REG^= 1<<BIT
#define READ_BIT(REG,BIT) REG&(1<<BIT)>>BIT

//Functions
void Port_Init(unsigned char portname){
	switch(portname)
	{
		case 'A':
		case 'a':
		{
			SET_BIT(SYSCTL_RCGCGPIO_R,0);
			while(!(READ_BIT(SYSCTL_RCGCGPIO_R,0)));
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
{ while(1)
		switch (portName)
			
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
}
	
void writePin(unsigned char portName,unsigned char pinNumber,unsigned char data)
{
	switch (portName)
			
{   case 'A' :
	{ if (data ==1) SET_BIT(GPIO_PORTA_DIR_R,pinNumber) ;
	 else  CLR_BIT(GPIO_PORTA_DIR_R,pinNumber);
	}break; 
		case 'B' :
	  { if (data ==1) SET_BIT(GPIO_PORTB_DIR_R,pinNumber) ;
	 else  CLR_BIT(GPIO_PORTB_DIR_R,pinNumber);
		}break; 
		case 'C' :
	 { if (data ==1) SET_BIT(GPIO_PORTC_DIR_R,pinNumber) ;
	 else  CLR_BIT(GPIO_PORTC_DIR_R,pinNumber);
	 }break; 
		case 'D' :
	 { if (data ==1) SET_BIT(GPIO_PORTD_DIR_R,pinNumber) ;
	 else  CLR_BIT(GPIO_PORTD_DIR_R,pinNumber);
	 }break; 
		case 'E' :
	  { if (data ==1) SET_BIT(GPIO_PORTE_DIR_R,pinNumber) ;
	 else  CLR_BIT(GPIO_PORTE_DIR_R,pinNumber);
		}break; 
		case 'F':
{ if (data ==1) SET_BIT(GPIO_PORTF_DIR_R,pinNumber) ;
	 else  CLR_BIT(GPIO_PORTF_DIR_R,pinNumber);
}break; 
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

// Set port function

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
//bit macros
#define TOG_BIT(reg,bit)     reg ^= (1>>bit) //define the toggle function 

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
