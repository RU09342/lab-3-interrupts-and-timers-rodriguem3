#include <msp430.h>


int buttonDown;

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD; //Stop WD
    PM5CTL0 &= ~LOCKLPM5;
    P1DIR |= BIT0; //set Port 1.0 output
    P5DIR &= ~(BIT5); //set Port 5.5 input --- pusbut
    P5REN |= BIT5; //enable pull-up resistor on
    P5OUT |= BIT5;
    P5IE |= BIT5; //enable the interrupt on Port 5.4
    P5IES |= BIT5; //set as falling edge
    P5IFG &= ~(BIT5); //clear interrupt flag
    TA0CTL = TASSEL_1 + MC_1 + ID_1; //Set up Timer A, Count up, and divider 2.
    TA0CCTL0 = 0x10; //Set up compare mode for CCTL
    TA0CCR0 = 1600;
    __enable_interrupt(); //enable interrupt
    _BIS_SR(LPM4_bits + GIE); // Enter Low Power Mode
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0(void)
{

    P1OUT ^= 0x01;

}

#pragma vector=PORT5_VECTOR
__interrupt void PORT_5(void)
{
    //Debouncing
    P5IE &= ~BIT5;
    __delay_cycles(1);

    if (buttonDown == 0) //Falling-dge of a button
    {
        TA1CTL = TASSEL_1+ MC_3;
        TA1CCR0 = 0xFFFF;
        TA1CCTL0 = CAP;
        buttonDown = 1;
        TA0CCR0 = 1;
    }
    else if (buttonDown == 1) //Rising-edge of a button
    {
        TA1CTL = MC_0; //Stop Counting
        TA0CCR0 = TA1R; //Assign new value for CCR0
        if (TA0CCR0 > 65500)
            TA0CCR0 = 0xFFFF;
        if (TA0CCR0 < 2000)
            TA0CCR0 = 2000;
        TA1CTL = TACLR; //Clear Timer A1
        buttonDown = 0;
    }

    P5IES ^= BIT5;
    P5IE |= BIT5;
    P5IFG &= ~(BIT5);
}
