//include tm4c123gh6pm.h file
#include "tm4c123gh6pm.h"
#include "led driver.h"
#include "Buzzer.h"
#include "timer.h"
#include "button driver.h"
#include "lcd.h"

//define states
#define Idle 0
#define cooking 1
#define beefWeight 2
#define chickenWeight 3
#define cookingTime 4
#define pause 5
#define end 6



// define port f pins
#define GPIO_PORTF_CLK_EN  0x20    //clock enable of PORTF
#define GPIO_PORTF_PIN0_EN 0x01    //Enable SW2
#define GPIO_PORTF_PIN1_EN 0x02    //Enable RED LED
#define GPIO_PORTF_PIN2_EN 0x04    //Enable BLUE LED
#define GPIO_PORTF_PIN3_EN 0x08    //Enable GREEN LED
#define GPIO_PORTF_PIN4_EN 0x10    //Enable SW1

//initialize port f
void PORTF_Init(void)
{
	SYSCTL_RCGCGPIO_R |= GPIO_PORTF_CLK_EN;   //enable clock of PORTF
	GPIO_PORTF_LOCK_R = 0x4C4F434B;           //unlock GPIO of PORTF
	GPIO_PORTF_CR_R = 0x01;                   //Enable GPIOPUR register enable to commit
	GPIO_PORTF_PUR_R |= GPIO_PORTF_PIN0_EN + GPIO_PORTF_PIN4_EN;   //Enable Pull Up SW1,SW2
	GPIO_PORTF_DIR_R |= GPIO_PORTF_PIN1_EN + GPIO_PORTF_PIN2_EN + GPIO_PORTF_PIN3_EN;   //Make PF1,PF2,PF3 as output and PF4 as input by default
	GPIO_PORTF_DEN_R |= GPIO_PORTF_PIN0_EN + GPIO_PORTF_PIN1_EN + GPIO_PORTF_PIN2_EN+ GPIO_PORTF_PIN3_EN + GPIO_PORTF_PIN4_EN; //enable PF1,PF2,PF3,PF4 pins as digital GPIO 
}

//Macros and prototypes for keypad
#define SET_BIT(REG,BIT) REG|=1<<BIT
#define CLR_BIT(REG, BIT) REG&=~(1<<BIT)
#define READ_BIT(REG,BIT) (REG&(1<<BIT))>>BIT
void RGBLEDS_Init(void);
void Keypad_init();
unsigned char KeypadScan();
unsigned char noPressed=0xFF;
unsigned char  array [4][4]={{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}};


//General port initialization function
void Port_Init(unsigned char portname){
	switch(portname)
	{
		case 'A':
		case 'a':
		{
			SET_BIT(SYSCTL_RCGCGPIO_R,0);
			while(!(READ_BIT(SYSCTL_RCGCGPIO_R,0)));
			GPIO_PORTA_LOCK_R=0X4C4F434B;
			GPIO_PORTA_CR_R=0xFF;
			GPIO_PORTA_DEN_R=0xFF;
			break;
		}
		case 'B':
		case 'b':
		{
			SET_BIT(SYSCTL_RCGCGPIO_R,1);
			while(!(READ_BIT(SYSCTL_RCGCGPIO_R,1)));
			GPIO_PORTB_LOCK_R=0X4C4F434B;
			GPIO_PORTB_CR_R=0xFF;
			GPIO_PORTB_DEN_R=0xFF;
			break;
		}
		case 'C':
		case 'c':
		{
			SET_BIT(SYSCTL_RCGCGPIO_R,2);
			while(!(READ_BIT(SYSCTL_RCGCGPIO_R,2)));
			GPIO_PORTC_LOCK_R=0X4C4F434B;
			GPIO_PORTC_CR_R=0xFF;
			GPIO_PORTC_DEN_R=0xFF;
			break;
		}
		case 'D':
		case 'd':
		{
			SET_BIT(SYSCTL_RCGCGPIO_R,3);
			while(!(READ_BIT(SYSCTL_RCGCGPIO_R,3)));
			GPIO_PORTD_LOCK_R=0X4C4F434B;
			GPIO_PORTD_CR_R=0xFF;
			GPIO_PORTD_DEN_R=0xFF;
			break;
		}
		case 'E':
		case 'e':
		{
			SET_BIT(SYSCTL_RCGCGPIO_R,4);
			while(!(READ_BIT(SYSCTL_RCGCGPIO_R,4)));
			GPIO_PORTE_LOCK_R=0X4C4F434B;
			GPIO_PORTE_CR_R=0xFF;
			GPIO_PORTE_DEN_R=0xFF;
			break;
		}
		case 'F':
		case 'f':
		{
			SET_BIT(SYSCTL_RCGCGPIO_R,5);
			while(!(READ_BIT(SYSCTL_RCGCGPIO_R,5)));
			GPIO_PORTF_LOCK_R=0X4C4F434B;
			GPIO_PORTF_CR_R=0xFF;
			GPIO_PORTF_DEN_R=0xFF;
			break;
		}
	}
}
//general pin direction function
void Set_pinDirection (unsigned char port_name, unsigned char pin_num, unsigned char direction){ //set the bin in the wanted port to 1 or 0
	switch (port_name){
		//A
		case 'A':
		case 'a': 
		{if(direction ==1)
		{SET_BIT(GPIO_PORTA_DIR_R, pin_num);
		 break;
		}
		else
			{CLR_BIT(GPIO_PORTA_DIR_R, pin_num);
		 break;
		} }
		//B
		case 'B':
		case 'b': 
		{if(direction ==1)
		{SET_BIT(GPIO_PORTB_DIR_R, pin_num);
		 break;
		}
		else
			{CLR_BIT(GPIO_PORTB_DIR_R, pin_num);
		 break;
		} }
		//C
		case 'C':
		case 'c': 
		{if(direction ==1)
		{SET_BIT(GPIO_PORTC_DIR_R, pin_num);
		 break;
		}
		else
			{CLR_BIT(GPIO_PORTC_DIR_R, pin_num);
		 break;
		} }	
		//D
		case 'D':
		case 'd': 
		{if(direction ==1)
		{SET_BIT(GPIO_PORTD_DIR_R, pin_num);
		 break;
		}
		else
			{CLR_BIT(GPIO_PORTD_DIR_R, pin_num);
		 break;
		} }	
			//E
		case 'E':
		case 'e': 
		{if(direction ==1)
		{SET_BIT(GPIO_PORTE_DIR_R, pin_num);
		 break;
		}
		else
			{CLR_BIT(GPIO_PORTE_DIR_R, pin_num);
		 break;
		} }	
		//F
		case 'F':
		case 'f': 
		{if(direction ==1)
		{SET_BIT(GPIO_PORTF_DIR_R, pin_num);
		 break;
		}
		else
			{CLR_BIT(GPIO_PORTF_DIR_R, pin_num);
		 break;
		} 
		}	
	} 
  }
//function to enable the pull up for pin
void enable_PullUP (unsigned char port_name, unsigned char pin_num){ //set the  pullup pin in the wanted port to 1 
	switch (port_name){
		//A
		case 'A':
		case 'a': 
		{SET_BIT(GPIO_PORTA_PUR_R, pin_num);
		 break;
		}
	  //B
		case 'B':
		case 'b': 
		{SET_BIT(GPIO_PORTB_PUR_R, pin_num);
		 break;
		}
	  //C
		case 'C':
		case 'c': 
		{SET_BIT(GPIO_PORTC_PUR_R, pin_num);
		 break;
		}
	 //D
		case 'D':
		case 'd': 
		{SET_BIT(GPIO_PORTD_PUR_R, pin_num);
		 break;
		}
	//E
		case 'E':
		case 'e': 
		{SET_BIT(GPIO_PORTE_PUR_R, pin_num);
		 break;
		}
   //F
		case 'F':
		case 'f': 
		{SET_BIT(GPIO_PORTF_PUR_R, pin_num);
		 break;
		}
	} }

// this function makes buzzer on
/*void ONbuzzer(void){
	//buzzer is at pin A7
	SYSCTL_RCGCGPIO_R|=0x01; //INTIALIZE THE CLOCK OF PORTF
	while((SYSCTL_PRGPIO_R & 0x01)==0); //delay
	GPIO_PORTA_LOCK_R = 0x4C4F434B; //unlocking the ports have the same value
	GPIO_PORTA_CR_R |= 0x80;	//Allow changing 
	GPIO_PORTA_AMSEL_R &=~0x80; //disable the analog function
	GPIO_PORTA_PCTL_R &=~0xF0000000;
	GPIO_PORTA_AFSEL_R &=~0x80;	  //disable the alternative    function

	GPIO_PORTA_DIR_R |= 0x80;	
	GPIO_PORTA_DEN_R |=0x80;  //Enable digital for pin A7
	GPIO_PORTA_DATA_R |=0x80;//ON
} */

//Function to read the pin in any port
unsigned char ReadPin (unsigned char portName,unsigned pinNum)
{ while(1){

		switch (portName)
			
{   case 'A' :
	 return READ_BIT(GPIO_PORTA_DATA_R,pinNum);
    case 'B' :
	  return READ_BIT(GPIO_PORTB_DATA_R,pinNum);
		case 'C' :
	  return READ_BIT(GPIO_PORTC_DATA_R,pinNum);
		case 'D' :
	 return READ_BIT(GPIO_PORTD_DATA_R,pinNum);
		case 'E' :
	  return READ_BIT(GPIO_PORTE_DATA_R,pinNum);
		case 'F' :
	  return READ_BIT(GPIO_PORTF_DATA_R,pinNum);
}
}}

//function to write the pin in any port
void writePin(unsigned char portName,unsigned char pinNumber,unsigned char data)
{
	switch (portName)
			
{   case 'A' :
		{if(data ==1)
		{SET_BIT(GPIO_PORTA_DATA_R,pinNumber);
		 break;
		}
		else
			{CLR_BIT(GPIO_PORTA_DATA_R,pinNumber);
		 break;
		} 
		}
		case 'B' :
	  {if(data ==1)
		{SET_BIT(GPIO_PORTB_DATA_R,pinNumber);
		 break;
		}
		else
			{CLR_BIT(GPIO_PORTB_DATA_R,pinNumber);
		 break;
		} 
		}
		case 'C' :
	 {if(data ==1)
		{SET_BIT(GPIO_PORTC_DATA_R,pinNumber);
		 break;
		}
		else
			{CLR_BIT(GPIO_PORTC_DATA_R,pinNumber);
		 break;
		} 
		}
		case 'D' :
	 {if(data ==1)
		{SET_BIT(GPIO_PORTD_DATA_R,pinNumber);
		 break;
		}
		else
			{CLR_BIT(GPIO_PORTD_DATA_R,pinNumber);
		 break;
		} 
		}
		case 'E' :
	  {if(data ==1)
		{SET_BIT(GPIO_PORTE_DATA_R,pinNumber);
		 break;
		}
		else
			{CLR_BIT(GPIO_PORTE_DATA_R,pinNumber);
		 break;
		}  
		}
		case 'F':
{if(data ==1)
		{SET_BIT(GPIO_PORTA_DATA_R,pinNumber);
		 break;
		}
		else
			{CLR_BIT(GPIO_PORTA_DATA_R,pinNumber);
		 break;
		} 
		}
}
}
//initialization for the leds
void RGBLEDS_Init(void)
{
  SYSCTL_RCGCGPIO_R |= 0x20; 						//1) Activate Clock for Port F
  while ((SYSCTL_PRGPIO_R & 0x20) == 0); // Delay to Allow Time for Clock to Start
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   		//2) Unlock GPIO Port F
  GPIO_PORTF_CR_R |= 0x0E;          		//Allow Changes to PF3-1
  GPIO_PORTF_AMSEL_R |= ~0x0E; 					//3)Disable Analog on Port F
  GPIO_PORTF_PCTL_R &= ~0x0000FFF0; 		//4)Clear Bits of PCTL GPIO on PF123
  GPIO_PORTF_AFSEL_R &= ~0x0E; 					//5)Disable Alternate Function on PF123
  GPIO_PORTF_DIR_R |= 0x0E; 						//6)Set PF1 , PF2 and PF3 as Outputs
  GPIO_PORTF_DEN_R |= 0x0E; 						//7)Enable Digital I/O on PF1 , PF2 and PF3
  GPIO_PORTF_DATA_R &= ~0x0E;     			//Initialize LEDs to be OFF
}
//################################################STATESDELAY FUNCTION FROM TIMER####################################################################
//function to make a delay AND update the LCD 
/* int statesDelay(int time){ //the function takes time in milliseconds
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
		 while(!SW1 && SW3){ //when the switch1 or 3 is pressed go to pause
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
		
	} state = pause;
  		 //end while
	 } //end for
return remainTime;	 
} //end function */
//########################################################KEYPAD FUNCTIONS#################################################################################

//keypad initilization in port C and E
void Keypad_init()
{ Port_Init('C');
	Port_Init('E');
	Set_pinDirection('C',4,0); //C4-C7 input
	Set_pinDirection('C',5,0);
	Set_pinDirection('C',6,0);
	Set_pinDirection('C',7,0);
	
	Set_pinDirection('E',0,1); //E0-E3 output
	Set_pinDirection('E',1,1);
	Set_pinDirection('E',2,1);
	Set_pinDirection('E',3,1); 
	
	enable_PullUP ('C', 4);   
	enable_PullUP ('C', 5);
	enable_PullUP ('C', 6);
	enable_PullUP ('C', 7);
	
}

//Keypad  general scan 
unsigned char KeypadScan()
{	unsigned char returnvalue = noPressed;
	unsigned char  array [4][4]={{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}};
	unsigned char x,y,i;

	for (x=0;x<4;x++)
		{ 
		     	writePin( 'E',0, 1);
			    writePin( 'E',1, 1);
			     writePin( 'E',2, 1);
			   writePin( 'E',3, 1);
					writePin('E',x,0);
		
			for (y=0;y<4;y++)
		{
				i=ReadPin ('C',y+4);
					if(i==0) {
					returnvalue = array[x][y];
					return returnvalue; }
		}
	}				return returnvalue;
						 
}



//Keypad digit scan
int KeypadConversionDigit()
{ int a;
	unsigned char x = KeypadScan(); 
 if ((x!= 'A' )& (x!= 'B') &( KeypadScan()!= 'C') & (x!= 'D') & (x!= '#' )& (x!= '*' ) ){	//input '0'is will be handled
   a = (int) x-'0'; //********************************************
	return a ;}
else {
LCD_WriteStr("Err"); //
genericDelay(2000);//delay 2 sec
LCD_cmd(CLR_display );
 KeypadConversionDigit();
}
return 0;
}


//the function will take inputs for D in keypad, ddetermine minutes and seconds then display the countdown
void cookingtime_D(){ 
   int arr[4] = {0,0,0,0};
	int number=0x00; //the 16 bit digit
	int i=0;
	int j;
 	int min;
	int sec;
	int s1;
	int s2;
	int m1;
	int m2;
	LCD_cmd(CLR_display);
	LCD_cmd(Curs_1stRow);
	LCD_cmd(CursOff_DisON);
	for(j = 3 ; j>=0; j--)
	//sw1 not pressed
	{
		while(KeypadScan()==noPressed) genericDelay(5000); 
		while(KeypadScan()!='*')
		{	
			while(KeypadScan()==noPressed) genericDelay(5000);
			arr[j] = KeypadConversionDigit();	//take the input every 
			if(KeypadScan()=='#') continue;
			
			LCD_write(arr[j]+'0');
			LCD_cmd(RShiftCurs);
			genericDelay(2000);
			//number = (number<<4) | i; 
			//arr[i] = KeypadConversionDigit();	//we don't know if they(function and for loop) are in sync	
		}
	}
/*	s1=number&~0xFFF0;
	s2=number&~0xFF0F;
	m1=number&~0xF0FF;
	m2=number&~0x0FFF;
	//sec = number | 0xF + (number | 0xF0)*10; 
	sec = s1+ s2*10; 
	min = m1+ m2*10;
	
	//int min = arr[1] + arr[0] * 10; //get minutes from the array
	//int sec = arr[3] + arr[2] * 10; //get seconds from the array
	statesDelay(D_delay (sec, min)); //get the delay for custom and display the countdown */
}

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
				do{PressedKey = KeypadScan();} while (PressedKey == noPressed);
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
					while(KeypadScan()==noPressed) genericDelay(5000);
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
			case pause:
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
		} //end of case pause
			
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
