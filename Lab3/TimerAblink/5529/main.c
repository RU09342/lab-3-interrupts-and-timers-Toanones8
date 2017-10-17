#include <msp430.h>

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

  P1DIR |= BIT0;                            // P1.0 output
  P1DIR |= BIT1;

  // Timer 0 Configuration
  TACTL = MC_0;// Stop the timer
  TACTL = TASSEL_2 + ID_3 + TAIE;// Timer Clock = SMCLK,1MHz/8 = 125KHz,enable TAR interrupt

  CCR0 = 10000; // Count in CCR0 register
  CCR1 = 300000; // Count in CCR1 register
  CCR2 = 40000; // Count in CCR2 register

  CCTL0 |= CCIE; // Enable CCR0 interrupt
  CCTL1 |= CCIE; // Enable CCR1 interrupt
  CCTL2 |= CCIE; // Enable CCR2 interrupt

  TACTL |= MC_2; // Start the timer in continuous mode

  _BIS_SR(LPM0_bits + GIE); // Sleep in LPM0 with interrupts enabled               // SMCLK, Contmode

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0 (void)
{
   P1OUT ^= BIT0;                          // Toggle P1.0
}


#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A(void)
{
  switch( TA0IV )
  {
  case  2:                                  // CCR1
    {
    //P1OUT ^= 0x01;                          // Toggle P1.0
    //CCR1 += 500000;                          // Add Offset to CCR1
    }
           break;
  case  4:
  {
    P1OUT^=BIT1;
    CCR2+=300000;

  }

      break;
  case 10:

      break;

}
}
