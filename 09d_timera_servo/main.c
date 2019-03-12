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
