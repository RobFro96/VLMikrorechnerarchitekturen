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
 *  - Erstes Programm
 * 	- Zwei verschiedene Muster werden abwechselnd an den LEDs ausgegeben
 * 	- Programm muss im Debugger ausgef�hrt werden, da Muster sich sehr schnell abwechseln
 */

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
