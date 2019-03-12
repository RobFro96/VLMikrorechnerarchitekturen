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
	CCTL1 = OUTMOD_6;
	CCR2 = 0;
	CCTL2 = OUTMOD_6;
	TACTL = TASSEL_1 + MC_3 + TACLR;

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
