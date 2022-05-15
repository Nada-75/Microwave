#include "IO.h"
#include "button driver.h"
#include "lcd.h"
#include "timer.h"
#include "tm4c123gh6pm.h"
#include "stdint.h"
#include "Keypad driver.h"
#include "led driver.h"


// define the port name and the pin number where the sw3 will connect
#define sw3PortName E
#define sw3PinNUM 0

// define the states we will use in the switch conductions
enum state{Idle, cooking, beefWeight, chickenWeight, cookingTime, pause, end};

void BuzzerConfig() // connect buzzer to A6
{ 
	 Set_pinDirection('A',6,1); //output
	writePin( 'A',6,1);//active high
  
}

int main(void){
	
Port_Init('A'); //for buzzer
     Button_init(F,0);//sw2
     Button_init(F,4);//sw1
     Button_init( sw3PortName, sw3PinNUM);//sw3
     LED_INIT()
  Keypad_init();//keypad         
   int state = Idle;
	while(1){
		switch(state){
			Idle:
			//your code goes here
			if ( Button_read( sw3PortName, sw3PinNUM)!=0)//SW3 IS UP (CONNECTED on port E ,PIN0 )
			{
				if(KeypadScan()=='A')
				{
					lcd_send_string( "popcorn");
					genericDelay( 2000);
					//DELY FOR 1 MIN
					statesDelay(A_delay()); //get the delay for A and display the count down on the LCD
					
					if ( Button_read( F,  0)==0)//sw2 pressed
					{
						state = cooking;
					}
				}
				if(KeypadScan()=='B')
				{
					state = beefWeight;
				}
				if(KeypadScan()=='C')
				{
					state = chickenWeight;
				}
				if(KeypadScan()=='D')
				{
					state = cookingTime;
				}
			}
			break;
			cooking:
			//your code goes here
			ArrayLED_ON(); //LEDS ON
if((Button_read( sw3PortName,  sw3PinNUM)==0)|(Button_read( F,  4)==0))//door open or sw1 pressed
			{
				state = pause;
			}
			//if(Button_read( F,  4)==0)//sw1 pressed
			//{
			//	state = pause;
			//}
			/*if((NVIC_ST_CTRL_R&0x00010000)==0)//wait
			//{
			//	state = cooking;
	   	}*/
			
			if(NVIC_ST_CTRL_R&0x00010000//time out)
			{
				state = end;
			}
			break;
			
			beefWeight:
			//your code goes here
			lcd_send_string( "Beef weight?");
			//
			
			
			if ( Button_read( F,  0)==0)//sw2 pressed
			{
			if ((KeypadScan()!= 'A' )& (KeypadScan()!= 'B') &( KeypadScan()!= 'C') & (KeypadScan()!= 'D') & (KeypadScan()!= '#' )& (KeypadScan()!= '*' ) & (KeypadScan()!= '0')) // enter a number from 1-9
				// lcd show the entered number for 2 seconds
							//lcd showing remaing time
	state = cooking;
			}
			//hint ,If an illegal number is entered,lcd_send_string( "Err"),state = beef weight
if ((KeypadScan()== 'A' )| (KeypadScan()== 'B') |( KeypadScan()== 'C') | (KeypadScan()== 'D') | (KeypadScan()== '#' )| (KeypadScan()== '*' ) | (KeypadScan()== '0')) // invalid number
			 { //LCD error for 2 sec
			 state = beefweight;
			 }
			break;
			 
			chickenWeight:
			//your code goes here
			lcd_send_string( "Chicken weight?");
			//
			
			
			if ( Button_read( F,  0)==0)//sw2 pressed
			{
if ((KeypadScan()!= 'A' )& (KeypadScan()!= 'B') &( KeypadScan()!= 'C') & (KeypadScan()!= 'D') & (KeypadScan()!= '#' )& (KeypadScan()!= '*' ) & (KeypadScan()!= '0')) // enter a number from 1-9
				// lcd show the entered number for 2 seconds
							//lcd showing remaing time			
	state = cooking;
			}
	if((KeypadScan()== 'A' )| (KeypadScan()== 'B') |( KeypadScan()== 'C') | (KeypadScan()== 'D') | (KeypadScan()== '#' )| (KeypadScan()== '*' ) | (KeypadScan()== '0')) // invalid number
				{
					//LCD error for 2 sec
			  state = beefweight;
				}		
break;
			cookingTime:
			//your code goes here
			lcd_send_string( "Cooking Time?");
			//
			
			
			if ( Button_read( F,  0)==0)//sw2 pressed
			{
				state = cooking;
			}
			break;
			pause:
			//your code goes here
			ArrayLED_Blink();//led blink
			if(Button_read(F, 4)==0)//sw1 pressed 2nd time
			{
				state = end;
			}
			else if(Button_read(F, 0)==0)//sw2 pressed
			{
				state = cooking;
			}
			break;
			end:
			//your code goes here
			ArrayLED_Flash();
			//BUZZER ON
		BuzzerConfig() ;
			state = Idle;
			
			break;
		}
	}
}