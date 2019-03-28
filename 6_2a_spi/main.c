/**
 * @author 	Robert Fromm
 * @date	März 2019
 * @brief	Beispielprogramm für die Vorlesung Mikrorechnerarchitektur
 * 			Fakultät EIT, HTWK Leipzig
 *
 * Aus Kapitel:
 * 	6.2 SPI
 *
 * Benötigte Hardware:
 *  - MAX7219 mit LED-Matrix an SPI-Schnittstelle
 *    - Vcc   sw   3,3 V
 *    - GND   wß   GND
 *    - DIN   gr   P3.1
 *    - CS    vl   P1.0
 *    - CLK   bl   P3.3
 *
 * Funktion:
 *  - Demonstartion der SPI-Schnittstelle
 *  - Initialisierung des MAX7219 über SPI
 *  - Ausgeben von "Hi!"-Text auf der LED-Matrix
 */

#include <msp430.h>
#include <stdint.h>

void max7221_send(uint16_t command);

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;

	P1DIR |= BIT0;	// CS-Pin als Ausgang, High
	P1OUT |= BIT0;

	P3SEL |= BIT1 + BIT2 + BIT3;	// MOSI, MISO, CLK-Pins

	UCB0CTL1 |= UCSWRST;	// Soft-Reset des SPI-Moduls
	UCB0CTL0 = UCCKPH + UCMSB + UCMST + UCSYNC;	// Einstellungen: Clk-Phase, MSB-First, SPI-Master, Synchrone-Übertragung
	UCB0BR0 = 1;	// kein Teiler -> 1 MHz Clk
	UCB0BR1 = 0;

	UCB0CTL1 = UCSSEL_2;

	__enable_interrupt();

	max7221_send(0x0900); // Decode Mode = None
	max7221_send(0x0A0F); // Intensity = Full
	max7221_send(0x0B07); // Scan Limit = 8 Zeilen
	max7221_send(0x0C01); // Enable = 1
	max7221_send(0x0f00); // Test = 0

	// Muster ausgeben
	max7221_send(0x017d);
	max7221_send(0x0200);
	max7221_send(0x032f);
	max7221_send(0x0400);
	max7221_send(0x057f);
	max7221_send(0x0608);
	max7221_send(0x0708);
	max7221_send(0x087f);

	while(1) {
		__low_power_mode_4();
	}

}

void max7221_send(uint16_t command) {
	P1OUT &= ~BIT0;	// CS low

	UCB0TXBUF = command >> 8;	// MSByte senden
	while (!(IFG2 & UCB0RXIFG));

	UCB0TXBUF = command & 0xff;	// LSByte senden
	while (!(IFG2 & UCB0RXIFG));

	P1OUT |= BIT0; // CS high
}
