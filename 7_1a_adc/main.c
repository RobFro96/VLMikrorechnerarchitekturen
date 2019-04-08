/**
 * @author 	Robert Fromm
 * @date	März 2019
 * @brief	Beispielprogramm für die Vorlesung Mikrorechnerarchitektur
 * 			Fakultät EIT, HTWK Leipzig
 *
 * Aus Kapitel:
 * 	7. Analog-Digital-Umsetzer
 *
 * Benötigte Hardware:
 *	- 8 LEDs an P1.0 bis P1.7
 *	- Potentiometer an P3.7
 *
 * Funktion:
 *  - Demonstration des ADC
 *  - Pegelanzeige der LEDs entsprechend der Potentiometerposition
 */

#include <msp430.h>
#include <stdint.h>

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;

	P1DIR = 0xff;
	P1OUT = 0;

	ADC10CTL0 = ADC10ON + ADC10IE;
	ADC10CTL1 = INCH_7;
	ADC10AE0 |= BIT7;

	__enable_interrupt();

	while (1) {
		ADC10CTL0 |= ENC + ADC10SC;
		__low_power_mode_0();

		// Pegelanzeige
		for (uint8_t i = 0; i<8; i++) {
			if (ADC10MEM > i * 128) {
				P1OUT |= (1 << i);
			} else {
				P1OUT &= ~(1 << i);
			}
		}
	}
}

#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR() {
	__low_power_mode_off_on_exit();
}
