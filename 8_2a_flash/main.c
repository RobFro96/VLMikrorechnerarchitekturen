/**
 * @author 	Robert Fromm
 * @date	März 2019
 * @brief	Beispielprogramm für die Vorlesung Mikrorechnerarchitektur
 * 			Fakultät EIT, HTWK Leipzig
 *
 * Aus Kapitel:
 * 	‌8.   Flash-Speicher
 *
 * Benötigte Hardware:
 *	- 8 LEDs an P1.0 bis P1.7
 *	- Taster an P2.0
 *
 * Funktion:
 *  - Demonstration eines kapazitiven Touchsensor ohne Capacitive-Sensing-Modul
 *  - LED an P1.0 wird angeschaltet, wenn eine Berührung detektiert wurde
 */

#include <msp430.h>
#include <stdint.h>

void flash_init();
void flash_erase(uint8_t *address);
void flash_write(uint8_t *address, uint8_t value);

static uint8_t *data_pointer = (uint8_t *) 0x1000;

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;

	P1DIR = 0xff;
	P1OUT = *data_pointer;

	P2IES |= BIT0;
	P2IFG &= ~BIT0;
	P2IE |= BIT0;

	flash_init();

	__enable_interrupt();

	while (1) {
		__low_power_mode_3();

		uint8_t new_value = *data_pointer + 1;
		flash_erase(data_pointer);
		flash_write(data_pointer, new_value);
		P1OUT = *data_pointer;
	}
}

void flash_init() {
	FCTL2 = FWKEY + FSSEL_1 + FN1;	// SMCLK / 3 -> 333 kHz
}

void flash_erase(uint8_t *address) {
	FCTL3 = FWKEY;           // Clear Lock bit
	FCTL1 = FWKEY + ERASE;   // Set Erase bit
	*address = 0;			 // Dummy write
	FCTL1 = FWKEY;           // Clear Erase bit
	FCTL3 = FWKEY + LOCK;    // Set LOCK bit
}

void flash_write(uint8_t *address, uint8_t value) {
	FCTL3 = FWKEY;  		// Clear Lock bit
	FCTL1 = FWKEY + WRT;	// Set WRT bit for write operation
	*address = value;		// Write
	FCTL1 = FWKEY;          // Clear WRT bit
	FCTL3 = FWKEY + LOCK; 	// Set LOCK bit
}

#pragma vector=PORT2_VECTOR
__interrupt void PORT2_ISR() {
	if (P2IFG & BIT0) {
		P2IFG &= ~BIT0;
		__low_power_mode_off_on_exit();
	}
}
