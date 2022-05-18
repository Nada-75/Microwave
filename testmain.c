//include tm4c123gh6pm.h file
#include "tm4c123gh6pm.h"

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


//initialize the systic timer 
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

// this function makes the array of leds blink
void blink(){
			GPIO_PORTF_DATA_R = 0x0E;   //Turn on  LEDS
			genericDelay(200);					//Delay 0.5sec
			GPIO_PORTF_DATA_R = 0x00;		//Turn oFF LEDS
			genericDelay(200);					//Delay 0.5sec
}

//this function makes the array of leds blinks for 3 times
void ArrayLED_Flash(){
   int i;
   for(i=0;i<6;i++)
		{
        GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R ^0x0E;
				genericDelay(500); //0.5sec  	
		} 
}

// this function makes buzzer on
void ONbuzzer(void){
	//buzzer is at pin A7
	SYSCTL_RCGCGPIO_R|=0x01; //INTIALIZE THE CLOCK OF PORTF
	while((SYSCTL_PRGPIO_R & 0x01)==0); //delay
	GPIO_PORTA_LOCK_R = 0x4C4F434B; //unlocking the ports have the same value
	GPIO_PORTA_CR_R |= 0x80;	//Allow changing 
	GPIO_PORTA_AMSEL_R &=~0x80; //disable the analog function
	GPIO_PORTA_PCTL_R &=~0xF0000000;
	GPIO_PORTA_AFSEL_R &=~0x80;	  //disable the alternative    function

	GPIO_PORTA_DIR_R |= 0x80;	
	GPIO_PORTA_DEN_R |=0x80;
	GPIO_PORTA_DATA_R |=0x80;//ON
}

void OFFbuzzer(void){
	//buzzer A4=10
	SYSCTL_RCGCGPIO_R|=0x01; //INTIALIZE THE CLOCK OF PORTF
	while((SYSCTL_PRGPIO_R & 0x01)==0); //delay
	GPIO_PORTA_LOCK_R = 0x4C4F434B; //unlocking the ports have the same value
	GPIO_PORTA_CR_R |= 0x80;	//Allow changing 
	GPIO_PORTA_AMSEL_R &=~0x80; //disable the analog function
	GPIO_PORTA_PCTL_R &=~0xF0000000;
	GPIO_PORTA_AFSEL_R &=~0x80;	
	GPIO_PORTA_DIR_R |= 0x80;	
	GPIO_PORTA_DEN_R |=0x80;
	GPIO_PORTA_DATA_R &=~0x80;//OFF
	
}
void sw3_Init(void){//E4
	
	SYSCTL_RCGCGPIO_R|=0x10; //INTIALIZE THE CLOCK OF PORTE
	while((SYSCTL_PRGPIO_R & 0x10)==0); //delay 
	GPIO_PORTE_LOCK_R = 0x4C4F434B;	//Constant value
	GPIO_PORTE_AMSEL_R &=~0x10;	//disable analog function
	GPIO_PORTE_CR_R |= 0x10; //setting pin p4 to change
	GPIO_PORTE_PCTL_R &=~0x000F0000; //enable digital function
	GPIO_PORTE_AFSEL_R &=~0x10; //disable alterante function
	GPIO_PORTE_DIR_R &=~0x10; 	//DIR--> 0->input & 1->output
	GPIO_PORTE_PUR_R &=~0x10;	//active low
	GPIO_PORTE_DEN_R |= 0x10;	//Enable digital for sw1 	
}

int main(void){
	int state = Idle;
	unsigned char flag=1 ;
	unsigned int SW1, SW2, SW3;
	PORTF_Init();
	sw3_Init();
	while(1){
		SW1 = GPIO_PORTF_DATA_R & 0x10;
		SW2 = GPIO_PORTF_DATA_R & 0x01;
		SW3 = GPIO_PORTE_DATA_R & 0x10;
		switch(state){
			case Idle:
			//your code goes here
			GPIO_PORTF_DATA_R &=~ 0x0E;   //Turn on  LEDS
			if(!SW2&&SW3){
			state = cooking;
			}
			break;
			case cooking:
			//your code goes here
			GPIO_PORTF_DATA_R = 0x0E;   //Turn on  LEDS
			if(!SW1){
				state = pause;
			}
			else if (!SW3){
				flag=0;
				state = pause;}
			break;
			case beefWeight:
			//your code goes here
			
			break;
			case chickenWeight:
			//your code goes here
			break;
			case cookingTime:
			//your code goes here
			break;
			case pause:
			//flag++;
			blink();
			//genericDelay(10000);
			if(!SW2){
			//flag--;
				state = cooking;		
			}
		  else if(!SW1){
        
			flag=flag+1;}
				if(flag%2){
			state = end;	
			}	
			 
			break;
			case end:
			ONbuzzer();
			ArrayLED_Flash();
			OFFbuzzer();
			state = Idle;
			//your code goes here
			break;
		}
	}
			
	
}
