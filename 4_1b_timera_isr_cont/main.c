/**
 * @author 	Robert Fromm
 * @date	März 2019
 * @brief	Beispielprogramm für die Vorlesung Mikrorechnerarchitektur
 * 			Fakultät EIT, HTWK Leipzig
 *
 * Aus Kapitel:
 * 	4.1 Erzeugen regelmäßiger Interruptsignale
 *
 * Benötigte Hardware:
 * 	- 8 LEDs an P1.0 bis P1.7
 * 	- 32,768 kHz-Quarz an XIN, XOUT
 *
 * Funktion:
 *  - Togglen der LED durch TimerA-CCR0-Interrupt
 *  - Anpassen der Interrupt-Periode auf 1 sec durch Verändern des CCR0-Wertes
 */

#include <msp430.h>
#include <stdint.h>

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P1DIR = 0xFF;
	P1OUT = 0x00;

	CCR0 = 0x8000;
	CCTL0 = CCIE;
	TACTL = TASSEL_1 + MC_2 + TACLR;

	__enable_interrupt();

	while (1) {
		__low_power_mode_3();
	}
}

#pragma vector=TIMERA0_VECTOR
__interrupt void TIMERA0_ISR() {
	P1OUT ^= BIT0;
	CCR0 += 0x8000;
}
