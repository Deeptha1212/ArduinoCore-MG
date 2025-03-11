#include "Arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * SystemCoreClock: Define system clock speed (modify based on your board)
 */
uint32_t SystemCoreClock = 1000000ul; // Set to actual RISC-V core clock

/*
 * RISC-V-specific init function
 */
void init(void) {
    // Set up system clock (modify based on your RISC-V board)
    SystemCoreClock = 1000000ul; // Example: Modify based on actual clock speed

    // Configure GPIO as inputs by default
    for (uint32_t ul = 0; ul < NUM_DIGITAL_PINS; ul++) {
        // pinMode(ul, INPUT);
    }
}

/*
 * RISC-V Machine Timer-Based Delay
 */
#define MTIME        (*((volatile uint64_t*)0x0200BFF8))   // Machine Timer Register
#define MTIMECMP     (*((volatile uint64_t*)0x02004000))   // Timer Compare Register

void delay(uint32_t ms) {
    uint64_t start_time = MTIME;
    uint64_t ticks = ms * (SystemCoreClock / 1000); // Convert ms to clock ticks

    while ((MTIME - start_time) < ticks); // Wait until the time has elapsed
}

#ifdef __cplusplus
}
#endif
