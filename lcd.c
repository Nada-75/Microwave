#include "tm4c123gh6pm.h"
#include "IO.h"
#include "lcd.h"

//these two functions for delay will be trasfered to another file
void SysTick_wait(unsigned long delay){
	NVIC_ST_CTRL_R =0x00;
	NVIC_ST_RELOAD_R= delay-1;
	NVIC_ST_CURRENT_R=0;
	NVIC_ST_CTRL_R =0x05;
	while((NVIC_ST_CTRL_R & 0x00010000)==0){//wait for count flag
	} 
}

void genericDelay(unsigned long time){
	int i;
	for(i=0; i<time ;i++){
		SysTick_wait(16000); //1msec
	}
}
//Pulse_send function is used to send characters and commands
static void Pulse_send(void){//this function is static as I will not use it outside this file
		writePin(CTRLPins,E,1);
	  genericDelay(2);		 
	  writePin(CTRLPins,E,0);	
} 
void lcd_send_cmd(unsigned char cmd){	
	 write_port(DataPins,cmd);
	 writePin(CTRLPins,RS,0);
	 Pulse_send();
	 genericDelay(1);
}
void lcd_Init(void){
		Port_Init(DataPins);
		Port_Init(CTRLPins);
		Set_portDirection(DataPins,0xFF);//set direction of pins as outputs
		Set_pinDirection(CTRLPins,E,1);//set enable to 1
	        Set_portDir(CTRLPins,RS,1);//set direction of RS as output
		Set_pinDirection(CTRLPins,RW,1);//set direction of RW as output
		writePin(CTRLPins,RW,0);//active low to write data
		lcd_send_cmd(Set_8bit); //using 8-bit mode
		genericDelay(1);//after each command, we should use a delay
		lcd_send_cmd(CursOff_DisON);//This command is used for display on and cursor off
		genericDelay(1);
		lcd_send_cmd(ClrDisplay);//To ensure that there is no data written
		genericDelay(10);
		lcd_send_cmd(RShift_curs);
	  genericDelay(1);		 
}
void lcd_send_char(unsigned char chr){
	 write_port(DataPins,chr);
	 writePin(CTRLPins,RS,1);
	 Pulse_send();
	 genericDelay(1);
}
void lcd_send_string(char *str){
	while((*str)!='\0'){
		lcd_send_char(*str);
		str++;
	}
}
void lcd_move_curs(unsigned char row,unsigned char col){
	char pos=0;
	if(row==1){
		pos=Curs_1stRow+col-1;
	}
	else if(row==2){
	  pos=Curs_2ndRow+col-1;
	}
	else //if we don't enter row 1 or 2 ,we will use first place
	{
		pos=0x80;
	}
	lcd_send_cmd(pos);
	genericDelay(1);
}


