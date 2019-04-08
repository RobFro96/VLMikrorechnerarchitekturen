/**
 * @author 	Robert Fromm
 * @date	März 2019
 * @brief	Beispielprogramm für die Vorlesung Mikrorechnerarchitektur
 * 			Fakultät EIT, HTWK Leipzig
 *
 * Aus Kapitel:
 * 	3.2 Ansteuern des LCD-Moduls
 */

#include <msp430.h>
#include <stdint.h>

#include "lcd.h"

typedef enum {
	LCD_COMMAND, LCD_DATA
} lcd_command_t;

// Prototypen
static void send_8bit(uint8_t data, lcd_command_t type);
static void send_4bit(uint8_t data, lcd_command_t type);
static void pin_mode();
static void set_rs_by_type(lcd_command_t type);
static void set_en();
static void clear_en();
static void set_data_pins(uint8_t data);

/**
 * Initialsierung des LCDs
 */
void lcd_init() {
	// Datenflussrichtung der Pins setzen
	pin_mode();

	__delay_cycles(15000);
	send_8bit(0x3, LCD_COMMAND);	// Initialisierungsschlüssel
	__delay_cycles(41000);
	send_8bit(0x3, LCD_COMMAND);	// Initialisierungsschlüssel
	__delay_cycles(100);
	send_8bit(0x3, LCD_COMMAND);	// Initialisierungsschlüssel
	send_8bit(0x2, LCD_COMMAND);    // Function set: 4Bit

	send_4bit(0x28, LCD_COMMAND);	// Function set: 4bit, 2Line
	send_4bit(0x0C, LCD_COMMAND);	// Display on/off: on, keine Cursor
	send_4bit(0x06, LCD_COMMAND);// Entry mode set: Links nach rechts, überschreiben
	send_4bit(0x01, LCD_COMMAND);	// Clear Display

	__delay_cycles(40000);
}

/**
 * Bewegen des Cursors an die angegebene Position
 * @param x	Spalte (0 ... 15)
 * @param y	Zeile (0, 1)
 */
void lcd_gotoxy(uint8_t x, uint8_t y) {
	uint8_t address;

	if (y == 0) {
		address = 0x80;
	} else {
		address = 0xC0;
	}

	address += x;

	send_4bit(address, LCD_COMMAND);
}

/**
 * Ausgeben eines Ascii-Zeichens auf dem LCD
 * @param c	Zeichen
 */
void lcd_put_char(char c) {
	send_4bit(c, LCD_DATA);
}

/**
 * Ausgeben einer Zeichenkette auf dem LCD
 * @param str	Zeichenkette
 */
void lcd_write(const char *str) {
	while (*str != 0) {
		lcd_put_char(*str);
		str++;
	}
}

// Funktionen zur Datenübertragung

/**
 * Senden eines Bytes an das LCD mit Hilfe der 8-Bit-Kommunikation
 * @param data	Byte
 * @param type	Typ des Bytes (LCD_COMMAND, LCD_DATA)
 */
static void send_8bit(uint8_t data, lcd_command_t type) {
	__delay_cycles(40);

	set_rs_by_type(type);

	set_en();
	set_data_pins(data);
	clear_en();
}

/**
 * Senden eines Bytes an das LCD mit Hilfe der 4-Bit-Kommunikation
 * @param data	Byte
 * @param type	Typ des Bytes (LCD_COMMAND, LCD_DATA)
 */
static void send_4bit(uint8_t data, lcd_command_t type) {
	__delay_cycles(40);

	set_rs_by_type(type);

	set_en();
	set_data_pins(data >> 4);
	clear_en();

	set_en();
	set_data_pins(data);
	clear_en();
}

// Pin-Funktionen

/**
 * Setzen der Datenflussrichtung aller Pins der MSP430, die zur Steuerung des LCDs benötigt werden
 */
static void pin_mode() {
	// Datenpins als Ausgang
	P1DIR |= BIT0 + BIT1 + BIT2 + BIT3;
	P1OUT &= ~(BIT0 + BIT1 + BIT2 + BIT3);

	// RS + EN als Ausgang
	P3DIR |= BIT0 + BIT3;
	P3OUT &= ~(BIT0 + BIT3);
}

/**
 * Setzen des RS-Pins entsprechend des Befehlstyps
 * @param type	LCD_COMMAND -> RS = LOW
 * 				LCD_DATA 	-> RS = HIGH
 */
static void set_rs_by_type(lcd_command_t type) {
	if (type == LCD_COMMAND) {
		P3OUT &= ~ BIT0;
	} else {
		P3OUT |= BIT0;
	}
}

/**
 * Setzen des EN-Pins auf HIGH
 */
static void set_en() {
	P3OUT |= BIT3;
}

/**
 * Setzen des EN-Pins auf LOW
 */
static void clear_en() {
	P3OUT &= ~BIT3;
}

/**
 * Setzen der Datenpins entsprechend der angebenen 4 Bits
 * @param data Die 4 niederwertigsten Bits werden an den Pins angelegt.
 */
static void set_data_pins(uint8_t data) {
	P1OUT = (P1OUT & 0xf0) + (data & 0x0f);
}
