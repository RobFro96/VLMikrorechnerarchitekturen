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
