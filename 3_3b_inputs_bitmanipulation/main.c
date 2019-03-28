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
 * 	  - P1.0 bis P1.3 werden angeschalten
 * 	- Taster an Port2
 * 	  - Taster 1: P2.0
 * 	  - Taster 2: P2.1
 * 	  - Taster 3: P2.2
 * 	  - Taster 4: P2.5
 *
 * Funktion:
 * 	- Durch Bitmanipulation werden Tasten einzeln abgefragt
 * 	- P1.0 bis P1.3 werden beim Tastedruck entsprechend angeschalten
 */

#include <msp430.h>
#include <stdint.h>

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P1DIR = 0xFF;
	P1OUT = 0x00;

	while (1) {
		if (P2IN & BIT0) {
			// Taster 1 losgelassen
			P1OUT &= ~BIT0;
		} else {
			// Taster 1 gedrückt
			P1OUT |= BIT0;
		}

		if (P2IN & BIT1) {
			// Taster 2 losgelassen
			P1OUT &= ~BIT1;
		} else {
			// Taster 2 gedrückt
			P1OUT |= BIT1;
		}

		if (P2IN & BIT2) {
			// Taster 3 losgelassen
			P1OUT &= ~BIT2;
		} else {
			// Taster 3 gedrückt
			P1OUT |= BIT2;
		}

		if (P2IN & BIT5) {
			// Taster 4 losgelassen
			P1OUT &= ~BIT3;
		} else {
			// Taster 4 gedrückt
			P1OUT |= BIT3;
		}
	}
}
