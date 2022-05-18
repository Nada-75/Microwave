#include "tm4c123gh6pm.h"
#include "timer.h"
#include "led driver.h"

void LED_INIT(void){
SYSCTL_RCGCGPIO_R|=0x20; //INTIALIZE THE CLOCK OF PORTF
while((SYSCTL_PRGPIO_R & 0x20)==0); //delay
GPIO_PORTF_LOCK_R = 0x4C4F434B; //unlocking the ports have the same value
GPIO_PORTF_CR_R |= 0x0E; //Allow changing pin 3,2,1 in portF
GPIO_PORTF_AMSEL_R &=~0x0E; //disable the analog function
GPIO_PORTF_PCTL_R &=~0x0000FFF0;
GPIO_PORTF_AFSEL_R &=~0x0E; //disable the alternate function
GPIO_PORTF_DIR_R |= 0x0E; //Pin1,2,3 is output
GPIO_PORTF_DEN_R |=0x0E;
GPIO_PORTF_DATA_R &=~0x0E; //intialize pins 1,2,3 to be off
}
//on led
void ArrayLED_ON(){
	GPIO_PORTF_DATA_R |= 0x0E;
	}
//off led	
void ArrayLED_OFF(){
	GPIO_PORTF_DATA_R &= ~0x0E;
	
	}

// flash leds for 3 times  
	void ArrayLED_Flash(){
   int i;
   for(i=0;i<7;i++)
		{
        GPIO_PORTF_DATA_R=GPIO_PORTF_DATA_R ^0x0E;
    	genericDelay(500); //0.5sec  
		
		} 
}
// leds blink
void ArrayLED_Blink(){
 
	GPIO_PORTF_DATA_R=GPIO_PORTF_DATA_R ^0x0E;
    	genericDelay(1000); //1sec 
}	      
