#include "HardwareSerial.h"
#include "uart.h"
namespace arduino {
    
extern uint8_t instance;
class Serial  {

private:
    // RISC-V specific UART registers and configuration variables
    SafeRingBufferN<SERIAL_BUFFER_SIZE> rxBuffer;
    SafeRingBufferN<SERIAL_BUFFER_SIZE> txBuffer;
    
public:
    Serial(uint8_t instanceno) {
        instance = instanceno;
    }

    void begin(unsigned long baudRate) override {
        // Set up UART baud rate, control registers, etc. based on your RISC-V hardware
       begin(baudRate,SERIAL_8N1)
    }
    
    void begin(unsigned long baudRate, uint16_t config) override {
        // Configure baud rate, parity, stop bits, etc. using 'config'
        UART_Config_t *uart_config;
        uart_config->uart_num=instance;
        uart_config->baudrate=baudRate;
        uart_config->delay=0;
        uart_config->pullup=1;
        uart_config->transfer_mode=2;
        uart_config->receive_mode=2;
        switch(){
            
        }

    }
    
    void end() override {
        // Disable UART and clear any configurations
    }
    
    int available() override {
        UART_Available();
        // Return the number of bytes available in the receive buffer
        return rxBuffer.available();
    }

    int peek() override {
        // Peek at the next byte in the receive buffer
        return rxBuffer.peek();
    }

    int read() override {
        // Read a byte from the receive buffer
        return rxBuffer.read();
    }

    void flush() override {
        // Wait until all data has been transmitted (if using TX buffer)
    }

    size_t write(uint8_t data) override {
        // Write data to the UART transmit register and handle TX buffer
        txBuffer.write(data);
        return 1;  // Return the number of bytes written
    }

    operator bool() override {
        // Return true if the UART is initialized and functional
        return uart_base != nullptr;
    }

    void IrqHandler() {
        // RISC-V interrupt handler for UART, read data from UART register into rxBuffer
        // Handle interrupts (e.g., data received or transmission complete)
    }
};

}  // namespace arduino

arduino::Serial Serial0(0);  // Initialize Wire0 on bus 0
arduino::Serial Serial1(1);  // Initialize Wire0 on bus 0
