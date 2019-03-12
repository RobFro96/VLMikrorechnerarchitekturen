#include <msp430.h>
#include <stdint.h>

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;

	P1DIR = 0xff;
	P1OUT = 0;

	P2IES |= BIT0 + BIT1 + BIT2 + BIT5;
	P2IFG &= ~(BIT0 + BIT1 + BIT2 + BIT5);
	P2IE |= BIT0 + BIT1 + BIT2 + BIT5;

	P3SEL |= BIT4 + BIT5;

	UCA0CTL1 |= UCSWRST;
	UCA0CTL0 = 0;
	UCA0CTL1 |= UCSSEL_2;

	UCA0BR0 = 6;
	UCA0BR1 = 0;
	UCA0MCTL = (8 << 4) + UCOS16;

	UCA0CTL1 &= ~UCSWRST;
	UC0IE |= UCA0RXIE;

	__enable_interrupt();

	while (1) {
		__low_power_mode_3();
	}
}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void) {
	if (IFG2 & UCA0RXIFG) {
		IFG2 &= ~UCA0RXIFG;
		P1OUT = UCA0RXBUF;
	}
}

#pragma vector=PORT2_VECTOR
__interrupt void PORT2_ISR() {
	if (P2IFG & BIT0) {
		P2IFG &= ~BIT0;
		UCA0TXBUF = '0';
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
