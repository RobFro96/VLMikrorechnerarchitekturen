#include <msp430.h>
#include <stdint.h>

#include "patterns.h"

// Globale Variablen
extern const pattern_t patterns[] = { { 0x81, PATTERNS_DELAY_NORMAL }, { 0x42,
		PATTERNS_DELAY_NORMAL }, { 0x24, PATTERNS_DELAY_NORMAL }, { 0x18,
		PATTERNS_DELAY_SLOW }, { 0x3c, PATTERNS_DELAY_FAST }, { 0x66,
		PATTERNS_DELAY_FAST }, { 0xc3, PATTERNS_DELAY_FAST } };
extern const uint8_t patterns_length = 7;

// Lokale Variablen
static const pattern_t *pattern_pointer;

// Prototypen
static void set_output(uint8_t pattern);
static void delay(pattern_delay_t duration);

void patterns_init() {
	P1DIR = 0xFF;	// Alle Pin als Ausgänge
	P1OUT = 0x00;   // Alle Ausgänge auf Low

	pattern_pointer = patterns;
}

void patterns_show() {
	set_output(pattern_pointer->output);

	delay(pattern_pointer->delay);

	pattern_pointer++;
	if (pattern_pointer >= patterns + patterns_length) {
		pattern_pointer = patterns;
	}
}

static void set_output(uint8_t pattern) {
	P1OUT = pattern;
}

static void delay(pattern_delay_t duration) {
	switch (duration) {
	case PATTERNS_DELAY_NORMAL:
		__delay_cycles(200000);
		break;
	case PATTERNS_DELAY_SLOW:
		__delay_cycles(400000);
		break;
	case PATTERNS_DELAY_FAST:
		__delay_cycles(100000);
		break;
	default:
		break;
	}
}
