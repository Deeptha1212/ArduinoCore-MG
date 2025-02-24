#ifndef _VARIANT_SEC_IOT_
#define _VARIANT_SEC_IOT_

#include "Arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

// Number of pins available
#define NUM_DIGITAL_PINS           20
#define NUM_ANALOG_INPUTS          6
#define NUM_ANALOG_OUTPUTS         1

// Define pin numbers
static const uint8_t D0  = 0;
static const uint8_t D1  = 1;
static const uint8_t D2  = 2;
static const uint8_t D3  = 3;
static const uint8_t D4  = 4;
static const uint8_t D5  = 5;
static const uint8_t D6  = 6;
static const uint8_t D7  = 7;
static const uint8_t D8  = 8;
static const uint8_t D9  = 9;

// Analog pins
static const uint8_t A0  = 14;
static const uint8_t A1  = 15;
static const uint8_t A2  = 16;
static const uint8_t A3  = 17;
static const uint8_t A4  = 18;
static const uint8_t A5  = 19;

// UART pins
#define PIN_SERIAL_RX  0
#define PIN_SERIAL_TX  1

#ifdef __cplusplus
}
#endif
// #ifdef __cplusplus
// #include "UART.h"  // Or "HardwareSerial.h" if your core has it
// extern Uart Serial;
// #endif
#endif /* _VARIANT_SEC_IOT_ */
