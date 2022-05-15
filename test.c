# include "C:\Keil\Labware\inc\tm4c123gh6pm.h"
# include "stdint.h"
#define READ_BIT(REG,BIT) REG&(1<<BIT)>>BIT
#define SET_BIT(REG,BIT) REG|=1<<BIT
#define CLR_BIT(REG, BIT) REG&=~(1<<BIT)
#include "Keypad driver.c"
#include "button driver.h"
#include "IO.c"


int main()
{ while(1)
	{
	 Keypad_init();
	if ( KeypadScan() =='A')
		  writePin('F',1,1);
		if ( KeypadScan() =='B')
		  writePin('F',2,1);
	if ( KeypadScan() =='2')
		  writePin('F',3,1);		
					}
				}				