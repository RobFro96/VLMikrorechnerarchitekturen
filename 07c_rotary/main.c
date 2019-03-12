#include <msp430.h>
#include <stdint.h>

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P1DIR = 0xFF;
	P1OUT = 0x00;

	P2IES |= BIT3;
	P2IFG &= ~(BIT3);
	P2IE |= BIT3;

	__enable_interrupt();

	while (1) {
		__low_power_mode_4();
	}
}

#pragma vector=PORT2_VECTOR
__interrupt void PORT2_ISR() {
	if (P2IFG & BIT3) {
		P2IFG &= ~BIT3;

		if (P4IN & BIT1) {
			P1OUT++;
		} else if (P4IN & BIT2) {
			P1OUT--;
		}

		__low_power_mode_off_on_exit();
	}
}
