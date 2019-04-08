/**
 * @author 	Robert Fromm
 * @date	März 2019
 * @brief	Beispielprogramm für die Vorlesung Mikrorechnerarchitektur
 * 			Fakultät EIT, HTWK Leipzig
 *
 * Aus Kapitel:
 * 	6.1 UART / RS-232
 *
 * Benötigte Hardware:
 *  - 8 LEDs an P1.0 bis P1.7
 * 	- Taster an P2.0, P2.1, P2.2, P2.5
 * 	- UART-USB-Wandler an P3.4, P3.5
 *
 * Funktion:
 *  - Initialisierung der UART-Schnittstelle mit 9600 Baud
 *  - Wenn Taster gedrückzt wird, werden ASCII-Zeichen '0' bis '3' versendet
 *  - Wenn ein Zeichen empfangen wird, wird Byte-Wert an P1OUT ausgegeben
 */

#include <msp430.h>
#include <stdint.h>

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	BCSCTL1 = CALBC1_1MHZ;	// DC0 kalibrieren auf 1 MHz
	DCOCTL = CALDCO_1MHZ;

	P1DIR = 0xff;	// Alle LEDs auf Ausgang
	P1OUT = 0;

	P2IES |= BIT0 + BIT1 + BIT2 + BIT5;		// Interrupt für Buttons aktivieren
	P2IFG &= ~(BIT0 + BIT1 + BIT2 + BIT5);
	P2IE |= BIT0 + BIT1 + BIT2 + BIT5;

	P3SEL |= BIT4 + BIT5;	// UART Pins

	UCA0CTL1 |= UCSWRST;	// UART Soft-Reset
	UCA0CTL0 = 0;			// Einstellungen
	UCA0CTL1 |= UCSSEL_2;	// SMCLK = 1 MHz

	UCA0BR0 = 6;	// Einstellungen für 9600 Baud
	UCA0BR1 = 0;
	UCA0MCTL = (8 << 4) + UCOS16;

	UCA0CTL1 &= ~UCSWRST;	// Soft-Reset loslassen
	UC0IE |= UCA0RXIE;		// Interrupt-Enable beim Empfangen

	__enable_interrupt();

	while (1) {
		__low_power_mode_4();
	}
}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void) {
	if (IFG2 & UCA0RXIFG) {
		IFG2 &= ~UCA0RXIFG;
		P1OUT = UCA0RXBUF;	// Empfangenes Byte auf P1OUT ausgeben
	}
}

#pragma vector=PORT2_VECTOR
__interrupt void PORT2_ISR() {
	if (P2IFG & BIT0) {
		P2IFG &= ~BIT0;
		UCA0TXBUF = '0';	// Senden des ASCII-Zeichens beim Tastendruck
	}
	if (P2IFG & BIT1) {
		P2IFG &= ~BIT1;
		UCA0TXBUF = '1';
	}
	if (P2IFG & BIT2) {
		P2IFG &= ~BIT2;
		UCA0TXBUF = '2';
	}
	if (P2IFG & BIT5) {
		P2IFG &= ~BIT5;
		UCA0TXBUF = '3';
	}
}
