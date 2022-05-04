#include "C:\Keil\Labware\inc\tm4c123gh6pm.h"
#include "stdint.h"

void Keypad_initial()
{
	SYSCTL_RCGCGPIO_R|=0x14; // activate clock for ports C & E
	while ((SYSCTL_PRGPIO_R & 0x14)==0); // wait for stabilization
	//GPIO_PORTF_LOCK_R=0x4C4F434B;
	GPIO_PORTC_CR_R|=0xF0; //allow changes to PC7-4
	GPIO_PORTE_CR_R|=0x0F; //allow changes to PE3-0
	GPIO_PORTC_AMSEL_R&=~0xF0; // disable analog function
	GPIO_PORTE_AMSEL_R&=~0x0F; // disable analog function
	GPIO_PORTC_PCTL_R&=~0xF0; // GPIO clear bit PCTL
	GPIO_PORTE_PCTL_R&=~0x0F;// GPIO clear bit PCTL
  GPIO_PORTC_AFSEL_R&=~0xF0; // no alternate function
	GPIO_PORTE_AFSEL_R&=~0x0F; //no alternate function
	GPIO_PORTC_DIR_R&=~0xF0; //PC7-4 input
	GPIO_PORTE_DIR_R|=0x0F; // PE3-0 output
	GPIO_PORTC_DEN_R|=0xF0; // enable digital pins PC7-4
	GPIO_PORTE_DEN_R|=0x0F; // enable digital pins PE3-0
	GPIO_PORTC_PDR_R|=0xF0; // keypad active high
	//GPIO_PORTC_DATA_R&=~0xF0; initialize 
	//GPIO_PORTE_DATA_R&=~0x0F;
	
}