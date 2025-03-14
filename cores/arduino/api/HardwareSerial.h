#pragma once

#include <inttypes.h>
#include "Stream.h"
#include "uart.h"  // Ensure UART_Config_t is properly included

#ifndef HARDWARESERIAL_H
#define HARDWARESERIAL_H

namespace arduino {

// UART configuration settings
#define SERIAL_PARITY_EVEN   (0x1ul)
#define SERIAL_PARITY_ODD    (0x2ul)
#define SERIAL_PARITY_NONE   (0x3ul)
#define SERIAL_PARITY_MARK   (0x4ul)
#define SERIAL_PARITY_SPACE  (0x5ul)
#define SERIAL_PARITY_MASK   (0xFul)

#define SERIAL_STOP_BIT_1    (0x10ul)
#define SERIAL_STOP_BIT_1_5  (0x20ul)
#define SERIAL_STOP_BIT_2    (0x30ul)
#define SERIAL_STOP_BIT_MASK (0xF0ul)

#define SERIAL_DATA_5        (0x100ul)
#define SERIAL_DATA_6        (0x200ul)
#define SERIAL_DATA_7        (0x300ul)
#define SERIAL_DATA_8        (0x400ul)
#define SERIAL_DATA_MASK     (0xF00ul)

// Standard UART configurations
#define SERIAL_5N1 (SERIAL_STOP_BIT_1 | SERIAL_PARITY_NONE | SERIAL_DATA_5)
#define SERIAL_6N1 (SERIAL_STOP_BIT_1 | SERIAL_PARITY_NONE | SERIAL_DATA_6)
#define SERIAL_7N1 (SERIAL_STOP_BIT_1 | SERIAL_PARITY_NONE | SERIAL_DATA_7)
#define SERIAL_8N1 (SERIAL_STOP_BIT_1 | SERIAL_PARITY_NONE | SERIAL_DATA_8)

// Define more configurations as needed...

class HardwareSerial : public Stream {
public:
    // Constructor
    HardwareSerial(uint8_t instanceno);

    // Initialize UART
    virtual void begin(unsigned long baudRate);
    virtual void begin(unsigned long baudRate, uint16_t config);
    
    // End the UART communication
    virtual void end();
    
    // UART data handling functions
    virtual int available();
    virtual int peek();
    virtual int read();
    virtual void flush();
    virtual size_t write(uint8_t data);
    
    // Operator bool to check if the serial interface is available
    virtual operator bool() { return uart_config != nullptr; }

protected:
    uint8_t instance;
   UART_Config_t  *uart_config;
};

// Weak definition for serialEventRun (if used)
extern void serialEventRun(void) __attribute__((weak));
// Serial objects declaration


#endif  // HARDWARESERIAL_H
}
extern arduino::HardwareSerial Serial;
extern arduino::HardwareSerial Serial1;
extern arduino::HardwareSerial Serial2;
extern arduino::HardwareSerial Serial3;