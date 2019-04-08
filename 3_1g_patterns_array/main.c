/**
 * @author 	Robert Fromm
 * @date	März 2019
 * @brief	Beispielprogramm für die Vorlesung Mikrorechnerarchitektur
 * 			Fakultät EIT, HTWK Leipzig
 *
 * Aus Kapitel:
 * 	3.1 Ausgänge der parallelen Schnittstelle
 *
 * Benötigte Hardware:
 * 	- 8 LEDs an P1.0 bis P1.7
 *
 * Funktion:
 * 	- Ablauf eines Musters an den LEDs
 * 	- Abspeichern der Muster in einem Array
 */

#include <msp430.h>
#include <stdint.h>

const uint8_t patterns[] = {0x81, 0x42, 0x24, 0x18, 0x3c, 0x66, 0xc3};
const uint8_t pattern_length = 7;

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P1DIR = 0xFF;	// Alle Pin als Ausgänge
	P1OUT = 0x00;   // Alle Ausgänge auf Low

	uint8_t pattern_id = 0;
	while (1) {
		// Muster ausgeben
		P1OUT = patterns[pattern_id];

		// Weiterzählen, ggf. zurücksetzen
		pattern_id++;
		if (pattern_id >= pattern_length) {
			pattern_id = 0;
		}

		__delay_cycles(200000);
	}
}
