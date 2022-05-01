#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40025520))
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))
#define PF4                     (*((volatile unsigned long *)0x40025040))
#define PF3                     (*((volatile unsigned long *)0x40025020))
#define PF2                     (*((volatile unsigned long *)0x40025010))
#define PF1                     (*((volatile unsigned long *)0x40025008))
#define PF0                     (*((volatile unsigned long *)0x40025004))
#define GPIO_LOCK_KEY           0x4C4F434B  // Unlocks the GPIO_CR register
#define SYSCTL_RCGCGPIO_R       (*((volatile unsigned long *)0x400FE608))
#define SYSCTL_PRGPIO_R         (*((volatile unsigned long *)0x400FEA08))
#define NVIC_ST_CTRL_R         (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R       (*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R      (*((volatile unsigned long *)0xE000E018))
#define RED       0x02
#define BLUE      0x04
#define GREEN     0x08
#define PF123_mask              0x0E
#define PF04_mask               0x11
#define PF_mask      0x20
#define GPIO_PORTA_DATA_R       (*((volatile unsigned long *)0x400043FC))
#define GPIO_PORTA_DIR_R        (*((volatile unsigned long *)0x40004400))
#define GPIO_PORTA_AFSEL_R      (*((volatile unsigned long *)0x40004420))
#define GPIO_PORTA_PUR_R        (*((volatile unsigned long *)0x40004510))
#define GPIO_PORTA_DEN_R        (*((volatile unsigned long *)0x4000451C))
#define GPIO_PORTA_LOCK_R       (*((volatile unsigned long *)0x40004520))
#define GPIO_PORTA_CR_R         (*((volatile unsigned long *)0x40004524))
#define GPIO_PORTA_AMSEL_R      (*((volatile unsigned long *)0x40004528))
#define GPIO_PORTA_PCTL_R       (*((volatile unsigned long *)0x4000452C))


void SystemInit(){}
// a delay function for the leds blink
#define DELAY_VALUE        4000000   
void Delay(void)
{
	volatile unsigned long i;
	for(i=0;i<DELAY_VALUE;i++);
}


void sw3_Init(void){
	//SW3 IN PORT A0
SYSCTL_RCGCGPIO_R|=0x01; //INTIALIZE THE CLOCK OF PORTF
	while((SYSCTL_PRGPIO_R & 0x01)==0); //delay 
	GPIO_PORTA_LOCK_R = 0x4C4F434B;	//Constant value
	GPIO_PORTA_AMSEL_R &=~0x04;	//disable analog function
	GPIO_PORTA_CR_R |= 0x04; //setting pin p4 to change
	GPIO_PORTA_PCTL_R &=~0x0000000F; //enable digital function
	GPIO_PORTA_AFSEL_R &=~0x04; //disable alterante function
	GPIO_PORTA_DIR_R &=~0x04; 	//DIR--> 0->input & 1->output
	GPIO_PORTA_PUR_R =0x4;	//active LOW
	GPIO_PORTA_DEN_R |= 0x04;	//Enable digital for sw1
	
	
}
void SW1_2_Init(void){
	
	SYSCTL_RCGCGPIO_R|=0x20; //INTIALIZE THE CLOCK OF PORTF
	while((SYSCTL_PRGPIO_R & 0x20)==0); //delay 
	GPIO_PORTF_LOCK_R = 0x4C4F434B;	//Constant value
	GPIO_PORTF_AMSEL_R &=~0x11;	//disable analog function
	GPIO_PORTF_CR_R |= 0x11; //setting pin p4 to change
	GPIO_PORTF_PCTL_R &=~0x000F000F; //enable digital function
	GPIO_PORTF_AFSEL_R &=~0x11; //disable alterante function
	GPIO_PORTF_DIR_R &=~0x11; 	//DIR--> 0->input & 1->output
	GPIO_PORTF_PUR_R |=0x11;	//active low
	GPIO_PORTF_DEN_R |= 0x11;	//Enable digital for sw1 	
	
	
}
void RGB_Init(void){
	
	SYSCTL_RCGCGPIO_R|=0x20; //INTIALIZE THE CLOCK OF PORTF
	while((SYSCTL_PRGPIO_R & 0x20)==0); //delay
	GPIO_PORTF_LOCK_R = 0x4C4F434B; //unlocking the ports have the same value
	GPIO_PORTF_CR_R |= 0x0E;	//Allow changing pin 3,2,1 in portF
	GPIO_PORTF_AMSEL_R &=~0x0E; //disable the analog function
	GPIO_PORTF_PCTL_R &=~0x0000FFF0;
	GPIO_PORTF_AFSEL_R &=~0x0E;	//disable the alternate function
	GPIO_PORTF_DIR_R |= 0x0E;	//Pin1,2,3 is output
	GPIO_PORTF_DEN_R |=0x0E;
	GPIO_PORTF_DATA_R &=~0x0E; //intialize pins 1,2,3 to be off
	
}
unsigned char sw1_input(void){
	
	return GPIO_PORTF_DATA_R&0x10;	//0001 0000 
}
unsigned char sw2_input(void){
	
	return GPIO_PORTF_DATA_R&0x01;	//0000 0001	
}
unsigned char sw3_input(void){
	
	return GPIO_PORTA_DATA_R&0x04;	//0000 0100
}

void RGB_Output (unsigned char data){
	
	GPIO_PORTF_DATA_R &=~0x0E;	//Reseting the pf321
	GPIO_PORTF_DATA_R |= data;
}


/*int is_CLOSE(void)
{
	 if(GPIO_PORTA_DATA_R==!0X01 )//   SW3 IS PRESS (DOOR OPWN) =0X10
	return(0); //THE DOOR IS OPEN
	
 }*/

  unsigned char button1;
  unsigned char button2;
  unsigned char button3;
  unsigned char led_out =0X0E;//IED ON AS DEFULT


int main()
{	
  sw3_Init();
  SW1_2_Init();
	RGB_Init();
	
	while(1)
	{	
	  button1=sw1_input();
		button2=sw2_input();
		button3=sw3_input();
		
		if(button1!=0x10 &&button2!=01 &&button3!=0x4 ) //SW1 is pressed for second time
		{ 
			
		  	GPIO_PORTF_DATA_R = 0x02;    //Turn on RED LED 	 
					                  			
       	button1=0x10;
		  	button1=0x0;
			  if(button1!=0x10&&button2!=01 &&button3!=0x4)
				{
				GPIO_PORTF_DATA_R = 0x00;    //Turn  off LED
		    led_out = 0x00; //led off
				RGB_Output(led_out);
				}
			}
		if(button3!=0x4) //not pressed Case(2)
			{
					GPIO_PORTF_DATA_R = 0x00;
			}
    if((button3==0X4)&(button2==!0X01))
		{
			GPIO_PORTF_DATA_R = 0x02;			
			
		  if((button3==0X4)&(button2==!0X01)&(button1==0x10))
			{
				GPIO_PORTF_DATA_R = 0x02;
			}
			else if((button3==0X4)&(GPIO_PORTF_DATA_R = 0x02))
			{
				GPIO_PORTF_DATA_R = 0x02;    //Turn on RED LED 	 
				Delay();	                   //Delay almost
		}
					//LED off
			
				
			/*if(button1!=0x10 &&button2!=01 &&button3==01 ) //SW1 is pressed for second time
			{ 
		  	GPIO_PORTF_DATA_R = 0x02;    //Turn on RED LED 	 
				Delay();	                   //Delay almost 1 sec 1 sec
				GPIO_PORTF_DATA_R = 0x00;    //Turn  off LED
				Delay();                     //Delay almost 1 sec				
			}
				GPIO_PORTF_DATA_R = 0x00;    //Turn  off LED
				Delay();
				led_out = 0x00; //led off
				RGB_Output(led_out);
			}*/
		/*	if(button3) //not pressed Case(2)
			{
					led_out = 0x0;
					RGB_Output(led_out);
			}*/
	}
}
	}