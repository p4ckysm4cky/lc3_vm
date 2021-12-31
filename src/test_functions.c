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
        PCoffset9 = 0x002 = 0 0000 0010   
    */
    uint16_t instr = 0b1010110000000010;
    op_ldi(instr);
    print_16bit(reg[6]);
    printf("%d\n", reg[6]);
}