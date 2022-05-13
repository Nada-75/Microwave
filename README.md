# Microwave
This is a Microwave Oven Controller Project using Arm Cortex-m4 for our college. 

# Project Description
• If A is pushed on the keypad (for popcorn), the LCD should show “Popcorn” and then 
cook for 1 minute while the remaining cook time counts down (in seconds) on the LCD, 
then clear the LCD after cooking completes.

• If B (for Beef) or C (for chicken) is pushed on the keypad, the words “Beef weight?” or 
“Chicken weight?” (respectively) appear on the LCD. After that, the user must 
enter an integer value between 1 and 9 on the keypad to indicate how many kilos are 
there to be defrosted.

• If D is pushed on the keypad, the words “Cooking Time?” appear on the LCD. 
After that, the user can enter a value between 1 and 30 to indicate the cooking time 
required in minutes and seconds. This value is displayed on the LCD as it is entered, right 
to left. 

For example, pressing 1 displays 00:01, then pressing 2 displays 00:12, then pressing 4 
displays 01:24, then pressing 5 displays 12:45. Press push button SW1 to clear the LCD 
display and press SW2 to start cooking and counting down (in seconds) the cooking time 
on the LCD.

• Switch SW3 (external push button), simulate the microwave oven door latch

When the microwave completes its function and the timer has counted down to zero (regular 
timed cooking or defrosting), the array of LEDs flashes 3 times, and the buzzer produces 
an audible tone/alarm during these 3 second times periods.
