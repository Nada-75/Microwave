#include "tm4c123gh6pm.h"
#include "timer.h"
#include "led driver.h"

//initialization for the leds
void RGBLEDS_Init(void)
{
  SYSCTL_RCGCGPIO_R |= 0x20; 						//1) Activate Clock for Port F
  while ((SYSCTL_PRGPIO_R & 0x20) == 0); // Delay to Allow Time for Clock to Start
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   		//2) Unlock GPIO Port F
  GPIO_PORTF_CR_R |= 0x0E;          		//Allow Changes to PF3-1
  GPIO_PORTF_AMSEL_R |= ~0x0E; 					//3)Disable Analog on Port F
  GPIO_PORTF_PCTL_R &= ~0x0000FFF0; 		//4)Clear Bits of PCTL GPIO on PF123
  GPIO_PORTF_AFSEL_R &= ~0x0E; 					//5)Disable Alternate Function on PF123
  GPIO_PORTF_DIR_R |= 0x0E; 						//6)Set PF1 , PF2 and PF3 as Outputs
  GPIO_PORTF_DEN_R |= 0x0E; 						//7)Enable Digital I/O on PF1 , PF2 and PF3
  GPIO_PORTF_DATA_R &= ~0x0E;     			//Initialize LEDs to be OFF
}

//on led
void ArrayLED_ON(){
	GPIO_PORTF_DATA_R |= 0x0E;
	}
//off led	
void ArrayLED_OFF(){
	GPIO_PORTF_DATA_R &= ~0x0E;
	
	}
// this function makes the array of leds blink
void blink(){
			GPIO_PORTF_DATA_R = 0x0E;   //Turn on  LEDS
			genericDelay(200);					//Delay 0.5sec
			GPIO_PORTF_DATA_R = 0x00;		//Turn oFF LEDS
			genericDelay(200);					//Delay 0.5sec
}

//this function makes the array of leds blinks for 3 times
void ArrayLED_Flash(){
   int i;
   for(i=0;i<6;i++)
		{
        GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R ^0x0E;
				genericDelay(500); //0.5sec  	
		} 
}
	  /*

//General port initialization function
void Port_Init(unsigned char portname){
	switch(portname)
	{
		
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
		
	}
}
//general pin direction function
void Set_pinDirection (unsigned char port_name, unsigned char pin_num, unsigned char direction){ //set the bin in the wanted port to 1 or 0
	switch (port_name){
		
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
	} 
  }
//function to enable the pull up for pin
void enable_PullUP (unsigned char port_name, unsigned char pin_num){ //set the  pullup pin in the wanted port to 1 
	switch (port_name){
		
	  //C
		case 'C':
		case 'c': 
		{SET_BIT(GPIO_PORTC_PUR_R, pin_num);
		 break;
		}
	} }



//function to write the pin in any port
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
*/    
