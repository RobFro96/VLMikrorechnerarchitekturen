// Benötige Bibliotheken
#include <msp430.h>
#include <stdint.h>

// Eigenen Header-Datei
#include "patterns.h"

// Globale Variablen
extern const uint8_t patterns[] = { 0x81, 0x42, 0x24, 0x18, 0x3c, 0x66, 0xc3 };
extern const uint8_t patterns_length = 7;

// Lokale Variablen
static const uint8_t *pattern_pointer;

// Prototypen lokaler Funktionen
static void set_output(uint8_t pattern);

// Globale Funktionen

void patterns_init() {
	P1DIR = 0xFF;	// Alle Pin als Ausgänge
	P1OUT = 0x00;   // Alle Ausgänge auf Low

	pattern_pointer = patterns;
}

void patterns_show() {
	set_output(*pattern_pointer);

	pattern_pointer++;
	if (pattern_pointer >= patterns + patterns_length) {
		pattern_pointer = patterns;
	}

	__delay_cycles(200000);
}

// Lokale Funktionen

static void set_output(uint8_t pattern) {
	P1OUT = pattern;
}
