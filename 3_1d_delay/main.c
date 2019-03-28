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
 * 	- Verwenden einer Programmschleife, um das Programm zu verz�gern
 * 	- Unterteilen der Programmierung in eine Funktion
 * 	- LEDs an P1.0 und P1.1 werden an- und ausgeschaltet
 */

#include <msp430.h>
#include <stdint.h>

// Prototypen
void delay(uint16_t duration);

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P1DIR = 0xFF;	// Alle Pin als Ausg�nge
	P1OUT = 0x00;   // Alle Ausg�nge auf Low

	while (1) {
		P1OUT |= BIT0;	// set P1.0
		P1OUT &= ~BIT1;	// clear P1.1

		delay(30000);

		P1OUT &= ~BIT0;	// clear P1.0
		P1OUT |= BIT1;	// set P1.1

		delay(30000);
	}
}

void delay(uint16_t duration) {
	volatile uint16_t i = duration;
	while (i > 0) {
		i--;
	}
}
