#ifndef WIRING_H
#define WIRING_H

#include "Arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * SystemCoreClock: Define system clock speed (modify based on your board)
 */
extern uint32_t SystemCoreClock;

/*
 * Initialization function for RISC-V
 */
void init(void);

/*
 * Delay function using RISC-V Machine Timer
 */
void delay(uint32_t ms);

#ifdef __cplusplus
}
#endif

#endif // WIRING_H
