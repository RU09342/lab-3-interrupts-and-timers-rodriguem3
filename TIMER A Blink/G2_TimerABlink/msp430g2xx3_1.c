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
    P1SEL &= ~BIT0;
    P1DIR |= BIT0; //set Port 1.0 output ---LED
    P1SEL &= ~BIT6;
    P1DIR |= BIT6; //set Port 1.6 output ---LED

    P1DIR &= ~(BIT3); //set Port 1.3 input --- pushbutton
    P1REN |= BIT3; //enable pull-up resistor on
    P1OUT |= BIT3;
    P1IE |= BIT3; //enable the interrupt on Port 1.3
    P1IES |= BIT3; //set as falling edge
    P1IFG &= ~(BIT3); //clear interrupt flag

    TA0CTL = TASSEL_1 + MC_1;
    TA0CCTL0 = 0x10;
    TA0CCR0 = 12000;

    P1OUT &= ~BIT3;

    __enable_interrupt();
    _BIS_SR(LPM4_bits + GIE);

}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
    P1OUT ^= BIT6;
    counter++;
    if(counter == 5){
        P1OUT ^= BIT0;
        counter =0;
    }
}
