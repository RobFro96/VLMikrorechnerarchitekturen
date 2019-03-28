/**
 * @author 	Robert Fromm
 * @date	M�rz 2019
 * @brief	Beispielprogramm f�r die Vorlesung Mikrorechnerarchitektur
 * 			Fakult�t EIT, HTWK Leipzig
 *
 * Aus Kapitel:
 * 	3.3 Eing�nge der parallelen Schnittstelle
 *
 * Ben�tigte Hardware:
 * 	- 8 LEDs an P1.0 bis P1.7
 * 	- Taster an P2.0
 *
 * Funktion:
 * 	- Beim Dr�cken des Tasters an P2.0 wird Register P1OUT hochgez�hlt
 * 	- Wert des Z�hlers in Bin�r an den LEDs ablesbar
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
