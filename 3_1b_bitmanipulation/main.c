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
 * 	- Demonstration der Bitmanipulation
 * 	- LEDs an P1.0 und P1.1 werden an- und ausgeschaltet
 * 	- Programm muss im Debugger ausgeführt werden, da Programm sehr schnell abläuft
 */

#include <msp430.h>

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P1DIR = 0xFF;	// Alle Pin als Ausgänge
	P1OUT = 0x00;   // Alle Ausgänge auf Low

	while (1) {
		P1OUT |= BIT0;	// set P1.0
		P1OUT ^= BIT1;	// toggle P1.1

		P1OUT &= ~BIT0;	// clear P1.0
		P1OUT ^= BIT1;	// toggle P1.1
	}
}
