#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include "debug_tools.h"
#include "test_functions.h"


// Memory 0 -> 65535 = 65536 locations
uint16_t memory[UINT16_MAX];

// Register constants | Anonymous enum is used here
enum
{ 
    R_R0 = 0,
    R_R1,
    R_R2,
    R_R3,
    R_R4,
    R_R5,
    R_R6,
    R_R7,
    R_PC,     // Program counter
    R_COND, 
    R_COUNT
};

// Registers
uint16_t reg[R_COUNT];

// Opcode constants
enum
{
    OP_BR = 0, /* branch */
    OP_ADD,    /* add  */
    OP_LD,     /* load */
    OP_ST,     /* store */
    OP_JSR,    /* jump register */
    OP_AND,    /* bitwise and */
    OP_LDR,    /* load register */
    OP_STR,    /* store register */
    OP_RTI,    /* unused */
    OP_NOT,    /* bitwise not */
    OP_LDI,    /* load indirect */
    OP_STI,    /* store indirect */
    OP_JMP,    /* jump */
    OP_RES,    /* reserved (unused) */
    OP_LEA,    /* load effective address */
    OP_TRAP    /* execute trap */
};

// Condition Flags
enum
{
    FL_POS = 1 << 0, // Positive
    FL_ZRO = 1 << 1, // Zero
    FL_NEG = 1 << 2, // Negative
};


uint16_t sign_extend(uint16_t x, int bit_count)
{
    // Check if num is negative by checking
    // if MSB is set
    if (x >> (bit_count - 1) & 1) {
        // apply a bitmask of leading 1's
        x |= (~0 << bit_count);
    }
    return x;
}


int main(int argc, char* const argv[])
{
    // Set PC to starting positon of 
    // 0x3000
    uint16_t const PC_START = 0x3000;
    reg[R_PC] = PC_START;
    test_sign_extend(0b01111, 5);
}