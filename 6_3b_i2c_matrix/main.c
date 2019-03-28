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
 *  - Schachbrettmuster wird durch Multiplexing angezeigt
 */

#include <msp430.h>
#include <stdint.h>

static const uint8_t MCP_ADDRESS = 0x20;	// 7-bit Adresse des MCP23008

char i2c_data[2];	// Datenpuffer
volatile uint8_t i2c_counter; // Index der Daten

void matrix_mcp_write(uint8_t reg, uint8_t data);

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;

	P3SEL |= BIT1 + BIT2;	// I2C-Pins

	UCB0CTL1 |= UCSWRST;				// Soft-Reset des I2C-Moduls
	UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;	// Master, I2C, Synchron
	UCB0BR0 = 2;	// Teiler: 1 MHz /2 = 500 kHz
	UCB0BR1 = 0;

	UCB0CTL1 = UCSSEL_2;
	IE2 |= UCB0TXIE;

	__enable_interrupt();

	matrix_mcp_write(0, 0);		// Alle Pins des MCP23008 als Ausgang

	while (1) {
		matrix_mcp_write(0x09, 0xA1);	// Spalte X=0
		__delay_cycles(1000L);
		matrix_mcp_write(0x09, 0x52);	// Spalte X=1
		__delay_cycles(1000L);
		matrix_mcp_write(0x09, 0xA4);	// Spalte X=2
		__delay_cycles(1000L);
		matrix_mcp_write(0x09, 0x58);	// Spalte X=3
		__delay_cycles(1000L);
	}

}

void matrix_mcp_write(uint8_t reg, uint8_t data) {
	// Warten, bis Modul frei
	while (UCB0STAT & UCBBUSY)
		;

	// Puffer füllen
	i2c_data[0] = reg;
	i2c_data[1] = data;
	i2c_counter = 0;

	UCB0I2CSA = MCP_ADDRESS; // Slave Adresse setzen
	UCB0CTL1 |= UCTR;		 // W-Mode
	UCB0CTL1 |= UCTXSTT;     // Transmition Start

}

#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void) {
	if (i2c_counter < 2) {
		// Nächtes Byte senden
		UCB0TXBUF = i2c_data[i2c_counter];
		i2c_counter++;
	} else {
		// Alles Bytes versendet
		UCB0CTL1 |= UCTXSTP;	// Stop-Senden
		IFG2 &= ~UCB0TXIFG;
	}
}
