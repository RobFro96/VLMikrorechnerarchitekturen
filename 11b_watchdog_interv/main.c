#include <msp430.h>
#include <stdint.h>

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P1DIR |= BIT0;
	P1OUT &= ~BIT0;

	WDTCTL = WDTPW + WDTTMSEL + WDTCNTCL + WDTSSEL;
	IE1 |= WDTIE;

	__enable_interrupt();

	while (1) {
		__low_power_mode_3();
	}
}

#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR() {
	P1OUT ^= BIT0;
}
