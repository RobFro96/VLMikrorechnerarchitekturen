/**
 * @author 	Robert Fromm
 * @date	März 2019
 * @brief	Beispielprogramm für die Vorlesung Mikrorechnerarchitektur
 * 			Fakultät EIT, HTWK Leipzig
 *
 * Aus Kapitel:
 * 	7. Analog-Digital-Umsetzer
 *
 * Benötigte Hardware:
 *	- LED an P1.0
 *	- Freier Pin P4.3 mit 220k-Widerstand zur Berührungsfläche
 *
 * Funktion:
 *  - Demonstration eines kapazitiven Touchsensor ohne Capacitive-Sensing-Modul
 *  - LED an P1.0 wird angeschaltet, wenn eine Berührung detektiert wurde
 */

#include <msp430.h>
#include <stdint.h>

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;

	P1DIR |= BIT0;
	P1OUT |= BIT0;

	__enable_interrupt();

	while (1) {
		P4OUT |= BIT3;
		P4DIR |= BIT3;

		__delay_cycles(500);

		P4OUT &= ~BIT3;
		P4DIR &= ~BIT3;

		__delay_cycles(30);

		if (P4IN & BIT3) {
			P1OUT |= BIT0;
		} else {
			P1OUT &= ~BIT0;
		}

	}

}

