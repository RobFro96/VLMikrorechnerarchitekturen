#include <msp430.h>
#include <stdint.h>

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P1DIR |= BIT0;
	P1OUT |= BIT0;
	__delay_cycles(100000L);
	P1OUT &= ~BIT0;

	P2IES |= BIT0;
	P2IFG &= ~BIT0;
	P2IE |= BIT0;

	WDTCTL = WDTPW + WDTCNTCL + WDTSSEL;

	__enable_interrupt();

	while (1) {
		__low_power_mode_3();
	}
}

#pragma vector=PORT2_VECTOR
__interrupt void PORT2_ISR() {
	if (P2IFG & BIT0) {
		P2IFG &= ~BIT0;
		WDTCTL = WDTPW + WDTCNTCL + WDTSSEL;
	}
}
