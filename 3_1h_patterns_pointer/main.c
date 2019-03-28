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
 * 	- Ablauf eines Musters an den LEDs
 * 	- Abspeichern der Muster in einem Array
 * 	- Verwendung von Zeigern
 */

#include <msp430.h>
#include <stdint.h>

const uint8_t patterns[] = { 0x81, 0x42, 0x24, 0x18, 0x3c, 0x66, 0xc3 };
const uint8_t pattern_length = 7;

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P1DIR = 0xFF;	// Alle Pin als Ausg�nge
	P1OUT = 0x00;   // Alle Ausg�nge auf Low

	// Zeiger auf 1. Element
	const uint8_t *pattern_pointer = patterns;

	while (1) {
		// Muster ausgeben
		P1OUT = *pattern_pointer;

		// Weiterz�hlen, ggf. zur�cksetzen
		pattern_pointer++;
		if (pattern_pointer >= patterns + pattern_length) {
			pattern_pointer = patterns;
		}

		__delay_cycles(200000);
	}
}
