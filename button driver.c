#include "IO.h" 

//initialization 
void Button_init(unsigned char port_name, unsigned char pin_num){
	//initialize the port 
	 Port_Init(port_name);
	
	//set the direction pin register 
   Set_pinDirection (port_name, pin_num, 0);	
}

//read 
unsigned char Button_read(unsigned char port_name, unsigned char pin_num){
	//read pin
	return ReadPin(port_name, pin_num);
     
}

//pullup the Button
void Button_pullup(unsigned char port_name, unsigned char pin_num){
	// enable_PullUP 
	enable_PullUP(port_name, pin_num);
	
}

