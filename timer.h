void SysTick_wait(unsigned long delay); //initialize the systic timer
void genericDelay(unsigned long time);  //A function to make a generic delay in seconds
int BC_delay(unsigned char state, int weight); // the delay for chicken and beef
int A_delay(); //determine the delay for popcorn
int D_delay (int seconds, int minutes);//A function to determine D(custom) delay

void statesDelay(int time); ////function to make a delay AND update the lcd 
void displayTime (int seconds, int minutes); //A function to display time in the wanted format
