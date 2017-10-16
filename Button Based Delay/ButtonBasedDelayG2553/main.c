//Matthew Rodriguez
#include <msp430.h> 



int buttonEdge;

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD; //Stop WD
    P1SEL &= ~BIT0;
    P1DIR |= BIT0;
    P1OUT &= ~(BIT0);
    P1DIR &= ~(BIT3);
    P1REN |= BIT3;
    P1OUT |= BIT3;
    P1IE |= BIT3; //enable the interrupt on Port 1.3
    P1IES |= BIT3; //set as falling edge
    P1IFG &= ~(BIT3); //clear interrupt flag
    TA0CTL = TASSEL_1 + MC_1 + ID_2; //Set up Timer A, Count up, and divider 4.
    TA0CCTL0 = 0x10;
    TA0CCR0 = 1600;

    //enter LPM0 mode and enable global interrupt
           _BIS_SR(LPM0_bits + GIE);
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0(void)
{

    P1OUT ^= 0x01; //Toggle LED

}

// Timer0 Interrupt Service Routine
#pragma vector=PORT1_VECTOR
__interrupt void PORT_1(void)
{
    P1IE &= ~BIT3;
    __delay_cycles(100);

if (buttonEdge == 0) //Falling-edge of a button
    {
        TA1CTL = TASSEL_1+ MC_1;
        TA1CCR0 = 0xFFFF;
        TA1CCTL0 = CAP; //Capture mode
        buttonEdge = 1;
        TA0CCR0 = 1; //Reset CCR0

    }
    else if (buttonEdge == 1) //Rising-edge of a button
    {
        TA1CTL = MC_0; //Stop Counting
        TA0CCR0 = TA1R; //Assign new value for CCR0
        if (TA0CCR0 > 65500) //Fastest
            TA0CCR0 = 0xFFFF;
        if (TA0CCR0 < 2000) // Slowest
            TA0CCR0 = 2000;
        TA1CTL = TACLR; //Clear Timer A1
        buttonEdge = 0;
    }

    P1IES ^= BIT3;
    P1IE |= BIT3;
    P1IFG &= ~(BIT3);
}
