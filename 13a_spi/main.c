/*
 * Pinbelegung:
 *
 * Vcc   sw   3,3 V
 * GND   wﬂ   GND
 * DIN   gr   P3.1
 * CS    vl   P1.0
 * CLK   bl   P3.3
 */


#include <msp430.h>
#include <stdint.h>

void max7221_send(uint16_t command);

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;

	P1DIR |= BIT0;
	P1OUT |= BIT0;
	P3SEL |= BIT1 + BIT2 + BIT3;

	UCB0CTL1 |= UCSWRST;
	UCB0CTL0 = UCCKPH + UCMSB + UCMST + UCSYNC;
	UCB0BR0 = 1;
	UCB0BR1 = 0;

	UCB0CTL1 = UCSSEL_2;

	__enable_interrupt();

	max7221_send(0x0900); // Decode Mode = None
	max7221_send(0x0A0F); // Intensity = Full
	max7221_send(0x0B07); // Scan Limit = 8 Zeilen
	max7221_send(0x0C01); // Enable = 1
	max7221_send(0x0f00); // Test = 0

	// Muster ausgeben
	max7221_send(0x0100);
	max7221_send(0x022f);
	max7221_send(0x0300);
	max7221_send(0x047f);
	max7221_send(0x0508);
	max7221_send(0x0608);
	max7221_send(0x0708);
	max7221_send(0x087f);

	while(1) {
		__low_power_mode_3();
	}

}

void max7221_send(uint16_t command) {
	P1OUT &= ~BIT0;

	UCB0TXBUF = command >> 8;
	while (!(IFG2 & UCB0RXIFG));

	UCB0TXBUF = command & 0xff;
	while (!(IFG2 & UCB0RXIFG));

	P1OUT |= BIT0;
}
