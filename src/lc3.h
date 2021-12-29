#ifndef LC3_H
#define LC3_h

#include <stdint.h>

uint16_t sign_extend(uint16_t x, int bit_count);
void update_flags(uint16_t r);

#endif