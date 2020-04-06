/**
 * @author 	Robert Fromm
 * @date	März 2019
 * @brief	Beispielprogramm für die Vorlesung Mikrorechnerarchitektur
 * 			Fakultät EIT, HTWK Leipzig
 *
 * Aus Kapitel:
 * 	7.5   Einführung in die digitale Signalverarbeitung
 *
 * Funktion:
 *  - Programm kann nicht ausgeführt werden!
 *  - Beispiel für die Implementierung eines digitalen Filters
 */

#include <msp430.h>
#include <stdint.h>

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

}


uint16_t u_speicher[4] = {0, 0, 0, 0};

uint16_t filter(uint16_t u) {
	u_speicher[3] = u_speicher[2];
	u_speicher[2] = u_speicher[1];
	u_speicher[1] = u_speicher[0];
	u_speicher[0] = u;

	uint16_t y = 0;
	y += 0.25 * u_speicher[0];
	y += 0.25 * u_speicher[1];
	y += 0.25 * u_speicher[2];
	y += 0.25 * u_speicher[3];

	return y;
}

uint16_t u_speicher[4] = {0, 0, 0, 0};

uint16_t filter2(uint16_t u, uint16_t k) {
	u_speicher[k & 0b11] = u;

	uint16_t y = 0;
	for (uint8_t i = 0; i<4; i++) {
		y += 0.25 * u_speicher[i];
	}
}

