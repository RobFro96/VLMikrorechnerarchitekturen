/**
 * @author 	Robert Fromm
 * @date	M�rz 2019
 * @brief	Beispielprogramm f�r die Vorlesung Mikrorechnerarchitektur
 * 			Fakult�t EIT, HTWK Leipzig
 *
 * Aus Kapitel:
 * 	3.4 Interrupts der parallelen Schnittstelle
 *
 * Ben�tigte Hardware:
 * 	- 8 LEDs an P1.0 bis P1.7
 * 	- Taster an P2.0
 *
 * Funktion:
 *  - Demonstration von Interrupts
 * 	- Beim Dr�cken des Tasters an P2.0 wird Register P1OUT hochgez�hlt
 * 	- Wert des Z�hlers in Bin�r an den LEDs ablesbar
 */

#include <msp430.h>
#include <stdint.h>

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P1DIR = 0xFF;
	P1OUT = 0x00;

	P2IES |= BIT0;
	P2IFG &= ~BIT0;
	P2IE |= BIT0;

	__enable_interrupt();

	while (1) {
		__low_power_mode_4();
		P1OUT++;
	}
}

#pragma vector=PORT2_VECTOR
__interrupt void PORT2_ISR() {
	if (P2IFG & BIT0) {
		P2IFG &= ~BIT0;
		__low_power_mode_off_on_exit();
	}
}
