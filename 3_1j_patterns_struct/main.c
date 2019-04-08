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
 * 	- Abspeichern der Muster in einem struct-Element
 * 	- Verwendung von Zeigern
 * 	- Strukturierung des Programmes durch Module
 */

#include <msp430.h>
#include <stdint.h>
#include "patterns.h"

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	patterns_init();

	while (1) {
		patterns_show();
	}
}
