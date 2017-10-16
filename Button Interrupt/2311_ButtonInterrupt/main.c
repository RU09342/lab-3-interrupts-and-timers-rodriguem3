//Matthew Rodriguez
#include <msp430.h>

/**
 * main.c
 */

unsigned long count = 0;
int buttonPressed = 0;

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;
    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;
    P1DIR |= BIT0; //set Port 1.0 output ---LED
    P2DIR |= BIT0; //set Port 2.0 output ---LED

    P1DIR &= ~(BIT1); //set Port 1.1 input --- pushbutton
    P1REN |= BIT1; //enable pull-up resistor on
    P1OUT |= BIT1;
    P1IE |= BIT1; //enable the interrupt on Port 1.1
    P1IES |= BIT1; //set as falling edge
    P1IFG &= ~(BIT1); //clear interrupt flag

    TB0CTL = TBSSEL_1 + MC_1;
    TB0CCTL0 = 0x10;
    TB0CCR0 = 12000;

    P2OUT &= ~BIT0;

    __enable_interrupt();
    _BIS_SR(LPM0_bits + GIE);

}

#pragma vector=TIMER0_B0_VECTOR
__interrupt void Timer_B(void)
{

    if(buttonPressed == 1){
        P2OUT ^= BIT0;
    }
}

#pragma vector=PORT1_VECTOR
__interrupt void PORT_1(void)
{
    P1IE &= ~BIT1;
    __delay_cycles(1);
    P1IE |= BIT1;
    buttonPressed ^= 1;

    P1IFG &= ~(BIT1); //clear interrupt flag
}
