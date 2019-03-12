#include <msp430.h>
#include <stdint.h>

volatile uint16_t timer_start;

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P1DIR = 0xff;
	P1OUT = 0;

	P2SEL |= BIT2;

	CCR0 = 0;
	CCTL0 = CM_3 + CCIS_1 + SCS + CAP + CCIE;
	TACTL = TASSEL_1 + ID_3 + MC_2 + TACLR;


	__enable_interrupt();

	while (1) {
		__low_power_mode_3();
	}
}

#pragma vector=TIMERA0_VECTOR
__interrupt void TIMERA0_ISR() {
	if (CCTL0 & CCI) {
		// L -> H: Taster losgelassen
		uint16_t time = CCR0 - timer_start;
		P1OUT = time >> 8;
	} else {
		// H -> L: Taster gedrückt
		timer_start = CCR0;
	}
}
