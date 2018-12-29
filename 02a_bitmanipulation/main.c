#include <msp430.h>

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P1DIR = 0xFF;	// Alle Pin als Ausgänge
	P1OUT = 0x00;   // Alle Ausgänge auf Low

	while (1) {
		P1OUT |= BIT0;	// set P1.0
		P1OUT ^= BIT1;	// toggle P1.1

		P1OUT &= ~BIT0;	// clear P1.0
		P1OUT ^= BIT1;	// toggle P1.1
	}
}
