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
 *  - Funktion des Watchdog-Timers im Watchdog-Modus
 *  - LED blinkt beim Programmstart
 *  - Watchdog-Timer löst nach 1 sec ein Reset aus
 *  - Watchdog-Timer wird zurückgesetzt, wenn Taster an P2.0 gedrückt wird
 */

#include <msp430.h>
#include <stdint.h>

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P1DIR |= BIT0;
	P1OUT |= BIT0;
	__delay_cycles(100000L);
	P1OUT &= ~BIT0;

	P2IES |= BIT0;
	P2IFG &= ~BIT0;
	P2IE |= BIT0;

	WDTCTL = WDTPW + WDTCNTCL + WDTSSEL;

	__enable_interrupt();

	while (1) {
		__low_power_mode_3();
	}
}

#pragma vector=PORT2_VECTOR
__interrupt void PORT2_ISR() {
	if (P2IFG & BIT0) {
		P2IFG &= ~BIT0;
		WDTCTL = WDTPW + WDTCNTCL + WDTSSEL;
	}
}
