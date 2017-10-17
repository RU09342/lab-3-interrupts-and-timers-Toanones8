#include <msp430.h>

void main(void) {


    WDTCTL = WDTPW | WDTHOLD;   //stop watchdog timer
    //LED control
    P1DIR |= BIT0 + BIT6;   // set leds 1.0 and 1.6 as outputs


    //Button COntrol
    P1REN|= BIT3;   // enable pullup resistor
    P1OUT|= BIT3;   // pullup resistor
    P1IE |= BIT3;   // interrupt enable
    P1IES |= BIT3;  //set interrupt to falling edge
    P1IFG &= ~BIT3; // clear interrupt flag

    //ENable clocks
    TA0CCTL0 = CCIE;    // enable capture and compare
    TA0CTL= TASSEL_1+MC_1;  // set aclock
    __bis_SR_register(LPM0_bits + GIE); // enable interrupts and low power mode

}

#pragma vector= TIMER0_A0_VECTOR // TimerA0 interrupt
__interrupt void Timer_A0 (void)
    {P1OUT ^= BIT0;  // toggle led 1.0
    }


#pragma vector=PORT1_VECTOR     // button interrupt

    __interrupt void PORT_1(void)

    {if (P1IES & BIT3) //if the button is pressed

        {TA1CTL = TASSEL_1 + MC_2;   // timerA1 is set to ACLK, continuous mode
            P1OUT ^= BIT6;              // toggle second LED
            P1IES &= ~BIT3;             // set interrupt to rising edge
            }
            else                // if button is depressed...
            {
               TA0CCR0 = TA1R; // set CCR0 to the value counted in TA1R
              P1OUT &= ~BIT6; // turn off the second LED
             P1IES |= BIT3; // set interrupt to falling edge
             TA1CTL = TACLR; // clear vla
            }P1IFG &= ~BIT3; // clear interrupt flag
            }
