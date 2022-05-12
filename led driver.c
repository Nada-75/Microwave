#include "tm4c123gh6pm.h"
#include "timer.h"
#include "IO.h"
void LED_INIT(unsigned char port_name ,unsigned char pin_number){
	set_pinDirection (unsigned char port_name ,unsigned char pin_number,1);
 }


void LED_ON(unsigned char port_name ,unsigned char pin_number){
	writepin(unsigned char port_name ,unsigned char pin_number,1);
	}
	
void LED_OFF(unsigned char port_name ,unsigned char pin_number){
	writepin(unsigned char port_name ,unsigned char pin_number,0);
	}
	
void LED_TOG(unsigned char port_name ,unsigned char pin_number){
        TOG_pinData (unsigned char port_name ,unsigned char pin_number);
	}

// Blink Leds 
void LED_TOG(unsigned char port_name ,unsigned char pin_number){
        TOG_pinData (unsigned char port_name ,unsigned char pin_number);
	      genericDelay(1000); //delay for 1 sec
	      
	}