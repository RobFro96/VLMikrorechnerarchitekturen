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
 * 	- Taster an P2.0, P2.1, P2.2, P2.5
 * 	- Servo-Motor
 * 	  - Vcc (rot) an 5 V
 * 	  - GND (braun) an GND
 * 	  - Signal (orange) an P1.2
 * 	- 32,768 kHz-Quarz an XIN, XOUT
 *
 * Funktion:
 *  - Ausgabe des PWM-Signals für den Servo-Motor an P1.3
 *  - Tasten 1 und 2 um schrittweise nach rechts oder links zu drehen
 *  - Tasten 3 und 4 um komplett nach recht oder links zu drehen
 */

#include <msp430.h>
#include <stdint.h>

volatile uint8_t pwm = 48;

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P1SEL |= BIT2;
	P1DIR |= BIT2;

	CCR0 = 655;
	CCR1 = pwm;
	CCTL1 = OUTMOD_7;
	TACTL = TASSEL_1 + MC_1 + TACLR;

	P2IES |= BIT0 + BIT1 + BIT2 + BIT5;
	P2IFG &= ~(BIT0 + BIT1 + BIT2 + BIT5);
	P2IE |= BIT0 + BIT1 + BIT2 + BIT5;

	__enable_interrupt();

	while (1) {
		__low_power_mode_3();
	}
}

#pragma vector=PORT2_VECTOR
__interrupt void PORT2_ISR() {
	if (P2IFG & BIT0) {
		P2IFG &= ~BIT0;
		pwm -= 2;
	}

	if (P2IFG & BIT1) {
		P2IFG &= ~BIT1;
		pwm += 2;
	}

	if (P2IFG & BIT2) {
		P2IFG &= ~BIT2;
		pwm = 32;
	}

	if (P2IFG & BIT5) {
		P2IFG &= ~BIT5;
		pwm = 64;
	}

	if (pwm > 64)
		pwm = 64;
	if (pwm < 32)
		pwm = 32;

	CCR1 = pwm;
}
