#ifndef PATTERNS_H_
#define PATTERNS_H_

typedef enum {
	PATTERNS_DELAY_NORMAL = 0, PATTERNS_DELAY_SLOW, PATTERNS_DELAY_FAST
} pattern_delay_t;

typedef struct {
	uint8_t output;
	pattern_delay_t delay;
} pattern_t;

extern const pattern_t patterns[];
extern const uint8_t patterns_length;

void patterns_init();
void patterns_show();

#endif /* PATTERNS_H_ */
