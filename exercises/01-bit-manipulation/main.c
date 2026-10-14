#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/* Bit positions are 0..7; bit 0 is the least significant bit.
 * Invalid positions: return the original value, or false for read_bit.
 * TODO: replace these safe placeholders using |, &, ~, ^ and <<.
 */
static uint8_t set_bit(uint8_t value, unsigned bit)
{
    (void)bit;
    return value;
}

static uint8_t clear_bit(uint8_t value, unsigned bit)
{
    (void)bit;
    return value;
}

static uint8_t toggle_bit(uint8_t value, unsigned bit)
{
    (void)bit;
    return value;
}

static bool read_bit(uint8_t value, unsigned bit)
{
    (void)value;
    (void)bit;
    return false;
}

/* Provided: display bits from most significant to least significant. */
static void print_register(const char *label, uint8_t value)
{
    printf("%s: ", label);
    for (int bit = 7; bit >= 0; --bit) {
        putchar(((unsigned)value >> bit) & 1u ? '1' : '0');
    }
    printf(" (0x%02X)\n", (unsigned)value);
}

int main(void)
{
    /* Simulated register: bit 0 = LED, bit 2 = motor, bit 7 = alarm.
     * This is ordinary RAM, not a real hardware register.
     */
    uint8_t status = 0u;
    print_register("Initial", status);
    status = set_bit(status, 0u);
    print_register("LED on", status);
    status = set_bit(status, 2u);
    print_register("Motor on", status);
    status = toggle_bit(status, 7u);
    print_register("Alarm toggled", status);
    status = clear_bit(status, 0u);
    print_register("LED off", status);
    printf("Motor bit: %u\n", (unsigned)read_bit(status, 2u));
    printf("LED bit: %u\n", (unsigned)read_bit(status, 0u));
    return 0;
}
