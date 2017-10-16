#include <msp430.h>

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;

    P1SEL =0; //Select GPIO option
    P1DIR |=BIT0; //set Port 1.0 output
    P1DIR &=~(BIT1); //set Port 1.1 input
    P1REN|=BIT1;//enable pull-up/pull-down resistor on
    P1OUT|=BIT1; //choose the pull-up resistor
    P1IE |=BIT1;//enable the interrupt on Port 1.1
    P1IES |=BIT1;//set as falling edge
    P1IFG &=~(BIT1);//clear interrupt flag
    _BIS_SR(LPM4_bits + GIE);//enter LPM4 mode and enable global interrupt
}

#pragma vector=PORT1_VECTOR
__interrupt void PORT_1(void)
{
    P1OUT ^=0x01; // Change state of P1.1
    volatile unsigned int dur = 1000;
    do (dur--);
    while (dur != 0);
    P1IFG &=~(BIT1); // Clear flag
}
