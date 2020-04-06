/**
 * @author 	Robert Fromm
 * @date	März 2019
 * @brief	Beispielprogramm für die Vorlesung Mikrorechnerarchitektur
 * 			Fakultät EIT, HTWK Leipzig
 *
 * Aus Kapitel:
 * 	9.1.3 Möglichkeiten der Spannungswandlung -> Ladungspumpen
 *
 * Benötigte Hardware:
 *	- Ladungspumpe an P2.0
 *	- 3,3 V und GND Anschluss der Ladepumpe
 *
 * Funktion:
 *  - Erzeugen einer Rechteckspannung mit ACLK-Ausgang
 */

#include <msp430.h>
#include <stdint.h>

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P2DIR |= BIT0;
	P2SEL |= BIT0;

	while (1) {
		__low_power_mode_3();
	}
}
