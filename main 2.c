#include "IO.h"
enum state{Idle, cooking, beefWeight, chickenWeight, cookingTime, pause, end};
int main(void){
	int state = Idle;
	while(1){
		switch(state){
			Idle:
			if ( Button_read( E,  0)=!0)//SW3 IS UP (CONNECTED on port E ,PIN0 )
			{
   			if(KeypadScan()=='A')
		    { lcd_send_string( "popcorn");
				  genericDelay( 2000);
					//DELY FOR 1 MIN
				  if ( Button_read( F,  0)==0)//sw2 pressed
				    {state = cooking;
				    }		
		    }
			if(KeypadScan()=='B')
			{state = beefWeight;
			}
			if(KeypadScan()=='C')
			{state = chickenWeight;
			}
			if(KeypadScan()=='D')
			{stata=cookingTime;
			}
		}
			break;
			cooking:
			 ArrayLED_ON(); //LEDS ON
   	   if(Button_read( E,  0)=0)//door open
			 {state = pause;
			 }
			 if(Button_read( F,  4)=0)//sw1 pressed
			 {state = pause;
			 }
			 if(NVIC_ST_CTRL_R&0x00010000//time out)
			 {state = end;
			 }
			break;
			beefWeight:
		  lcd_send_string( "Beef weight?");
//	
			 
			 
			 if ( Button_read( F,  0)==0)//sw2 pressed
				    {state = cooking;
				    }	
			 //hint ,If an illegal number is entered,lcd_send_string( "Err"),stata=beefweight
			break;
			chickenWeight:
			lcd_send_string( "Chicken weight?");
//	
						
			 
			if ( Button_read( F,  0)==0)//sw2 pressed
				    {state = cooking;
				    }				
			break;
			cookingTime:
			lcd_send_string( "Cooking Time?");
//			
				
						
			if ( Button_read( F,  0)==0)//sw2 pressed
				    {state = cooking;
				    }				
			break;
						
			pause:
			 ArrayLED_Blink();//led blink
			if(Button_read(unsigned char F, unsigned char 4)=0)//sw1 pressed 2'nd time
			  {state = end;
			  }
			if(Button_read(unsigned char F, unsigned char 0)=0)//sw2 pressed
			 {state = cooking;
			 }
			break;
			end:
	    ArrayLED_Flash();
			 //BUZZER ON
			 state = Idle;

			break;
		}
	}
}