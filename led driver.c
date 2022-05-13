#include "tm4c123gh6pm.h"
#include "timer.h"
#include "IO.h"

void LED_INIT(){
	GPIO_PORTF_Dir_R |= 0x0E;
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
   for(int i=0;i<6;i++)
		{
        GPIO_PORTF_DATA_R=GPIO_PORTF_DATA_R ^0x0E;
    	genericDelay(1000); //1sec  
		
		} }
// leds blink
void ArrayLED_Blink(){
 GPIO_PORTF_DATA_R=GPIO_PORTF_DATA_R ^0x0E;
    	genericDelay(1000); //1sec 
}	      
	