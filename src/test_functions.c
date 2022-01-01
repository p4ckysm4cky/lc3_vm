#include <stdio.h>
#include <stdint.h>
#include "lc3.h"
#include "debug_tools.h"
#include "test_functions.h"


/* This file is only used for debugging purposes */

void test_sign_extend(uint16_t x, int bit_count)
{
    printf("Before: ");
    print_16bit(x);
    printf("After: ");
    uint16_t a = sign_extend(x, bit_count);
    print_16bit(a);
}


void test_update_flags(uint16_t reg[], uint16_t r, uint16_t num)
{
    const int R_COND = 9;
    printf("Num: %d\n", num);
    printf("Current Flag: ");
    print_16bit(reg[R_COND]);
    reg[r] = num;
    update_flags(r);
    printf("Updated Flag: ");
    print_16bit(reg[R_COND]);
}


void test_add(uint16_t reg[])
{
    const int R_COND = 9;
    // Register mode
    // DR = R_R0
    // SR1 = R_R3 = (int) 5
    reg[3] = 5;
    // SR2 = R_R4 = (int) 1000
    reg[4] = 1000;
    uint16_t instr = 0b0001000011000100;
    op_add(instr);
    // Expected value of 1005
    printf("Register mode, R_R0:\n");
    print_16bit(reg[0]);
    print_16bit(reg[R_COND]);

    // imm5 mode
    // DR = R_R1
    // SR1 = R_R5 = (int) 5
    reg[5] = 5;
    // imm5 = -8 = 0b11000
    instr = 0b0001001101111000;
    op_add(instr);
    printf("Register mode, R_R1:\n");
    // Expected value of -3
    print_16bit(reg[1]);
    print_16bit(reg[R_COND]);

}


void test_ldi(uint16_t reg[])
{
    // far_data
    mem_write(0x3456, 48);
    // pointer to far_data
    mem_write(0x3002, 0x3456);
    /*  DR = R_R6 = 110
        PC = 0x3000
        PCoffset9 = 2 = 0 0000 0010   
    */
    uint16_t instr = 0b1010110000000010;
    op_ldi(instr);
    print_16bit(reg[6]);
    printf("%d\n", reg[6]);
}


void test_ld(uint16_t reg[])
{
    // PC = 0x3000
    mem_write(0x30FF, 130);
    /*  DR = R_R4
        PCoffset = 255 = 0 1111 1111
    */
   uint16_t instr = 0b0010100011111111;
   op_ld(instr);
   printf("%d\n", reg[4]);
}


void test_and(uint16_t reg[])
{
    // AND R2, R3, R4
    reg[3] = ~0; // 10 0011
    reg[4] = ~0; //  1 0101
    uint16_t instr = 0b0101010011000100;
    op_and(instr);
    print_16bit(reg[3]);
    print_16bit(reg[4]);
    printf("&\n");
    print_16bit(reg[2]);
    printf("==========================\n");
    printf("imm5 test\n");
    // AND R2, R3, #7
    reg[3] = 14; // 1100
    instr = 0b0101010011101110;
    op_and(instr);
    print_16bit(reg[3]);
    print_16bit(14);
    printf("&\n");
    print_16bit(reg[2]);
}


void test_br(uint16_t reg[])
{
    int R_PC = 8;
    printf("PC: %x\n", reg[R_PC]);
    // increment 1 to R_R0
    uint16_t increment_instr = 0b0001000000100001;
    op_add(increment_instr);
    // expect PC to be at 0x3024
    uint16_t instr = 0b0000001000100100;
    op_br(instr);
    printf("PC: %x\n", reg[R_PC]);
    instr = 0b0000100000100100;
    op_br(instr);
    printf("PC: %x\n", reg[R_PC]);
}