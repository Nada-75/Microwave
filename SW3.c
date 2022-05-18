//files included
#include "IO.h" 
#include "button driver.h"
#include "tm4c123gh6pm.h"
#define GPIO_PORTF_CLK_EN  0x20    //clock enable of PORTF
#define GPIO_PORTF_PIN0_EN 0x01    //Enable SW2
#define GPIO_PORTF_PIN1_EN 0x02    //Enable RED LED
#define GPIO_PORTF_PIN2_EN 0x04    //Enable BLUE LED
#define GPIO_PORTF_PIN3_EN 0x08    //Enable GREEN LED
#define GPIO_PORTF_PIN4_EN 0x10    //Enable SW1

//initialization 
void SW1_2_Init(void){
	SYSCTL_RCGCGPIO_R |= GPIO_PORTF_CLK_EN;   //enable clock of PORTF
	GPIO_PORTF_LOCK_R = 0x4C4F434B;           //unlock GPIO of PORTF
	GPIO_PORTF_CR_R = 0x01;                   //Enable GPIOPUR register enable to commit
	GPIO_PORTF_PUR_R |=  0x11;   //Enable Pull Up SW1,SW2
	GPIO_PORTF_DIR_R |= 0x11;
	GPIO_PORTF_DEN_R |=  0x11;
}
/*SYSCTL_RCGCGPIO_R|=0x20; //INTIALIZE THE CLOCK OF PORTF
while((SYSCTL_PRGPIO_R & 0x20)==0); //delay
GPIO_PORTF_LOCK_R = 0x4C4F434B; //Constant value
GPIO_PORTF_AMSEL_R &=~0x10; //disable analog function
GPIO_PORTF_CR_R |= 0x10; //setting pin p4 to change
GPIO_PORTF_PCTL_R &=~0x000F0000; //enable digital function
GPIO_PORTF_AFSEL_R &=~0x10; //disable alterante function
GPIO_PORTF_DIR_R &=~0x10; //DIR--> 0->input & 1->output
GPIO_PORTF_PUR_R |=0x10; //active LOW
GPIO_PORTF_DEN_R |= 0x10; //Enable digital for sw1

}
void sw2_Init(void){
	
	SYSCTL_RCGCGPIO_R|=0x10; //INTIALIZE THE CLOCK OF PORTE
	while((SYSCTL_PRGPIO_R & 0x10)==0); //delay 
	GPIO_PORTE_LOCK_R = 0x4C4F434B;	//Constant value
	GPIO_PORTE_AMSEL_R &=~0x20;	//disable analog function
	GPIO_PORTE_CR_R |= 0x20; //setting pin p4 to change
	GPIO_PORTE_PCTL_R &=~0x00F00000; //enable digital function
	GPIO_PORTE_AFSEL_R &=~0x20; //disable alterante function
	GPIO_PORTE_DIR_R &=~0x20; 	//DIR--> 0->input & 1->output
	GPIO_PORTE_PUR_R &=~0x20;	//active low
	GPIO_PORTE_DEN_R |= 0x20;	//Enable digital for sw2 	
}	*/

void sw3_Init(void){//E4
	
	SYSCTL_RCGCGPIO_R|=0x10; //INTIALIZE THE CLOCK OF PORTE
	while((SYSCTL_PRGPIO_R & 0x10)==0); //delay 
	GPIO_PORTE_LOCK_R = 0x4C4F434B;	//Constant value
	GPIO_PORTE_AMSEL_R &=~0x10;	//disable analog function
	GPIO_PORTE_CR_R |= 0x10; //setting pin p4 to change
	GPIO_PORTE_PCTL_R &=~0x000F0000; //enable digital function
	GPIO_PORTE_AFSEL_R &=~0x10; //disable alterante function
	GPIO_PORTE_DIR_R &=~0x10; 	//DIR--> 0->input & 1->output
	GPIO_PORTE_PUR_R &=~0x10;	//active low
	GPIO_PORTE_DEN_R |= 0x10;	//Enable digital for sw1 	
	
	
}


unsigned char sw1_input(void){
return GPIO_PORTF_DATA_R&0x10; //0001 0000
}
unsigned char sw2_input(void){
return GPIO_PORTF_DATA_R&0x01; //0010 0001
	}
unsigned char sw3_input(void){
return GPIO_PORTE_DATA_R&0x10; //0001 0000
	}
	
	
	
	