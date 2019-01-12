#include <msp430.h>
#include <stdint.h>

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P1DIR = 0xFF;
	P1OUT = 0x00;

	while (1) {
		// Warte solange P2.0 High
		while (P2IN & BIT0) {
		}

		P1OUT++;

		// Warte solange P2.0 Low
		while (!(P2IN & BIT0)) {
		}

	}
}
