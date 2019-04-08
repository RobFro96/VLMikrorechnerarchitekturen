/**
 * @author 	Robert Fromm
 * @date	März 2019
 * @brief	Beispielprogramm für die Vorlesung Mikrorechnerarchitektur
 * 			Fakultät EIT, HTWK Leipzig
 *
 * Aus Kapitel:
 * 	6.3 I2C
 *
 * Benötigte Hardware:
 *	- MCP23008 mit 4x4-LED-Matrix
 *	  - SCL an P3.2
 *	  - SDA an P3.1
 *
 * Funktion:
 *  - Ansteuern der LED-Matrix
 *  - Modul für LED-Matrix
 *  - Taktung der Matrix durch Timer
 */

#include <msp430.h>
#include <stdint.h>

#include "matrix.h"

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;

	// Timer A mit regelmäßigen CCR0-Interrupt
	CCR0 = MATRIX_UPDATE_INTERVAL;
	CCTL0 = CCIE;
	TACTL = TASSEL_1 + MC_2 + TACLR;

	__enable_interrupt();

	// Initialisierung der Matrix
	matrix_init();
	matrix_write_row(0, 0b0101);
	matrix_write_row(1, 0b1000);
	matrix_write_row(2, 0b1000);
	matrix_write_row(3, 0b0101);

	while (1) {
		matrix_update();
		__low_power_mode_3();
	}

}

#pragma vector=TIMERA0_VECTOR
__interrupt void TIMERA0_ISR() {
	CCR0 += MATRIX_UPDATE_INTERVAL;
	__low_power_mode_off_on_exit();
}
