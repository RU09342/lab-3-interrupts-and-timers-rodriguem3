#include <msp430.h>

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;// Stop WD
    P1SEL =0; //Choose GPIO option for P1
    P1OUT &= ~(BIT0); // Clear P1.0
    P1DIR |=BIT0; //set Port 1.0 output
    P4SEL =0; //Choose GPIPO option for P4
    P4OUT &= ~(BIT7);
    P4DIR |=BIT7; //set Port 4.7 output
    TA0CTL= TASSEL_1 + MC_1; //Set up Timer A0 in Up mode
    TA0CCTL0 = 0x10; //Set up Timer A0 in the compare mode
    TA0CCR0 = 12000;  //set up TA0CCR0, and have Timer A0 (TA0R) to count to its contents.
                      // 32kHz/12000 is the frequency at which the LED will blink
    TA0CCTL1 = 0x10;    // Set up Timer A instance 1 in Compare mode
    TA0CCR1 = 3000;     // Set up value for CCR1 to 3000.
    _BIS_SR(LPM4_bits + GIE);//enter LPM4 mode and enable global interrupt
}
//Port 1 ISR
#pragma vector=TIMER0_A0_VECTOR
#pragma vector = TIMER0_A1_VECTOR
__interrupt void Timer_A(void)
{
    P1OUT ^= 0x01; //Toggle the P1.0 LED
    switch (TA0IV) //Choose the right Interrupt Vector for value of TA0CCR1
    {
        case TA0IV_TACCR1: P4OUT ^= BIT7; //Toggle the P4.7 LED
        break;
    }
}
