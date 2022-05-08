#include "C:\Keil\Labware\inc\tm4c123gh6pm.h"
#include "stdint.h"
unsigned int Keypad_col_1= 0x10;
unsigned int Keypad_row_1 =0x01;
unsigned char array[4][4]={{'1', '2', '3', 'A'},{'4', '5', '6', 'B'},{'7', '8', '9', 'c'},{'*', '0','#', 'D'}}; 

unsigned char Keypad_scan()
	
{while(1)
	{
		for(short i=0;i<4;i++) // scan columns
				{ GPIO_PORTE_DATA_R =  Keypad_row_1 << i;
						for(short j=0;j<4;j++) //scan rows
								{ if ((GPIO_PORTC_DATA_R & 0xF0)== Keypad_col_1<<j)
										return array[i][j];
									return 0;
								}
				}
	}
}
