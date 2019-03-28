/**
 * @author 	Robert Fromm
 * @date	M�rz 2019
 * @brief	Beispielprogramm f�r die Vorlesung Mikrorechnerarchitektur
 * 			Fakult�t EIT, HTWK Leipzig
 *
 * Aus Kapitel:
 * 	3.1 Ausg�nge der parallelen Schnittstelle
 *
 * Ben�tigte Hardware:
 * 	- 8 LEDs an P1.0 bis P1.7
 *
 * Funktion:
 * 	- Anzeigen eines Lauflichtes an den LEDs P1.0 bis P1.7
 * 	- Verwendung der Bitshift-Operation
 */

#include <msp430.h>
#include <stdint.h>

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P1DIR = 0xFF;	// Alle Pin als Ausg�nge
	P1OUT = 0x00;   // Alle Ausg�nge auf Low

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
