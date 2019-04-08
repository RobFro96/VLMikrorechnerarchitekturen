#ifndef PATTERNS_H_
#define PATTERNS_H_

typedef struct {
	uint8_t output;
	uint16_t delay;
} pattern_t;

extern const pattern_t patterns[];
extern const uint8_t patterns_length;

void patterns_init();
void patterns_show();

#endif /* PATTERNS_H_ */
