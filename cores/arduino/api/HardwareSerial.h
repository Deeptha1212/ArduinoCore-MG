#pragma once

#include <inttypes.h>
#include "Stream.h"
#include "SafeRingBuffer.h"


#endif

namespace arduino {

// UART configuration settings (you might want to adjust these for your RISC-V platform)
// XXX: Those constants should be defined as const int / enums?
// XXX: shall we use namespaces too?
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

#define SERIAL_5N1           (SERIAL_STOP_BIT_1 | SERIAL_PARITY_NONE  | SERIAL_DATA_5)
#define SERIAL_6N1           (SERIAL_STOP_BIT_1 | SERIAL_PARITY_NONE  | SERIAL_DATA_6)
#define SERIAL_7N1           (SERIAL_STOP_BIT_1 | SERIAL_PARITY_NONE  | SERIAL_DATA_7)
#define SERIAL_8N1           (SERIAL_STOP_BIT_1 | SERIAL_PARITY_NONE  | SERIAL_DATA_8)
#define SERIAL_5N2           (SERIAL_STOP_BIT_2 | SERIAL_PARITY_NONE  | SERIAL_DATA_5)
#define SERIAL_6N2           (SERIAL_STOP_BIT_2 | SERIAL_PARITY_NONE  | SERIAL_DATA_6)
#define SERIAL_7N2           (SERIAL_STOP_BIT_2 | SERIAL_PARITY_NONE  | SERIAL_DATA_7)
#define SERIAL_8N2           (SERIAL_STOP_BIT_2 | SERIAL_PARITY_NONE  | SERIAL_DATA_8)
#define SERIAL_5E1           (SERIAL_STOP_BIT_1 | SERIAL_PARITY_EVEN  | SERIAL_DATA_5)
#define SERIAL_6E1           (SERIAL_STOP_BIT_1 | SERIAL_PARITY_EVEN  | SERIAL_DATA_6)
#define SERIAL_7E1           (SERIAL_STOP_BIT_1 | SERIAL_PARITY_EVEN  | SERIAL_DATA_7)
#define SERIAL_8E1           (SERIAL_STOP_BIT_1 | SERIAL_PARITY_EVEN  | SERIAL_DATA_8)
#define SERIAL_5E2           (SERIAL_STOP_BIT_2 | SERIAL_PARITY_EVEN  | SERIAL_DATA_5)
#define SERIAL_6E2           (SERIAL_STOP_BIT_2 | SERIAL_PARITY_EVEN  | SERIAL_DATA_6)
#define SERIAL_7E2           (SERIAL_STOP_BIT_2 | SERIAL_PARITY_EVEN  | SERIAL_DATA_7)
#define SERIAL_8E2           (SERIAL_STOP_BIT_2 | SERIAL_PARITY_EVEN  | SERIAL_DATA_8)
#define SERIAL_5O1           (SERIAL_STOP_BIT_1 | SERIAL_PARITY_ODD   | SERIAL_DATA_5)
#define SERIAL_6O1           (SERIAL_STOP_BIT_1 | SERIAL_PARITY_ODD   | SERIAL_DATA_6)
#define SERIAL_7O1           (SERIAL_STOP_BIT_1 | SERIAL_PARITY_ODD   | SERIAL_DATA_7)
#define SERIAL_8O1           (SERIAL_STOP_BIT_1 | SERIAL_PARITY_ODD   | SERIAL_DATA_8)
#define SERIAL_5O2           (SERIAL_STOP_BIT_2 | SERIAL_PARITY_ODD   | SERIAL_DATA_5)
#define SERIAL_6O2           (SERIAL_STOP_BIT_2 | SERIAL_PARITY_ODD   | SERIAL_DATA_6)
#define SERIAL_7O2           (SERIAL_STOP_BIT_2 | SERIAL_PARITY_ODD   | SERIAL_DATA_7)
#define SERIAL_8O2           (SERIAL_STOP_BIT_2 | SERIAL_PARITY_ODD   | SERIAL_DATA_8)
#define SERIAL_5M1           (SERIAL_STOP_BIT_1 | SERIAL_PARITY_MARK  | SERIAL_DATA_5)
#define SERIAL_6M1           (SERIAL_STOP_BIT_1 | SERIAL_PARITY_MARK  | SERIAL_DATA_6)
#define SERIAL_7M1           (SERIAL_STOP_BIT_1 | SERIAL_PARITY_MARK  | SERIAL_DATA_7)
#define SERIAL_8M1           (SERIAL_STOP_BIT_1 | SERIAL_PARITY_MARK  | SERIAL_DATA_8)
#define SERIAL_5M2           (SERIAL_STOP_BIT_2 | SERIAL_PARITY_MARK  | SERIAL_DATA_5)
#define SERIAL_6M2           (SERIAL_STOP_BIT_2 | SERIAL_PARITY_MARK  | SERIAL_DATA_6)
#define SERIAL_7M2           (SERIAL_STOP_BIT_2 | SERIAL_PARITY_MARK  | SERIAL_DATA_7)
#define SERIAL_8M2           (SERIAL_STOP_BIT_2 | SERIAL_PARITY_MARK  | SERIAL_DATA_8)
#define SERIAL_5S1           (SERIAL_STOP_BIT_1 | SERIAL_PARITY_SPACE | SERIAL_DATA_5)
#define SERIAL_6S1           (SERIAL_STOP_BIT_1 | SERIAL_PARITY_SPACE | SERIAL_DATA_6)
#define SERIAL_7S1           (SERIAL_STOP_BIT_1 | SERIAL_PARITY_SPACE | SERIAL_DATA_7)
#define SERIAL_8S1           (SERIAL_STOP_BIT_1 | SERIAL_PARITY_SPACE | SERIAL_DATA_8)
#define SERIAL_5S2           (SERIAL_STOP_BIT_2 | SERIAL_PARITY_SPACE | SERIAL_DATA_5)
#define SERIAL_6S2           (SERIAL_STOP_BIT_2 | SERIAL_PARITY_SPACE | SERIAL_DATA_6)
#define SERIAL_7S2           (SERIAL_STOP_BIT_2 | SERIAL_PARITY_SPACE | SERIAL_DATA_7)
#define SERIAL_8S2           (SERIAL_STOP_BIT_2 | SERIAL_PARITY_SPACE | SERIAL_DATA_8)

class HardwareSerial : public Stream
{
public:
    // Constructor: Must initialize the platform-specific hardware (UART)
    virtual void begin(unsigned long baudRate) = 0;
    virtual void begin(unsigned long baudRate, uint16_t config) = 0;
    
    // End the UART communication
    virtual void end() = 0;
    
    // UART data handling functions
    virtual int available() = 0;
    virtual int peek() = 0;
    virtual int read() = 0;
    virtual void flush() = 0;
    virtual size_t write(uint8_t data) = 0;
        
    // Operator bool to check if the serial interface is available
    virtual operator bool() = 0;
private:
    uint8_t instance; 
    typedef struct 
    {
	
	    uint8_t uart_num ;/*An Integer type parameter, which gets the uart number 
	  * from the user needed to be initialized. This is usually, 1 and 2, as
	  * the 0th instance is occupied for the serial communication.*/

	    unsigned int baudrate; //The desired baud rate for the UART communication.

	    uint8_t stop_bits : 2; //An integer type, which is of 2 bits. The value can be from 0-2, and 3 is undefined.

	    uint8_t parity : 2; //An integer type, which is again of 2 bits. The value can be from 0-2, and 3 is undefined.

	    uint8_t char_size : 2; //An integer type, which is of 2 bits. The values to be given are 5,6,7 and 8.

	    unsigned short delay; // Delay value

	    unsigned char rxthreshold;/*The value of the receive (RX) threshold for a UART instance. This 
                              * value is used to set the RX Threshold value of RX FIFO.*/

	    uint8_t transfer_mode : 3;

	    uint8_t receive_mode : 3 ;

	    uint8_t pullup : 1;

    }UART_Config_t;
};

// Weak definition for serialEventRun (if used)
extern void serialEventRun(void) __attribute__((weak));

}  // namespace arduino

extern arduino::Serial Serial0;
extern arduino::Serial Serial1;
