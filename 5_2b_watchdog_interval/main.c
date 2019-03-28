/**
 * @author 	Robert Fromm
 * @date	März 2019
 * @brief	Beispielprogramm für die Vorlesung Mikrorechnerarchitektur
 * 			Fakultät EIT, HTWK Leipzig
 *
 * Aus Kapitel:
 * 	5.2 Watchdog Timer
 *
 * Benötigte Hardware:
 * 	- LED an P1.0
 * 	- Taster an P2.0
 * 	- 32,768 kHz-Quarz an XIN, XOUT
 *
 * Funktion:
 *  - Funktion des Watchdog-Timers im Intervall-Modus
 *  - Watchdog-Interrupt wird einmal pro Sekunde ausgelöst
 *  - LED wird getogglet
 */

#include <msp430.h>
#include <stdint.h>

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P1DIR |= BIT0;
	P1OUT &= ~BIT0;

	WDTCTL = WDTPW + WDTTMSEL + WDTCNTCL + WDTSSEL;
	IE1 |= WDTIE;

	__enable_interrupt();

	while (1) {
		__low_power_mode_3();
	}
}

#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR() {
	P1OUT ^= BIT0;
}
