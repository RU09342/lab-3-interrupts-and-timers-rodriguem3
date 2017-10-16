# Rapid Press Game
## Author: Matthew Rodriguez, Seamus Plunkett, Austin Huang
## Summary 
An LED on the board wil blink at a contant rate, another LED will blink a constant different rate.

## Notes
Because this program was and can be run on different MSP430 boards that use different pins, the specific pin numbers will be replaced with the variable "X" (i.e. PXOUT ^= BITX;)
The first thing this program does is stop the watch dog timer, this is done to ensure that the processor will not reset. This is done with the following statement:
```c
	WDTCTL = WDTPW + WDTHOLD or WDTCTL = WDTPW | WDTHOLD
```
The pins are first initialized to determine which are inputs and outputs. 
Example:
```c
	PXDIR |= BITX;                          // Set P1.0 to output direction
    PXOUT &= ~BITX;                         // Switch LED off
    PXDIR  &= ~BITX;                        // Set P5.6 as input
    PXOUT |= BITX;                          // Configure P5.6 for Pull-Up
    PXREN |= BITX;                          // Enable Pull Up of P5.6
```
Timer is then initialized.
Example:
```c
	TA0CTL = TASSEL_2 + MC_1 +TACLR ;
    TA0CCTL1 = OUTMOD_7;
    TA0CCR0 = 1000;
    TA0CCR1 = 500;
```
## How it works
Each player will have a score that is stored in a field variable. The player with the higher score is winning. These scores determine the state of an LED(on/off).
### LED state
Timer A is set with a CCR0 value of 500. This means every 500 cycles an interupt will occure. Everytime this interupt occurs a block of code that
compares the two player score fields will be executed. if player1 has a higher scroe the LED will turn off if player 2 has a higher score the
LED will turn off. If the two players have equal score the LED will blink.
### Button Press
When a button is pressed on the board an interupt is caused executing a line of code that will increment its respictive player score value.

## Differences between boards
The pin assignments on each board may be different.
Some boards with FR require high impedence on a pin to be disabled.
Some boards may use a different timer.
Some boards may be unable to use PXSEL and will need the timer to be connected to the LED externally.

## Implementation 
Use a C compiler to run the code and upload it to an MSP430. Once uploaded player one and player two may press their respective buttons to increase their score.
if player one is winning an LED will shine, if player 2 is winning the LED will not shine. A tie will result in the LED blinking rapidly.
