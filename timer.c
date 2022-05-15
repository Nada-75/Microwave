//*/files included
#include "stdio.h"
#include "IO.h"
#include "lcd.h"

//initialize the Systic timer 
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
 for(i=0;i<time ;i++) //time here in milli seconds 
 SysTick_wait(16000); //one millisecond delay 	
}

//function to make a delay AND update the LCD 
void statesDelay(unsigned long time){ //the function takes time in seconds
	//used variables
	int i;
	int seconds;
	int minutes;
	char s1,s2;  //char s1 and s2 which will have the displayed seconds
	char m1,m2;	 //char m1 and m2 which will have the displayed minutes
	//LCD_Init(); //IF NOT IN MAIN
	
	//Equations
	minutes = time/60; //get the minutes by dividing the whole seconds /60
	seconds = time%60; //get the remaining seconds by taking the reminder of the previous operation
	
	//getting the four horsmen to be displayed

	//preparing to display 
	LCD4bits_Cmd(lcd_clear); //clear the lcd
	LCD4bits_Cmd(0x80); //get the cmd at position 0
	
	// for each seond do that
	for(i=0; i<time;i++){ 
		 genericDelay(1000); //1 sec delay
		
		//Update lcd goes here to be updated each sec with the new seconds and minutes
		
		//update components of seconds after updating seconds and same for minutes
		s2 = seconds/10; 
		s1 = seconds%10;
		m2 =minutes/10;
		m1=minutes%10;
		
		// we want the format to be m2 m1 : s2 s1
		LCD4bits_Data(s2+'0'); //display the  second bit of minutes  
		LCD4bits_Cmd(RShiftCurs);
		LCD4bits_Data(s2+'0'); //display the first bit of minutes 
		LCD4bits_Cmd(RShiftCurs);
		LCD4bits_Data(':'); // display : 
		LCD4bits_Cmd(RShiftCurs);
		LCD4bits_Data(s1+'0'); //display the second bit of seconds
		LCD4bits_Cmd(RShiftCurs);
		LCD4bits_Data(s1+'0'); //display the first bit of seconds
		
		
		//Here goes the code of changing minutes and seconds every second.
		
		if(seconds>0 && minutes>=0) {seconds--;} //decrease seconds each one second

		if(seconds ==0 && minutes>0) { //If seconds reached zero, decrease the minutes 
			// After 1:00 comes 0:59888888888//*****
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
		
		case 'B': return time =30* weight;       //in case of beef, delay = weight* 0.5 min
		case 'C' : return time =12*weight;       //in case of corn, delay= weight * 0.2 min 
	}
	 return 0; } //if we entered other inputs that B or C
	 
//A function to determine popcorn delay (just for further abstraction)	
unsigned long A_delay()
	{unsigned long time;
return time=60;	//60 sec delay
} 

//A function to determine D(custom) delay 
unsigned long D_delay ( int seconds, int minutes){ 
	unsigned long time = 60*minutes + seconds; //times in seconds
	return time; //as function takes seconds
}
