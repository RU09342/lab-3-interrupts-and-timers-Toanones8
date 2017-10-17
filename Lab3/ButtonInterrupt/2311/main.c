#include <msp430.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;     // Stop WDT

  P1OUT &= 0x00;               // Shut down everything
  P1DIR &= 0x00;
  P1DIR |= BIT0;            // P1.0 and P1.6 pins output the rest are input

  P1REN |= BIT1;                   // Enable internal pull-up/down resistors
  P1OUT |= BIT1;                   //Select pull-up mode for P1.3

  P1IE |= BIT1;   // P1.3 interrupt enabled
  P1IES |= BIT1;                     // P1.3 Hi/lo edge
  P1IFG &= ~BIT1;                  // P1.3 IFG cleared

  _BIS_SR(CPUOFF + GIE);          // Enter LPM0 w/ interrupt
  while(1)                          //Loop forever, we work with interrupts!
  {}
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
   P1OUT ^= BIT0;                      // Toggle P1.6
   P1IFG &= ~BIT1;                     // P1.3 IFG cleared
}
