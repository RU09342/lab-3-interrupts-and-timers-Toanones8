#include <msp430.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;     // Stop WDT

  P1OUT &= 0x00;               // Shut down everything
  P1DIR &= 0x00;
  P1DIR |= BIT0;            // P1.0 and P1.6 pins output the rest are input

  P5REN |= BIT6;                   // Enable internal pull-up/down resistors
  P5OUT |= BIT6;                   //Select pull-up mode for P1.3

  P5IE |= BIT6;   // P1.3 interrupt enabled
  P5IES |= BIT6;                     // P1.3 Hi/lo edge
  P5IFG &= ~BIT6;    // P1.3 IFG cleared

  PM5CTL0 &= ~LOCKLPM5;

  _BIS_SR(CPUOFF + GIE);          // Enter LPM0 w/ interrupt
  while(1)                          //Loop forever, we work with interrupts!
  {}
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
   P1OUT ^= BIT0;                      // Toggle P1.6
   P5IFG &= ~BIT6;                     // P1.3 IFG cleared
}
