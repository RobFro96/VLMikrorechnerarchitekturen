#include <msp430.h>
#include <stdint.h>

const uint8_t patterns[] = { 0x81, 0x42, 0x24, 0x18, 0x3c, 0x66, 0xc3 };
const uint8_t pattern_length = 7;

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P1DIR = 0xFF;	// Alle Pin als Ausgänge
	P1OUT = 0x00;   // Alle Ausgänge auf Low

	// Zeiger auf 1. Element
	const uint8_t *pattern_pointer = patterns;

	while (1) {
		// Muster ausgeben
		P1OUT = *pattern_pointer;

		// Weiterzählen, ggf. zurücksetzen
		pattern_pointer++;
		if (pattern_pointer >= patterns + pattern_length) {
			pattern_pointer = patterns;
		}

		__delay_cycles(200000);
	}
}
