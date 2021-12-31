#ifndef LC3_H
#define LC3_h

#include <stdint.h>

uint16_t sign_extend(uint16_t x, int bit_count);
void update_flags(uint16_t r);
void op_add(uint16_t instr);
void mem_write(uint16_t address, uint16_t val);
uint16_t mem_read(uint16_t address);
uint16_t check_key();
void op_ldi(uint16_t instr);

#endif