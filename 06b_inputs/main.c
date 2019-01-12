#include <msp430.h>
#include <stdint.h>

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P1DIR = 0xFF;
	P1OUT = 0x00;

	while (1) {
		if (P2IN & BIT0) {
			// Taster 1 losgelassen
			P1OUT &= ~BIT0;
		} else {
			// Taster 1 gedrückt
			P1OUT |= BIT0;
		}

		if (P2IN & BIT1) {
			// Taster 2 losgelassen
			P1OUT &= ~BIT1;
		} else {
			// Taster 2 gedrückt
			P1OUT |= BIT1;
		}

		if (P2IN & BIT2) {
			// Taster 3 losgelassen
			P1OUT &= ~BIT2;
		} else {
			// Taster 3 gedrückt
			P1OUT |= BIT2;
		}

		if (P2IN & BIT5) {
			// Taster 4 losgelassen
			P1OUT &= ~BIT3;
		} else {
			// Taster 4 gedrückt
			P1OUT |= BIT3;
		}
	}
}
