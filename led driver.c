#include "tm4c123gh6pm.h"
#include "timer.h"
#include "led driver.h"

//initialization for the leds
void RGBLEDS_Init(void)
{
  SYSCTL_RCGCGPIO_R |= 0x20; 		 //1) Activate Clock for Port F
  while ((SYSCTL_PRGPIO_R & 0x20) == 0); // Delay to Allow Time for Clock to Start
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   	 //2) Unlock GPIO Port F
  GPIO_PORTF_CR_R |= 0x0E;          	 //Allow Changes to PF3-1
  GPIO_PORTF_AMSEL_R |= ~0x0E; 		 //3)Disable Analog on Port F
  GPIO_PORTF_PCTL_R &= ~0x0000FFF0; 	 //4)Clear Bits of PCTL GPIO on PF123
  GPIO_PORTF_AFSEL_R &= ~0x0E; 		 //5)Disable Alternate Function on PF123
  GPIO_PORTF_DIR_R |= 0x0E; 		 //6)Set PF1 , PF2 and PF3 as Outputs
  GPIO_PORTF_DEN_R |= 0x0E; 		 //7)Enable Digital I/O on PF1 , PF2 and PF3
  GPIO_PORTF_DATA_R &= ~0x0E;     	 //Initialize LEDs to be OFF
}

//on led
void ArrayLED_ON()
{
  GPIO_PORTF_DATA_R |= 0x0E;	
}
//off led	
void ArrayLED_OFF()
{
  GPIO_PORTF_DATA_R &= ~0x0E;	
}
// this function makes the array of leds blink
void blink()
{
  GPIO_PORTF_DATA_R = 0x0E;             //Turn on  LEDS
  genericDelay(200);		        //Delay 0.5sec
  GPIO_PORTF_DATA_R = 0x00;		//Turn oFF LEDS
  genericDelay(200);		        //Delay 0.5sec
}

//this function makes the array of leds blinks for 3 times
void ArrayLED_Flash()
{
  int i;
  for(i=0;i<6;i++)
   {
    GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R ^0x0E;
    genericDelay(500); //0.5sec  	
   } 
}