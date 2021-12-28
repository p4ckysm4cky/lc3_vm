#include <stdio.h>
#include <stdint.h>
#include "lc3.h"
#include "debug_tools.h"

/* This file is only used for debugging purposes */

void test_sign_extend(uint16_t x, int bit_count)
{
    printf("Before: ");
    print_16bit(x);
    printf("After: ");
    uint16_t a = sign_extend(x, bit_count);
    print_16bit(a);
}