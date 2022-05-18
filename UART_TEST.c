#include "tm4c123gh6pm.h"
#include "stdint.h"
#include "string.h"
#include "IO.h"
#include "timer.h"
#include "lcd.h"
#include "UART.h"

#define bufferLen 5

int main(void){
	char command[bufferLen]={0};
	UART0Init();
	init_LCD();
	
	while(1){	
		LCD_cmd(CLR_display);
		UART_printStr("Enter Command:\n");
		getCommand(command,bufferLen);
		//only for testing
		if(strcmp(command,"A")==0)
		{
			LCD_WriteStr("Popcorn");
			genericDelay(500);
		}
		else if(strcmp(command, "B")==0){
      		LCD_WriteStr("Beef");
					genericDelay(500);
    	}
    	else if(strcmp(command, "C")==0){
      		LCD_WriteStr("Chicken");
					genericDelay(500);
    	}
    	else if(strcmp(command, "D")==0){
      		LCD_WriteStr("Cooking Time?");
					genericDelay(500);
    	}
		memset(command,0,bufferLen);
		UART0_WRITE('\n');
		genericDelay(500);
	}
}
