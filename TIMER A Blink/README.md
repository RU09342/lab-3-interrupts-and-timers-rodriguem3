# Timer A Blink
## Author: Matthew Rodriguez, Seamus Plunkett, Austin Huang
## Summary 
An LED on the board wil blink at a contant rate, another LED will blink a a constant different rate.

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
When the timer reaches a certain value an interupt will occure. When the timer reaches the TA0CCR0 the LED will toggle on/off, after a certain amount of time
based on how many times that interupt is caused the next LED will toggle on/off.

## Differences between boards
The pin assignments on each board may be different.
Some boards with FR require high impedence on a pin to be disabled.
Some boards may use a different timer.
Some boards may be unable to use PXSEL and will need the timer to be connected to the LED externally.

## Implementation
Use a C compiler to run the code and upload it to an MSP430. Watch the two LEDs blink... at different rates!
