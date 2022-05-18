#include "tm4c123gh6pm.h"
#include "stdint.h"
#define SET_BIT(REG,BIT) REG|=1<<BIT
#define CLR_BIT(REG, BIT) REG&=(~(1<<BIT))
#define READ_BIT(REG,BIT) (REG&(1<<BIT))>>BIT
#define noPressed 0xFF
#define DataPins 'B'
#define CTRLPins 'A'
//macros of CTRLPins
#define E  2
#define RS 3
#define RW 4
//Macros of commands
#define CLR_display   0x01
#define RShiftCurs    0x06
#define Turn_On       0x0F
#define Curs_1stRow   0x80
#define Curs_2ndRow   0xc0
#define Set_4bit      0x28
#define Set_8bit      0x38
#define CursOff_DisON 0x0c
#define Return_Home   0x02


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
	}

}
unsigned char ReadPin (unsigned char portName,unsigned pinNum)
{ while(1){

		switch(portName)
			
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
void Keypad_init(void)
{ 
	Port_Init('D');
	Port_Init('E');
	Set_pinDirection('D',0,0);		//D0-D3 input  (Col)
	Set_pinDirection('D',1,0);
	Set_pinDirection('D',2,0);
	Set_pinDirection('D',3,0);
	Set_pinDirection('E',0,1);		//E0-E3 output  (rows)
	Set_pinDirection('E',1,1);
	Set_pinDirection('E',2,1);
	Set_pinDirection('E',3,1);
	enable_PullUP ('D', 0);		
	enable_PullUP ('D', 1);
	enable_PullUP ('D', 2);
	enable_PullUP ('D', 3);
	
}
unsigned char KeypadScan(void)
{
	unsigned char  array [4][4]={{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}};
	
  unsigned char x,y,i;
	unsigned char returnvalue = noPressed;

	for (x=0; x<4; x++)
		{ 
		     	writePin('E',0, 1);
			    writePin('E',1, 1);
			    writePin('E',2, 1);
					writePin('E',3, 1);
					writePin('E',x, 0);
		
			for (y=0; y<4; y++)
		{
					i = ReadPin('D', y);
					if(i==0)
					{						
						returnvalue = array[x][y];
						return returnvalue;
					}
		}
	}
	return returnvalue;					 
}


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
void SysTick_wait(unsigned long delay){ 
	NVIC_ST_CTRL_R = 0x00;  
	NVIC_ST_RELOAD_R = delay-1;  //Reload delay
	NVIC_ST_CURRENT_R =0; 
	NVIC_ST_CTRL_R = 0x05; 
 while((NVIC_ST_CTRL_R&0x00010000)==0){} 
 } 
void genericDelay(unsigned long time){ 
	int i;
 for(i=0;i<time ;i++) 
 SysTick_wait(16000); //one millisecond delay 	
}

void LCD_cmd(unsigned char cmd){
	GPIO_PORTB_DATA_R=cmd;
	writePin('A',RS,0);
	writePin('A',RW,0);
	writePin('A',E,1);
	genericDelay(2);
	writePin('A',E,0);
}
void init_LCD(void){
	SYSCTL_RCGCGPIO_R|=0x03;
	while(!(SYSCTL_PRGPIO_R&0x03));
	GPIO_PORTA_LOCK_R=0X4C4F434B;
	GPIO_PORTA_CR_R=0xFF;
	GPIO_PORTA_DEN_R=0xFF;
	GPIO_PORTA_AMSEL_R&=~0xFF;
	GPIO_PORTA_AFSEL_R&=~0xFF;
	GPIO_PORTA_PCTL_R&=~0xFFFFFF00;
	
	GPIO_PORTB_LOCK_R=0X4C4F434B;
	GPIO_PORTB_CR_R=0xFF;
	GPIO_PORTB_DEN_R|=0xFF;
	GPIO_PORTB_AMSEL_R&=~0xFF;
	GPIO_PORTB_AFSEL_R&=~0xFF;
	GPIO_PORTB_PCTL_R&=~0xFFFF; 
	
	GPIO_PORTB_DIR_R=0xFF;
	GPIO_PORTA_DIR_R=0xFF;
	
	LCD_cmd(Set_8bit); //8-bit mode
	genericDelay(1);
	LCD_cmd(CLR_display); //Clear LCD display screen
	genericDelay(1);
	LCD_cmd(Return_Home); //Return home
	genericDelay(1);
	LCD_cmd(RShiftCurs); //increment cursor
	genericDelay(1);
	LCD_cmd(Curs_1stRow); //go to zero position
	genericDelay(1);
}
void LCD_write(unsigned char data){
	GPIO_PORTB_DATA_R=data; //send data to portB
	writePin('A',RS,1);
	writePin('A',RW,0);
	writePin('A',E,1);
	genericDelay(2);
	writePin('A',E,0);
}
void LCD_WriteStr(char * str)
{  
	volatile int i = 0;          	//i must be pulled from memory 
	while(*(str+i) != '\0')       	//Continue until you find the Null-Terminating Character.
	{
		LCD_write(*(str+i)); //Print each character of the string on the LCD
		i++;                        
	}
}

void SystemInit(void){}

int main(void)
{
  unsigned char PressedKey;

  RGBLEDS_Init();
	Keypad_init();		//use your keypad initialization function
  init_LCD();
  while(1)
	{

		PressedKey = KeypadScan(); 	//use your keypad read function

		if (PressedKey == 'A')		//Turn Red LED On
			{
				SET_BIT(GPIO_PORTF_DATA_R, 1);
							 //genericDelay(100);
		LCD_cmd(Curs_1stRow);
	//genericDelay(100);
	LCD_WriteStr("popcorn");
	//genericDelay(100);

			}
		if (PressedKey == 'B')			//Turn Blue LED On
			{
				SET_BIT(GPIO_PORTF_DATA_R, 2);
			}

		if (PressedKey == 'C')		//Turn Green LED On
			{
				SET_BIT(GPIO_PORTF_DATA_R, 3);
			}

		if (PressedKey == 'D')		//Turn All LEDs On
			{
				GPIO_PORTF_DATA_R |= 0x0E;
			}

		if (PressedKey == '0')			//Turn All LEDs Off
			{
				GPIO_PORTF_DATA_R &= ~0x0E;
			}
	}
}