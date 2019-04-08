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
#include "lcd.h"

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	lcd_init();

	lcd_gotoxy(0, 0);
	lcd_write("Hallo Welt!");

	char c = 0;
	while (1) {
		lcd_gotoxy(0, 1);
		lcd_put_char(c);
		c++;
		__delay_cycles(500000);
	}
}
