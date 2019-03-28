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
 * 	- Taster an Port2
 * 	  - Taster 1: P2.0
 * 	  - Taster 2: P2.1
 * 	  - Taster 3: P2.2
 * 	  - Taster 4: P2.5
 *
 * Funktion:
 * 	- Daten vom Register P2IN werden an P1OUT ausgegeben
 * 	- Beim Tastendruck gehen die entsprechenden LEDs an P2.5, P2.2, P2.1, P2.0 aus
 */

#include <msp430.h>
#include <stdint.h>

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P1DIR = 0xFF;

	while (1) {
		P1OUT = P2IN;
	}
}
