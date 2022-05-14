//files included
#include "stdio.h"
#include "IO.h"
#include "keypad driver.h"
#include "lcd.h"

//initialize the sys tic timer 
void SysTick_wait(unsigned long delay){ 
	NVIC_ST_CTRL_R = 0x00;  
	NVIC_ST_RELOAD_R = delay-1;  //Reload delay
	NVIC_ST_CURRENT_R =0; 
	NVIC_ST_CTRL_R = 0x05; 
 while((NVIC_ST_CTRL_R&0x00010000)==0){} 
 } 

//A function to make a generic delay in seconds
 void genericDelay(unsigned long time){ 
	int i;
 for(i=0;i<time ;i++) 
 SysTick_wait(16000); //one millisecond delay 	
}

//function to make a delay AND update the LCD 
void statesDelay(unsigned long time){ //the function takes time in milliseconds
	//used variables
	int i;
	int seconds;
	int minutes;
	//Equations
	seconds	= time/1000 ; //get the time in seconds 
	minutes = seconds/60; //get the minutes by dividing the whole seconds /60
	seconds =seconds%60; //get the remaining seconds by taking the reminder of the previous operation ###
	char *s;  //char s which will have the displayed value
	
	// now we have seconds and minutes in their variables
	for(i=0; i<time;i++){
		genericDelay(1000); //1 sec delay
		//Update lcd goes here to be updated each sec with the new seconds and minutes
		
		sprintf(s,"%u : %u",minutes,seconds);//put s in the format of min:sec in order to be printed ###
		lcd_send_string(s); //display the string 
		if(seconds>0 && minutes>=0) {seconds--;} //decrease seconds each one second
		if(seconds ==0 && minutes>0) { //If seconds reached zero, decrease the minutes 
			// After 1:00 comes 0:59
			minutes --;
			seconds =59;
		}
		if(seconds==0 && minutes==0){//we finished counting down 
			//what to do when we finish goes here ###
			break; //get out  from the for loop			
			}
		
		
	}
}

//A function to determine the delay for chicken and beef
//this function will be called inside the genericDelay function to determine the time in seconds.
unsigned long BC_delay(unsigned char state, int weight){
	unsigned long time;
	switch(state) {
		
		case 'B': return time =30* weight*1000;       //in case of beef, delay = weight* 0.5 min
		case 'C' : return time =12*weight*1000;       //in case of corn, delay= weight * 0.2 min 
	}
	 return 0; } //if we entered other inputs that B or C
	 
//A function to determine popcorn delay (just for further abstraction)	
unsigned long A_delay(){unsigned long time;
return time=60*1000;	//60 sec delay
} 

//A function to determine D(custom) delay 
unsigned long D_delay ( int seconds, int minutes){ 
	unsigned long time = 60*minutes + seconds; //times in seconds
	return time *1000; //as function takes milliseconds
}
	