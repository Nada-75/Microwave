#include "C:\Users\DELL 3550\Downloads\ENG.Rana\Second Year\Second Term\Embedded\Project\Io.h"
void SystemInit(){}
// a delay function for the leds blink
#define DELAY_VALUE        4000000   
void Delay(void)
{
	volatile unsigned long i;
	for(i=0;i<DELAY_VALUE;i++);
}


void sw3_Init(void){
	//SW3 IN PORT A0
SYSCTL_RCGCGPIO_R|=0x01; //INTIALIZE THE CLOCK OF PORTF
	while((SYSCTL_PRGPIO_R & 0x01)==0); //delay 
	GPIO_PORTA_LOCK_R = 0x4C4F434B;	//Constant value
	GPIO_PORTA_AMSEL_R &=~0x04;	//disable analog function
	GPIO_PORTA_CR_R |= 0x04; //setting pin p4 to change
	GPIO_PORTA_PCTL_R &=~0x0000000F; //enable digital function
	GPIO_PORTA_AFSEL_R &=~0x04; //disable alterante function
	GPIO_PORTA_DIR_R &=~0x04; 	//DIR--> 0->input & 1->output
	GPIO_PORTA_PUR_R &=~0x04;	//active LOW
	GPIO_PORTA_DEN_R |= 0x04;	//Enable digital for sw1
	
	
}
void SW1_2_Init(void){
	
	SYSCTL_RCGCGPIO_R|=0x20; //INTIALIZE THE CLOCK OF PORTF
	while((SYSCTL_PRGPIO_R & 0x20)==0); //delay 
	GPIO_PORTF_LOCK_R = 0x4C4F434B;	//Constant value
	GPIO_PORTF_AMSEL_R &=~0x11;	//disable analog function
	GPIO_PORTF_CR_R |= 0x11; //setting pin p4 to change
	GPIO_PORTF_PCTL_R &=~0x000F000F; //enable digital function
	GPIO_PORTF_AFSEL_R &=~0x11; //disable alterante function
	GPIO_PORTF_DIR_R &=~0x11; 	//DIR--> 0->input & 1->output
	GPIO_PORTF_PUR_R |=0x11;	//active low
	GPIO_PORTF_DEN_R |= 0x11;	//Enable digital for sw1 	
	
	
}
void RGB_Init(void){
	
	SYSCTL_RCGCGPIO_R|=0x20; //INTIALIZE THE CLOCK OF PORTF
	while((SYSCTL_PRGPIO_R & 0x20)==0); //delay
	GPIO_PORTF_LOCK_R = 0x4C4F434B; //unlocking the ports have the same value
	GPIO_PORTF_CR_R |= 0x0E;	//Allow changing pin 3,2,1 in portF
	GPIO_PORTF_AMSEL_R &=~0x0E; //disable the analog function
	GPIO_PORTF_PCTL_R &=~0x0000FFF0;
	GPIO_PORTF_AFSEL_R &=~0x0E;	//disable the alternate function
	GPIO_PORTF_DIR_R |= 0x0E;	//Pin1,2,3 is output
	GPIO_PORTF_DEN_R |=0x0E;
	GPIO_PORTF_DATA_R &=~0x0E; //intialize pins 1,2,3 to be off
	
}
unsigned char sw1_input(void){
	
	return GPIO_PORTF_DATA_R&0x10;	//0001 0000 
}
unsigned char sw2_input(void){
	
	return GPIO_PORTF_DATA_R&0x01;	//0000 0001	
}
unsigned char sw3_input(void){
	
	return GPIO_PORTA_DATA_R&0x10;	//0000 0001
}

void RGB_Output (unsigned char data){
	
	GPIO_PORTF_DATA_R &=~0x0E;	//Reseting the pf321
	GPIO_PORTF_DATA_R |= data;
}

// this fuction makes the red bilnks for almost 1 second
void ledBlink(void){
	GPIO_PORTF_DATA_R = 0x02;    //Turn on RED LED 
	Delay();	             //Delay almost 1 sec
	GPIO_PORTF_DATA_R = 0x00;    //Turn  off LED
	Delay();                     //Delay almost 1 sec
}
/*int is_CLOSE(void)
{
	 if(GPIO_PORTA_DATA_R==!0X01 )//   SW3 IS PRESS (DOOR OPWN) =0X10
	return(0); //THE DOOR IS OPEN
	
 }*/

  unsigned char button1;
  unsigned char button2;
  unsigned char button3;
  unsigned char led_out =0X0E;//IED ON AS DEFULT


int main()
{	
  sw3_Init();
  SW1_2_Init();
	RGB_Init();
	
	while(1)
	{	
	  button1=sw1_input();
		button2=sw2_input();
		button3=sw3_input();
    if((button3==!0X01)&(button2==!0X01))
		{
			GPIO_PORTF_DATA_R = 0x02;			
			if(button1==!0X01)//if SW1 is pressed or the door opened
			{
				ledBlink();
			}
			else if((button3==!0X01)&(button2==!0X01)&(button1==0X01))
			{
				GPIO_PORTF_DATA_R = 0x02;
			}
			else if((button3==0X01)&(GPIO_PORTF_DATA_R = 0x02))
			{
				ledBlink();				
			}
		}
		/*if()
       {//OFF
       }*/				 
	}
 }
