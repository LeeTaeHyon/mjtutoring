/*
 * ATmega128 / Microchip Studio (Atmel Studio 7) / GCC C Executable
 * PA0..2 = red, yellow, green. PC0..2 = corresponding second set.
 * Default: active-high, LED anode <- resistor <- pin, cathode -> GND.
 * F_CPU must match the simulator/project clock (here 1 MHz).
 */
#ifndef F_CPU
#define F_CPU 1000000UL
#endif
#include <avr/io.h>
#include <util/delay.h>

#define RED    (1U << PA0)
#define YELLOW (1U << PA1)
#define GREEN  (1U << PA2)
#define LIGHT_MASK (RED | YELLOW | GREEN)

static void show_lights(uint8_t state)
{
    /* Clear only the three controlled bits; preserve all other PORT bits. */
    PORTA = (PORTA & (uint8_t)~LIGHT_MASK) | state;
    PORTC = (PORTC & (uint8_t)~LIGHT_MASK) | state;
}

int main(void)
{
    DDRA |= LIGHT_MASK;
    DDRC |= LIGHT_MASK;
    show_lights(RED);
    for (;;) {
        show_lights(RED);
        _delay_ms(1000);
        show_lights(GREEN);
        _delay_ms(1000);
        show_lights(YELLOW);
        _delay_ms(500);
    }
}
