#ifndef TEST_FUNCTION_H
#define TEST_FUNCTION_H

void test_sign_extend(uint16_t x, int bit_count);
void test_update_flags(uint16_t reg[], uint16_t r, uint16_t num);
void test_add(uint16_t reg[]);
void test_ldi(uint16_t reg[]);
void test_ld(uint16_t reg[]);
void test_and(uint16_t reg[]);
void test_br(uint16_t reg[]);
void test_jmp(uint16_t reg[]);
void test_jsr(uint16_t reg[]);
void test_ldr(uint16_t reg[]);
void test_lea(uint16_t reg[]);
void test_not(uint16_t reg[]);
void test_ret(uint16_t reg[]);
void test_st(uint16_t reg[]);

#endif