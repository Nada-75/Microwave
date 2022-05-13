#include "tm4c123gh6pm.h"
#include "timer.h"
#include "IO.h"

void LED_INIT(unsigned char port_name ,unsigned char pin_number){
	Set_pinDirection(port_name ,pin_number,1);
 }


void ArrayLED_ON(){
	GPIO_PORTF_DATA_R |= 0x0E;
	}
	
void ArrayLED_OFF(){
	GPIO_PORTF_DATA_R &= ~0x0E;
	
		//void LED_TOG(unsigned char port_name ,unsigned char pin_number){
        TOG_BinData(port_name,bin_num); //Error here 
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
	