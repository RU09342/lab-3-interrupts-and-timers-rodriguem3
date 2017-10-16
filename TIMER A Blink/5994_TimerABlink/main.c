//Matthew Rodriguez
#include <msp430.h>

/**
 * main.c
 */

unsigned long count = 0;
int buttonPressed = 0;
unsigned int counter = 0;

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;
    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    P1SEL &= ~BIT0;
    P1DIR |= BIT0; //set Port 1.0 output ---LED
    P1SEL &= ~BIT1;
    P1DIR |= BIT1; //set Port 1.1 output ---LED

    P5DIR &= ~(BIT6); //set Port 5.6 input --- pushbutton
    P5REN |= BIT6; //enable pull-up resistor on
    P5OUT |= BIT6;
    P5IE |= BIT6; //enable the interrupt on Port 5.6
    P5IES |= BIT6; //set as falling edge
    P5IFG &= ~(BIT6); //clear interrupt flag

    TA0CTL = TASSEL_1 + MC_1;
    TA0CCTL0 = 0x10;
    TA0CCR0 = 12000;

    P1OUT &= ~BIT1;

    __enable_interrupt();
    _BIS_SR(LPM4_bits + GIE);

}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
    P1OUT ^= BIT1;
    counter++;
    if(counter == 5){
        P1OUT ^= BIT0;
        counter =0;
    }
}
