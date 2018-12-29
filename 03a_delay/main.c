#include <msp430.h>
#include <stdint.h>

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P1DIR = 0xFF;	// Alle Pin als Ausg�nge
	P1OUT = 0x00;   // Alle Ausg�nge auf Low

	while (1) {
		P1OUT |= BIT0;	// set P1.0
		P1OUT &= ~BIT1;	// clear P1.1

		volatile uint16_t i = 30000;
		while (i > 0) {
			i--;
		}

		P1OUT &= ~BIT0;	// clear P1.0
		P1OUT |= BIT1;	// set P1.1

		i = 30000;
		while (i > 0) {
			i--;
		}
	}
}
