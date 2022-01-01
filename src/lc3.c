#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include "lc3.h"
#include <signal.h> // SIGINT
/* windows only */
#include <Windows.h>
#include <conio.h>  // _kbhit
/* for debugging */
#include "debug_tools.h"
#include "test_functions.h"


HANDLE hStdin = INVALID_HANDLE_VALUE;


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

// Memory Mapped Registers
enum
{
    // KBSR indicates whether a key has been pressed
    MR_KBSR = 0xFE00, // Memory address of keyboard status
    // KBDR identifies which key was pressed
    MR_KBDR = 0xFE02 //  Memory address of keyboard data
};

/* Extends a value less than 16 bit to be 
correctly represented in a signed 16 bit format */
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

/* Sets condition codes, based on whether the
16 bit 2's complement integer is ZERO, POSITIVE, or
NEGATIVE */
void update_flags(uint16_t r)
{
    if (reg[r] == 0)
        reg[R_COND] = FL_ZRO;
    else if (reg[r] >> 15) // If MSB is set (negative in 2's complement)
        reg[R_COND] = FL_NEG;
    else
        reg[R_COND] = FL_POS;
}


/* Our setter function to write to memory */
void mem_write(uint16_t address, uint16_t val)
{
    memory[address] = val;
}


/* Our getter function to read from memory */
uint16_t mem_read(uint16_t address)
{
    /* "If address we're reading is the keyboard status register, 
    we'll enter this 'keyboard handling mode' where we'll write the status
    and the keyboard data to the special registers"
    */
    if (address == MR_KBSR) {
        // Check if received new character from input
        if (check_key()) {
            // set Bit[15] when input received a new character
            memory[MR_KBSR] = (1 << 15);
            // sets KBDR to the latest character inputted
            memory[MR_KBDR] = getchar(); 
        }
        else {
            // indicates no new character was received
            memory[MR_KBSR] = 0;
        }
    }
    return memory[address];
}

/* Determines if the console received a new char */
uint16_t check_key()
{
    return WaitForSingleObject(hStdin, 1000) == WAIT_OBJECT_0 && _kbhit();
}


void op_add(uint16_t instr)
{
    // Destination register
    uint16_t dr = (instr >> 9) & 0x7; // mask of 0111
    // Source register
    uint16_t sr1 = (instr >> 6) & 0x7;
    // Determine if in immediate mode 
    // by checking the 5th bit
    uint16_t imm_flag = (instr >> 5) & 1;

    // immediate mode
    if (imm_flag) {
        uint16_t imm5 = sign_extend(instr & 0x1F, 5);
        reg[dr] = reg[sr1] + imm5;
    }
    else {
        uint16_t sr2 = instr & 0x7;
        reg[dr] = reg[sr1] + reg[sr2];
    }
    // Update R_COND after op_add
    update_flags(dr);
}


void op_ld(uint16_t instr)
{
    // Destination register
    uint16_t dr = (instr >> 9) & 0x7;
    uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);
    reg[dr] = mem_read(reg[R_PC] + pc_offset);
    update_flags(dr);
}


void op_ldi(uint16_t instr)
{
    // Destination register
    uint16_t dr = (instr >> 9) & 0x7;
    // Extend PCoffset9 to 16bit
    uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);
    // Get final address from adding PCoffset9 to PC
    // and accessing the memory address stored at that location
    uint16_t final_mem = mem_read(reg[R_PC] + pc_offset);
    reg[dr] = mem_read(final_mem);
    update_flags(dr);
}


int main(int argc, char* const argv[])
{
    // Set PC to starting positon of 
    // 0x3000
    uint16_t const PC_START = 0x3000;
    reg[R_PC] = PC_START;
    test_ld(reg);
}