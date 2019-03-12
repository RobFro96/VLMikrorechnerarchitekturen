#include <msp430.h>
#include <stdint.h>

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P1DIR = 0xFF;
	P1OUT = 0x00;

	CCR0 = 0x8000;
	CCTL0 = CCIE;
	TACTL = TASSEL_1 + MC_1 + TACLR;

	__enable_interrupt();

	while (1) {
		__low_power_mode_3();
	}
}

#pragma vector=TIMERA0_VECTOR
__interrupt void TIMERA0_ISR() {
	P1OUT ^= BIT0;
}
