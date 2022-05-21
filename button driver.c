
#include "button driver.h"
#include "tm4c123gh6pm.h"
//initialization 
// define port f pins
#define GPIO_PORTF_CLK_EN  0x20    //clock enable of PORTF
#define GPIO_PORTF_PIN0_EN 0x01    //Enable SW2
#define GPIO_PORTF_PIN4_EN 0x10    //Enable SW1

//initialize port f
void PORTF_Init(void)
{
  SYSCTL_RCGCGPIO_R |= GPIO_PORTF_CLK_EN;                       //enable clock of PORTF
  GPIO_PORTF_LOCK_R = 0x4C4F434B;                               //unlock GPIO of PORTF
  GPIO_PORTF_CR_R = 0x01;                                       //Enable GPIOPUR register enable to commit
  GPIO_PORTF_PUR_R |= GPIO_PORTF_PIN0_EN + GPIO_PORTF_PIN4_EN;  //Enable Pull Up SW1,SW2
  GPIO_PORTF_DIR_R |= 0x00;                                     //Make PF1,PF2,PF3 as output and PF4 as input by default
  GPIO_PORTF_DEN_R |= GPIO_PORTF_PIN0_EN + GPIO_PORTF_PIN4_EN;  //enable PF1,PF2,PF3,PF4 pins as digital GPIO 
}


void sw3_Init(void)//disable alterante function
{	
  SYSCTL_RCGCGPIO_R|=0x10;                                      //INTIALIZE THE CLOCK OF PORTF
  while((SYSCTL_PRGPIO_R & 0x10)==0);                           //delay 
  GPIO_PORTE_LOCK_R = 0x4C4F434B;	                        //Constant value
  GPIO_PORTE_AMSEL_R &=~0x10;	                                //disable analog function
  GPIO_PORTE_CR_R |= 0x10;                                      //setting pin p4 to change
  GPIO_PORTE_PCTL_R &=~0x000F0000;                              //enable digital function
  GPIO_PORTE_AFSEL_R &=~0x10;                                   //disable alterante function
  GPIO_PORTE_DIR_R &=~0x10; 	                                //DIR--> 0->input & 1->output
  GPIO_PORTE_PUR_R &=~0x10;	                                //active low
  GPIO_PORTE_DEN_R |= 0x10;	                                //Enable digital for sw1 			
}


