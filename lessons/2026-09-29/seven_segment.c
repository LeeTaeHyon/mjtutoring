/*
 * ATmega128 / common-cathode single digit 7-segment
 * PC0..PC6 -> current limiting resistor -> a,b,c,d,e,f,g
 * COM cathode -> GND. DP unused. No physical board required to simulate.
 * For common-anode, connect COM to VCC and set COMMON_ANODE to 1.
 */
#ifndef F_CPU
#define F_CPU 1000000UL
#endif
#include <avr/io.h>
#include <util/delay.h>

#define COMMON_ANODE 0
#define SEG_MASK 0x7FU

/* bit 0=a, 1=b, ..., 6=g; logic 1 lights a common-cathode segment */
static const uint8_t digits[10] = {
    0x3F, 0x06, 0x5B, 0x4F, 0x66,
    0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

static void display_digit(uint8_t digit)
{
    uint8_t pattern = digits[digit];
#if COMMON_ANODE
    pattern = (uint8_t)(~pattern) & SEG_MASK;
#endif
    PORTC = (PORTC & (uint8_t)~SEG_MASK) | pattern;
}

int main(void)
{
    uint8_t digit;
    DDRC |= SEG_MASK;
    for (;;) {
        for (digit = 0; digit < 10; ++digit) {
            display_digit(digit);
            _delay_ms(1000);
        }
    }
}
