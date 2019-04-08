#include <msp430.h>
#include <stdint.h>

#include "patterns.h"

// Globale Variablen
extern const pattern_t patterns[] = { { 0x81, 30000 }, { 0x42, 30000 }, { 0x24,
		30000 }, { 0x18, 60000 }, { 0x3c, 15000 }, { 0x66, 15000 }, { 0xc3,
		15000 } };
extern const uint8_t patterns_length = 7;

// Lokale Variablen
static const pattern_t *pattern_pointer;

// Prototypen
static void set_output(uint8_t pattern);

void patterns_init() {
	P1DIR = 0xFF;	// Alle Pin als Ausgänge
	P1OUT = 0x00;   // Alle Ausgänge auf Low

	pattern_pointer = patterns;
}

void patterns_show() {
	set_output(pattern_pointer->output);

	volatile uint16_t i = pattern_pointer->delay;
	while (i > 0) {
		i--;
	}

	pattern_pointer++;
	if (pattern_pointer >= patterns + patterns_length) {
		pattern_pointer = patterns;
	}
}

static void set_output(uint8_t pattern) {
	P1OUT = pattern;
}
