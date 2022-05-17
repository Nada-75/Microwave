#include "tm4c123gh6pm.h"

//Functions Prototype
void Keypad_init();
unsigned char KeypadScan();

void cookingtime_D(); //the function will take inputs for D, ddetermine minutes and seconds then display the countdown
unsigned int KeypadConversionDigit(); //This function get the numeric input from keypad and return its integer value
