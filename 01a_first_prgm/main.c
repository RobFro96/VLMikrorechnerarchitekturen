#include <msp430.h>

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P1DIR = 0xFF;	// Datenflussrichtung von Port1 auf Ausgang

	while (1) {
		P1OUT = 0xA5;	// Muster 1 am Ausgang ausgeben
		P1OUT = 0x5A;   // Muster 2 am Ausgang ausgeben
	}
}
