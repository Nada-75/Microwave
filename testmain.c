//include tm4c123gh6pm.h file
#include "tm4c123gh6pm.h"
#include "led driver.h"
#include "Buzzer.h"
#include "timer.h"
#include "button driver.h"
#include "lcd.h"
#include "IO.h"

//define states
#define Idle 0
#define cooking 1
#define beefWeight 2
#define chickenWeight 3
#define cookingTime 4
#define pause 5
#define end 6

//unsigned char noPressed =0xFF;


//################################################STATESDELAY FUNCTION FROM TIMER####################################################################
//function to make a delay AND update the LCD 
 int statesDelay(int time){ //the function takes time in milliseconds
	//used variables
	int i;
	int seconds;
	int minutes;
	int remainTime;
	unsigned int SW1;
	unsigned int SW2;
  unsigned int SW3; 
	
	 
	
	//Equations
	seconds	= time%60; //get the time in seconds 
	minutes = time/60; //get the minutes by dividing the whole seconds /60
	
	// now we have seconds and minutes in their variables
	 for(i=0; i<=time+1;i++){
		genericDelay(1000); //1 sec delay
	
	//Condition Checks	 
		 SW1 = GPIO_PORTF_DATA_R & 0x10;
		 SW3 = GPIO_PORTE_DATA_R & 0x10;
     if((SW1==0x00) || (SW3 == 0x00)) {
			 //pause here 
			 
			//flag++;
			blink();
			//genericDelay(10000);
			if(SW2==0x00)//SW2 is pressed after SW1{
			//flag--;
				continue;		

		  else if(SW1==0x00) //SW1 is pressed for second time
			   seconds=0;
			   minutes=0;
			   continue; 
			//state = end;	
			
		
			 
		 }
		 else{
		 
		if(seconds>0 && minutes>=0) 
     { 
			 displayTime(seconds,minutes); //Display the current time on LCD
			 seconds--;  //decrease seconds each one second
		 } 
		else if(seconds ==0 && minutes>0) { //If seconds reached zero, decrease the minutes 
			// After 1:00 comes 0:59888888888//*****
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
		
	} // state = pause;
  		 //end while
	 } //end for
return remainTime;	 
} //end function 

//###################################################################Main##############################################################################
int main(void){

   //initial state 
	unsigned char flag=1 ;
	 //Global variables
   int	state;
   unsigned int SW1;
	 unsigned int SW2;
   unsigned int SW3;
	unsigned int type=0;
	unsigned int weight = 0;
	
	unsigned char PressedKey ;
	state	= Idle;
	//initial LCD/RGB/Keypad/ needed ports and switches
	init_LCD();  
  RGBLEDS_Init();
	Keypad_init();		
	PORTF_Init();
	sw3_Init();
	  
	
	while(1){
		genericDelay(2000);
		//do{PressedKey = KeypadScan();} while (PressedKey == noPressed); //wait here till you take an input
		LCD_cmd(CLR_display);
    LCD_cmd(CursOff_DisON);
		LCD_cmd(Curs_1stRow);
		
		SW1 = GPIO_PORTF_DATA_R & 0x10;
		SW2 = GPIO_PORTF_DATA_R & 0x01;
		SW3 = GPIO_PORTE_DATA_R & 0x10;
		
			
		
		
		switch(state){
			case Idle: // ************************************************IDLE STATE**************************************************************
			{ type=0;
				do{PressedKey = KeypadScan();} while (PressedKey == 0xFF);
			//What to do in Idle state
      LCD_write(PressedKey);
		  genericDelay(2000);
			LCD_cmd(CLR_display);
      LCD_cmd(CursOff_DisON);
		  LCD_cmd(Curs_1stRow);
				 
		switch (PressedKey)
		{
			
			//POPCORN
			case 'A':			
			{		
				LCD_WriteStr("Popcorn");
				genericDelay(2000);
				
			  do{SW2 = GPIO_PORTF_DATA_R & 0x01;
				   SW3 = GPIO_PORTE_DATA_R & 0x10;}
        while((SW2 || (SW3 == 0x00)));
				
				type = 1;
        state = cooking;
				break;
			}
			
			//BEEF
			case 'B':			
			{
				LCD_WriteStr("Beef Weight?");
				genericDelay(2000);
				type = 2;
				
				state = beefWeight; //We go there to take the weight from the user
					
				break;
			}
			
      //CHICKEN
			case 'C':			
			{ 
			
				LCD_WriteStr("Chicken Weight?");
				genericDelay(2000);
				type = 3;
				state = chickenWeight; //We go there to take the weight from the user
				
				break;
			}
			//CUSTOM
			case 'D':			
			{
				LCD_WriteStr("Cooking time?");
				type = 4;
				
				state = cookingTime;
						
				break;
			}			
		}
	} //end of case idle
		
			
			//***************************************************BEEFWEIGHT STATE*********************************************************************
			case beefWeight:
			{//we will take the inpt weight from the user 
			genericDelay(500);	
			weight=0;
				
			do{weight = KeypadConversionDigit();
			   genericDelay(50);} while (weight == 0);
			//show the user the weight he enterd
			 LCD_cmd(CLR_display);
				LCD_cmd(Curs_1stRow);
        LCD_cmd(CursOff_DisON);
			  LCD_write(weight+'0');
			  genericDelay(2000);
			//when sw2 is pressed and we know the door is closed: start cooking
				do{SW2 = GPIO_PORTF_DATA_R & 0x01;
				   SW3 = GPIO_PORTE_DATA_R & 0x10;}
        while((SW2 || (SW3 == 0x00)));
					 
        state = cooking;
				break; } //end of case beefWeight
				//********************************************************CHICKENWEIGHT STATE**************************************************************
			case chickenWeight: 
			{
			//your code goes here
				genericDelay(500);
				weight=0;
		 do{weight=KeypadConversionDigit();} while (weight==0);	
			
			//show the user the wait he choose
			  LCD_cmd(CLR_display);
				LCD_cmd(Curs_1stRow);
        LCD_cmd(CursOff_DisON);
			  LCD_write(weight+'0');
			  genericDelay(2000);
		 
				do{SW2 = GPIO_PORTF_DATA_R & 0x01;
				   SW3 = GPIO_PORTE_DATA_R & 0x10;}
        while((SW2 || (SW3 == 0x00)));
					 
        state = cooking;
				break; } //end of case chickenweight
			
			//**************************************************COOKINGTIME STATE******************************************************************
			case cookingTime: 
			{
			//your code goes here
			break;
			} //end of class chickenweight
			
			case cooking: //*********************************************Cooking State***************************************************
			{ //your code goes here
			GPIO_PORTF_DATA_R = 0x0E;   //Turn on  LEDS
			switch(type){
				case 1: //POPCORN
					{
						genericDelay(1000);
						statesDelay(A_delay()); //Show the countdown for popcorn
						state = end;
						break; 
					}
				
				case 2: //BEEF
				{
					LCD_cmd(CLR_display); 
					LCD_cmd(Curs_1stRow);
					LCD_cmd(CursOff_DisON);
				
					statesDelay(BC_delay('B',weight)); //show the countdown for Beef
								state = end;
					break;
				}
				
				case 3: //CHICKEN
				{
					LCD_cmd(CLR_display);
					LCD_cmd(Curs_1stRow);
					LCD_cmd(CursOff_DisON);
					statesDelay(BC_delay('C',weight)); //show the countdown for chicken
								state = end;
					break;
				}
				case 4: //CUSTOM 
				{
					while(KeypadScan()==0xFF) genericDelay(5000);
					LCD_cmd(Curs_1stRow);
					LCD_cmd(CursOff_DisON);
					cookingtime_D(); //calculate the time and show it //still needing edit here.
								state = end;
					break;
				}
				case 0: {
					LCD_cmd(CLR_display);
					LCD_cmd(Curs_1stRow);
					LCD_cmd(CursOff_DisON);	
					LCD_WriteStr("type is wrong");
					genericDelay(1000);
          					
				}			
				
				} //end switch for type of cooking
			
       //Pause condition still needs edit 
					
		/*	if(!SW1)//SW1 is pressed for first time{
				state = pause;
			
			else if (!SW3){ //if door is opened{
				flag=0;
				state = pause;}
			break; */
			} //end of case cooking
			
			//*************************************************PAUSE STATE*******************************************************************
		/*	case pause:
			{
			//flag++;
			blink();
			//genericDelay(10000);
			if(!SW2)//SW2 is pressed after SW1{
			//flag--;
				state = cooking;		

		  else if(!SW1) //SW1 is pressed for second time
			flag=flag+1;
				if(flag%2){
			state = end;	
			}break;
		} //end of case pause */
			
			//******************************************************END STATE************************************************************
			case end:
			{
			ONbuzzer();  //turn the buzzer on 
			ArrayLED_Flash(); //flash the leds 
			OFFbuzzer(); //turn the buzzer off
			state = Idle; //start over
			break;
			} //end of case end;
		}
	}
			
	
}
