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
 * 	- Tongeber mit Verstärker an P2.4
 * 	- Taster an P2.0
 * 	- 32,768 kHz-Quarz an XIN, XOUT
 *
 * Funktion:
 *  - Konfigurieren des CCR2-OUTMODs
 *  - Ausgeben einer Frequenz von ca. 440 Hz
 *  - Ton kann durch Taster 2.0 ausgeschaltet werden
 */

#include <msp430.h>
#include <stdint.h>

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P2SEL |= BIT4;
	P2DIR |= BIT4;

	CCR2 = 37;
	CCTL2 = CCIE + OUTMOD_4;
	TACTL = TASSEL_1 + MC_2 + TACLR;

	P2IES |= BIT0;
	P2IFG &= ~BIT0;
	P2IE |= BIT0;

	__enable_interrupt();

	while (1) {
		__low_power_mode_3();
	}
}


#pragma vector=TIMERA1_VECTOR
__interrupt void TimerA1_ISR() {
	switch (TAIV) {
	case 2:
		// CCR1 Interrupt
		break;
	case 4:
		// CCR2 Interrupt
		CCR2 += 37;
		break;
	case 10:
		// Timer Overflow
		break;
	}
}

#pragma vector=PORT2_VECTOR
__interrupt void PORT2_ISR() {
	if (P2IFG & BIT0) {
		P2IFG &= ~BIT0;
		TACTL = 0;
	}
}
