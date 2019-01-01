#include <msp430.h>
#include <stdint.h>

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P1DIR = 0xFF;	// Alle Pin als Ausgänge
	P1OUT = 0x00;   // Alle Ausgänge auf Low

	while (1) {
		// LEDs einzeln anschalten
		for (uint8_t i = 0; i < 8; i++) {
			P1OUT |= (1 << i);
			__delay_cycles(200000);
		}

		// LEDs einzeln ausschalten
		for (uint8_t i = 0; i < 8; i++) {
			P1OUT &= ~(1 << i);
			__delay_cycles(200000);
		}
	}
}
