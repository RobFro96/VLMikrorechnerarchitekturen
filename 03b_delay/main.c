#include <msp430.h>
#include <stdint.h>

// Prototypen
void delay(uint16_t duration);

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P1DIR = 0xFF;	// Alle Pin als Ausgänge
	P1OUT = 0x00;   // Alle Ausgänge auf Low

	while (1) {
		P1OUT |= BIT0;	// set P1.0
		P1OUT &= ~BIT1;	// clear P1.1

		delay(30000);

		P1OUT &= ~BIT0;	// clear P1.0
		P1OUT |= BIT1;	// set P1.1

		delay(30000);
	}
}

void delay(uint16_t duration) {
	volatile uint16_t i = duration;
	while (i > 0) {
		i--;
	}
}
