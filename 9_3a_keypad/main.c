/**
 * @author 	Robert Fromm
 * @date	März 2019
 * @brief	Beispielprogramm für die Vorlesung Mikrorechnerarchitektur
 * 			Fakultät EIT, HTWK Leipzig
 *
 * Aus Kapitel:
 * 	9.3.3  Taster-Matrix
 *
 * Benötigte Hardware:
 * 	- LCD des Education Systems
 *	- Tastermatrix an P4.0 bis P4.6
 *
 * Funktion:
 *  - Anzeigen der gedrückten Tasten auf dem LCD
 */

#include <msp430.h>
#include <stdint.h>

uint16_t read_keypad();

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P1DIR |= 0xff;

	P4OUT &= ~(BIT5 + BIT4 + BIT7);  // Alle Spalten auf L, wenn Output

	P4OUT |= BIT1 + BIT2 + BIT3 + BIT4; // Alle Zeilen mit Pullup
	P4REN |= BIT1 + BIT2 + BIT3 + BIT4;

	while (1) {
		P1OUT = read_keypad();
	}
}

uint16_t read_keypad() {
	uint16_t pressed_keys = 0;

	for (uint8_t i = 0; i<3; i++) {
		P4DIR &= ~(BIT5 + BIT4 + BIT7); // Alle Spalten auf HighZ
		P4DIR |= (BIT5 << i); // Entsprechende Spalte auf Output L
		__delay_cycles(10);
		pressed_keys = P4IN; // Zeilen auslesen und in pressed_keys eintragen
	}

	return pressed_keys;
}
