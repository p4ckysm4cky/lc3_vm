#ifndef DEBUG_TOOLS
#define DEBUG_TOOLS

#include <stdint.h>

/* Gets the bit of num at n position */
int get_nth_bit(int num, int n);

/* outputs the uint16 value to console */
void print_16bit(uint16_t value);

#endif