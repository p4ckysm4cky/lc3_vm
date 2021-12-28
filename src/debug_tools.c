#include <stdio.h>
#include <stdint.h>
#include "debug_tools.h"

/* This file is only used for debugging purposes */

int get_nth_bit(int num, int n) 
{
    // create bit_mask for nth bit
    int nth_bit_mask = 1 << n;
    return (num & nth_bit_mask) != 0;
}


void print_16bit(uint16_t value)
{
    const int uint16_size = sizeof(uint16_t) * 8;
    for (int i = uint16_size - 1; i > -1; i--) {
        printf("%d", get_nth_bit(value, i));
        if (i % 4 == 0)
            putchar(' ');
    }
    putchar('\n');
}