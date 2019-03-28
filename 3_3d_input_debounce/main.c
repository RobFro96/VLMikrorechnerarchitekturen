/**
 * @author 	Robert Fromm
 * @date	März 2019
 * @brief	Beispielprogramm für die Vorlesung Mikrorechnerarchitektur
 * 			Fakultät EIT, HTWK Leipzig
 *
 * Aus Kapitel:
 * 	3.3 Eingänge der parallelen Schnittstelle
 *
 * Benötigte Hardware:
 * 	- 8 LEDs an P1.0 bis P1.7
 * 	- Taster an P2.0
 *
 * Funktion:
 * 	- Beim Drücken des Tasters an P2.0 wird Register P1OUT hochgezählt
 * 	- Wert des Zählers in Binär an den LEDs ablesbar
 */

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
		__delay_cycles(5000L);

		// Warte solange P2.0 Low
		while (!(P2IN & BIT0)) {
		}

		__delay_cycles(5000L);
	}
}
