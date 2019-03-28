/**
 * @author 	Robert Fromm
 * @date	März 2019
 * @brief	Beispielprogramm für die Vorlesung Mikrorechnerarchitektur
 * 			Fakultät EIT, HTWK Leipzig
 *
 * Aus Kapitel:
 * 	4.2 Erzeugen von Rechtecksignalen
 *
 * Benötigte Hardware:
 * 	- LEDs an P1.1, P1.2, P1.3
 * 	- 32,768 kHz-Quarz an XIN, XOUT
 *
 * Funktion:
 *  - Ausgabe eines PWM-Signals an P1.2 und P1.3
 *  - LED an P1.1 wird angeschaltet und dient zur Referenzhelligkeit
 */

#include <msp430.h>
#include <stdint.h>

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P1SEL |= BIT2 + BIT3;
	P1DIR |= BIT1 + BIT2 + BIT3;
	P1OUT |= BIT1;

	CCR0 = 255;
	CCR1 = 63;
	CCTL1 = OUTMOD_7;
	CCR2 = 7;
	CCTL2 = OUTMOD_7;
	TACTL = TASSEL_1 + MC_1 + TACLR;

	__enable_interrupt();

	while (1) {
		__low_power_mode_3();
	}
}
