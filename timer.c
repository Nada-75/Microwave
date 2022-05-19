//*/files included
#include "tm4c123gh6pm.h"
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
//A function to display time 
void displayTime(int seconds, int minutes){
	//define first and second digit of seconds and minutes
	char s1,s2;  //char s which will have the displayed value
	char m1,m2;
	//get first and second digit of seconds and minutes
	 s2= seconds/10;
	 s1=seconds%10;
	 m2 = minutes/10;
	 m1 = minutes%10;
	//getting ready to display
		LCD_cmd(CLR_display); //clear the LCD
	  LCD_cmd(0x80);      //start from first pixel
	//Start displayting bit by bit
	  LCD_write(m2+'0');   //display the second digit of minutes 
		LCD_cmd(RShiftCurs);
		LCD_write(m1+'0');   //display the first digit of minutes
		LCD_cmd(RShiftCurs);
		LCD_write(':');
		LCD_cmd(RShiftCurs);
		LCD_write(s2+'0');
		LCD_cmd(RShiftCurs);
		LCD_write(s1+'0');
}
//function to make a delay AND update the LCD 
 /*int statesDelay(int time){ //the function takes time in milliseconds
	//used variables
	int i;
	int seconds;
	int minutes;
	int remainTime;
	
	//Equations
	seconds	= time%60; //get the time in seconds 
	minutes = time/60; //get the minutes by dividing the whole seconds /60
	
	// now we have seconds and minutes in their variables
	 for(i=0; i<=time+1;i++){
		genericDelay(1000); //1 sec delay
	
	//Condition Checks	 
		 //while(!SW1 && SW3){ //when the switch1 or 3 is pressed go to pause
		if(seconds>0 && minutes>=0) 
     { 
			 displayTime(seconds,minutes); //Display the current time on LCD
			 seconds--;  //decrease seconds each one second
		 } 
		else if(seconds ==0 && minutes>0) { //If seconds reached zero, decrease the minutes 
			// After 1:00 comes 0:59888888888
			displayTime(seconds,minutes); //Display the current time on LCD (Time here should be "minutes:00")
			minutes --;
			seconds =59;
		}
		else if(seconds==0 && minutes==0){//we finished counting down 
			displayTime(seconds,minutes); //Display the current time on LCD (Time here should be 00:00)
			//what to do when we finish goes here ###
			
		  return 0; //get out of while
			}
		remainTime = time-i;
		
	} //state = pause;
  		 //end while
	 //} //end for
return remainTime;	 
} //end function  */

//A function to determine the delay for chicken and beef
//this function will be called inside the genericDelay function to determine the time in seconds.
int BC_delay(unsigned char state, int weight){//UNSIGNED LONG
	int time=0;//UNSIGNED LONG
	switch(state) {
		
		case 'B': 
		{
			time =30* weight;
			return time;       //in case of beef, delay = weight* 0.5 min
		}
		case 'C' : 
		{
			time =12*weight;
			return time ;      //in case of corn, delay= weight * 0.2 min 
		}
	}
	 return 0; } //if we entered other inputs that B or C
	 
//A function to determine popcorn delay (just for further abstraction)	
int A_delay()//UNSIGNED LONG
	{int time;//UNSIGNED LONG
return time=60;	//60 sec delay
} 

//A function to determine D(custom) delay 
int D_delay ( int seconds, int minutes){ //UNSIGNED LONG
	int time = 60*minutes + seconds; //UNSIGNED LONG //times in seconds 
	return time; //as function takes milliseconds
}
