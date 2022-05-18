#include "C:\Users\dell\Downloads\tm4c123gh6pm.h"


void ONbuzzer(void){
	//buzzer is at pin A7
	SYSCTL_RCGCGPIO_R|=0x01; //INTIALIZE THE CLOCK OF PORTF
	while((SYSCTL_PRGPIO_R & 0x01)==0); //delay
	GPIO_PORTA_LOCK_R = 0x4C4F434B; //unlocking the ports have the same value
	GPIO_PORTA_CR_R |= 0x80;	//Allow changing 
	GPIO_PORTA_AMSEL_R &=~0x80; //disable the analog function
	GPIO_PORTA_PCTL_R &=~0xF0000000;
	GPIO_PORTA_AFSEL_R &=~0x80;	
	GPIO_PORTA_DIR_R |= 0x80;	
	GPIO_PORTA_DEN_R |=0x80;
	GPIO_PORTA_DATA_R |=0x80;//ON
}


void OFFbuzzer(void){
	//buzzer A4=10
	SYSCTL_RCGCGPIO_R|=0x01; //INTIALIZE THE CLOCK OF PORTF
	while((SYSCTL_PRGPIO_R & 0x01)==0); //delay
	GPIO_PORTA_LOCK_R = 0x4C4F434B; //unlocking the ports have the same value
	GPIO_PORTA_CR_R |= 0x80;	//Allow changing 
	GPIO_PORTA_AMSEL_R &=~0x80; //disable the analog function
	GPIO_PORTA_PCTL_R &=~0xF0000000;
	GPIO_PORTA_AFSEL_R &=~0x80;	
	GPIO_PORTA_DIR_R |= 0x80;	
	GPIO_PORTA_DEN_R |=0x80;
	GPIO_PORTA_DATA_R &=~0x80;//OFF
	
}
}