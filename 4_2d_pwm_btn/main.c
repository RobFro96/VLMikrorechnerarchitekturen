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
 * 	- LEDs an P1.1, P1.2
 * 	- Taster an P2.0, P2.1
 * 	- 32,768 kHz-Quarz an XIN, XOUT
 *
 * Funktion:
 *  - Ausgabe eines PWM-Signals an P1.2 und P1.3
 *  - Verwenden der Tasten-Interrupts, um die Helligkeiten der LEDs anzupassen
 */

#include <msp430.h>
#include <stdint.h>

volatile uint8_t pwm = 255;

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P1SEL |= BIT2 + BIT3;
	P1DIR |= BIT2 + BIT3;

	CCR0 = 255;
	CCR1 = 255;
	CCTL1 = OUTMOD_7;
	CCR2 = 0;
	CCTL2 = OUTMOD_7;
	TACTL = TASSEL_1 + MC_1 + TACLR;

	P2IES |= BIT0 + BIT1;
	P2IFG &= ~(BIT0 + BIT1);
	P2IE |= (BIT0 + BIT1);

	__enable_interrupt();

	while (1) {
		__low_power_mode_3();
	}
}

#pragma vector=PORT2_VECTOR
__interrupt void PORT2_ISR() {
	if (P2IFG & BIT0) {
		P2IFG &= ~BIT0;
		pwm -= 0x11;
	}

	if (P2IFG & BIT1) {
		P2IFG &= ~BIT1;
		pwm += 0x11;
	}

	CCR1 = pwm;
	CCR2 = 255 - pwm;
}
