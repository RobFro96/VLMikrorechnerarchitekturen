#include <msp430.h>
#include <stdint.h>
#include "patterns.h"

// Hauptprogramm
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	patterns_init();

	while (1) {
		patterns_show();
	}
}
