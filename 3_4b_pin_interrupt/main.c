/**
 * @author 	Robert Fromm
 * @date	März 2019
 * @brief	Beispielprogramm für die Vorlesung Mikrorechnerarchitektur
 * 			Fakultät EIT, HTWK Leipzig
 *
 * Aus Kapitel:
 * 	3.4 Interrupts der parallelen Schnittstelle
 *
 * Benötigte Hardware:
 * 	- 8 LEDs an P1.0 bis P1.7
 * 	- Taster an Port2
 * 	  - Taster 1: P2.0
 * 	  - Taster 2: P2.1
 * 	  - Taster 3: P2.2
 * 	  - Taster 4: P2.5
 *
 * Funktion:
 *  - Demonstration von Interrupts
 * 	- Verschiedenen Schaltern werden verschiedene Funktionen zugeordnet
 * 	  - Taster 1: Inkrementieren
  	  - Taster 2: Dekrementieren
  	  - Taster 3: Zurücksetzen auf 0
  	  - Taster 4: Setzen auf 0xAA
 */

#include <msp430.h>
#include <stdint.h>

static volatile uint8_t button_flag = 0;

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P1DIR = 0xFF;
	P1OUT = 0x00;

	P2IES |= BIT0 + BIT1 + BIT2 + BIT5;
	P2IFG &= ~(BIT0 + BIT1 + BIT2 + BIT5);
	P2IE |= BIT0 + BIT1 + BIT2 + BIT5;

	__enable_interrupt();

	while (1) {
		if (button_flag & BIT0) {
			P1OUT++;
			button_flag &= ~BIT0;
		} else if (button_flag & BIT1) {
			P1OUT--;
			button_flag &= ~BIT1;
		} else if (button_flag & BIT2) {
			P1OUT = 0;
			button_flag &= ~BIT2;
		} else if (button_flag & BIT3) {
			P1OUT = 0xAA;
			button_flag &= ~BIT3;
		} else {
			__low_power_mode_4();
		}

	}
}

#pragma vector=PORT2_VECTOR
__interrupt void PORT2_ISR() {
	if (P2IFG & BIT0) {
		P2IFG &= ~BIT0;
		button_flag |= BIT0;
		__low_power_mode_off_on_exit();
	}
	if (P2IFG & BIT1) {
		P2IFG &= ~BIT1;
		button_flag |= BIT1;
		__low_power_mode_off_on_exit();
	}
	if (P2IFG & BIT2) {
		P2IFG &= ~BIT2;
		button_flag |= BIT2;
		__low_power_mode_off_on_exit();
	}
	if (P2IFG & BIT5) {
		P2IFG &= ~BIT5;
		button_flag |= BIT3;
		__low_power_mode_off_on_exit();
	}
}
