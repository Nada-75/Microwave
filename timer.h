void SysTick_wait(unsigned long delay); //initialize the systic timer
void genericDelay(unsigned long time);  //A function to make a generic delay in seconds
unsigned long BC_delay(unsigned char state, unsigned char weight,unsigned long time ); // the delay for chicken and beef
unsigned long A_delay(unsigned long time); //determine the delay fot popcorn
unsigned long D_delay (unsigned long time, unsigned char seconds, unsigned char minutes);//A function to determine D(custom) delay
void statesDelay(unsigned long time); ////function to make a delay AND update the lcd 


