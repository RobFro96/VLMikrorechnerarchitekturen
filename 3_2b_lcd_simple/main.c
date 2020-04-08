/**
 * @author 	Robert Fromm
 * @date	März 2019
 * @brief	Beispielprogramm für die Vorlesung Mikrorechnerarchitektur
 * 			Fakultät EIT, HTWK Leipzig
 *
 * Aus Kapitel:
 * 	3.2 Ansteuern des LCD-Moduls
 *
 * Benötigte Hardware:
 * 	- LCD des MSP430 Education Systems
 * 	  - DATA4 ... DATA7 an P1.0 ... P1.3
 * 	  - RS an P3.0
 * 	  - EN an P3.3
 *
 * Funktion:
 * 	- Initialisierung des LCD-Moduls
 * 	- Ausgeben der Zeichenkette "Hallo Welt!" in der ersten Zeile
 * 	- Ausgaben aller ASCII-Zeichen in der zweiten Zeile, umschalten nach 500 ms
 */

#include <msp430.h>
#include <stdint.h>

static void lcd_init();
static void send_8bit(uint8_t data, uint8_t rs);
static void send_4bit(uint8_t data, uint8_t rs);
static void set_rs_by_type(uint8_t rs);
static void lcd_gotoxy(uint8_t x, uint8_t y);

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	lcd_init();

	lcd_gotoxy(0, 0);
	send_4bit('H', 1);
	send_4bit('e', 1);
	send_4bit('l', 1);
	send_4bit('l', 1);
	send_4bit('o', 1);
	send_4bit('!', 1);

	char c = 0;
	while (1) {
		lcd_gotoxy(0, 1);
		send_4bit(c, 1);
		c++;
		__delay_cycles(500000);
	}
}

static void lcd_init() {
	// Datenpins als Ausgang
	P1DIR |= BIT0 + BIT1 + BIT2 + BIT3;
	P1OUT &= ~(BIT0 + BIT1 + BIT2 + BIT3);

	// RS + EN als Ausgang
	P3DIR |= BIT0 + BIT3;
	P3OUT &= ~(BIT0 + BIT3);

	__delay_cycles(15000);
	send_8bit(0x3, 0);	// Initialisierungsschlüssel
	__delay_cycles(41000);
	send_8bit(0x3, 0);	// Initialisierungsschlüssel
	__delay_cycles(100);
	send_8bit(0x3, 0);	// Initialisierungsschlüssel
	send_8bit(0x2, 0);    // Function set: 4Bit

	send_4bit(0x28, 0);	// Function set: 4bit, 2Line
	send_4bit(0x0C, 0);	// Display on/off: on, keine Cursor
	send_4bit(0x06, 0);	// Entry mode set: Links nach rechts, überschreiben
	send_4bit(0x01, 0);	// Clear Display

	__delay_cycles(40000);
}

static void send_8bit(uint8_t data, uint8_t rs) {
	__delay_cycles(40);

	set_rs_by_type(rs);

	P3OUT |= BIT3;
	P1OUT = data & 0x0f;
	P3OUT &= ~BIT3;
}

static void send_4bit(uint8_t data, uint8_t rs) {
	__delay_cycles(40);

	set_rs_by_type(rs);

	P3OUT |= BIT3;
	P1OUT = data >> 4;
	P3OUT &= ~BIT3;

	P3OUT |= BIT3;
	P1OUT = data & 0x0f;
	P3OUT &= ~BIT3;
}

static void set_rs_by_type(uint8_t rs) {
	if (rs) {
		P3OUT |= BIT0;
	} else {
		P3OUT &= ~BIT0;
	}
}

static void lcd_gotoxy(uint8_t x, uint8_t y) {
	uint8_t address;
	if (y == 0) {
		address = 0x80 + x;
	} else {
		address = 0xC0 + x;
	}
	send_4bit(address, 0);
}
