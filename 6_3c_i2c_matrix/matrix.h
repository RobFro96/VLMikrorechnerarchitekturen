#ifndef MATRIX_H_
#define MATRIX_H_

#define MATRIX_UPDATE_INTERVAL 64

void matrix_init();
void matrix_mcp_write(uint8_t reg, uint8_t data);
void matrix_write_row(uint8_t row, uint8_t data);
void matrix_update();

#endif /* MATRIX_H_ */
