#ifndef TEST_FUNCTION_H
#define TEST_FUNCTION_H

void test_sign_extend(uint16_t x, int bit_count);
void test_update_flags(uint16_t reg[], uint16_t r, uint16_t num);
void test_add(uint16_t reg[]);
void test_ldi(uint16_t reg[]);
void test_ld(uint16_t reg[]);

#endif