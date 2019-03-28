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
 *  - Verwenden aller CCR-Register als Interrupt-Quellen
 *  - Einschalten des Timer-Overflow-Interrupts
 *  - Togglen der LEDs an P1.0 bis P1.3 mit verschiedenen Frequenzen
 *    - LED an P1.2: 1 sec durch CCR0-Interrupt
 *    - LED an P1.1: 0.5 sec durch CCR1-Interrupt
 *    - LED an P1.0: 0.25 sec durch CCR2-Interrupt
 *    - LED an P1.3: 2 sec durch Timer-Overflow-Interrupt
 *
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
	CCR1 = 0x4000;
	CCTL1 = CCIE;
	CCR2 = 0x2000;
	CCTL2 = CCIE;
	TACTL = TASSEL_1 + MC_2 + TACLR + TAIE;

	__enable_interrupt();

	while (1) {
		__low_power_mode_3();
	}
}

#pragma vector=TIMERA0_VECTOR
__interrupt void TIMERA0_ISR() {
	CCR0 += 0x8000;
	P1OUT ^= BIT2;
}

#pragma vector=TIMERA1_VECTOR
__interrupt void TimerA1_ISR() {
	switch (TAIV) {
	case 2:
		// CCR1 Interrupt
		CCR1 += 0x4000;
		P1OUT ^= BIT1;
		break;
	case 4:
		// CCR2 Interrupt
		CCR2 += 0x2000;
		P1OUT ^= BIT0;
		break;
	case 10:
		// Timer Overflow
		P1OUT ^= BIT3;
		break;
	}
}
