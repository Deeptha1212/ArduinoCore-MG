#include "HardwareSerial.h"
#include "uart.h"

namespace arduino {

class Serial {
private:
    uint8_t instance;
    SafeRingBufferN<SERIAL_BUFFER_SIZE> rxBuffer;
    SafeRingBufferN<SERIAL_BUFFER_SIZE> txBuffer;
    UART_Config_t *uart_config;  // Pointer to store UART configuration

public:
    Serial(uint8_t instanceno) : instance(instanceno), uart_config(nullptr) {}

    void begin(unsigned long baudRate) override {
        begin(baudRate, SERIAL_8N1);  // Default config
    }

    void begin(unsigned long baudRate, uint16_t config) override {
        UART_Config_t *uart_config;

        uart_config->uart_num = instance;
        uart_config->baudrate = baudRate;
        uart_config->delay = 0;
        uart_config->pullup = 1;
        uart_config->transfer_mode = DATA_SIZE_8;

        // Configure character size
        if (config & SERIAL_DATA_5) {
            uart_config->char_size = 5;
        } else if (config & SERIAL_DATA_6) {
            uart_config->char_size = 6;
        } else if (config & SERIAL_DATA_7) {
            uart_config->char_size = 7;
        } else {
            uart_config->char_size = 8;
        }

        // Configure parity
        if (config & SERIAL_PARITY_EVEN) {
            uart_config->parity = 2;
        } else if (config & SERIAL_PARITY_ODD) {
            uart_config->parity = 1;
        } else {
            uart_config->parity = 0;
        }

        // Configure stop bits
        if (config & SERIAL_STOP_BIT_2) {
            uart_config->stop_bits = 2;
        } else {
            uart_config->stop_bits = 1;
        }

        // Initialize UART
        UART_Init(uart_config);
    }

    void end() override {
       return -1;
    }

    int available() override {
        return uart_config ? UART_Available(uart_config) : 0;
    }

    int peek() override {
        return rxBuffer.peek();
    }

    int read() override {
          struct uart_buf rx = { .uart_data = &a, .len = x};
          return UART_Read_Character(uart_config->uart_num);
    }

    void flush() override {
        if (uart_config) {
            UART_Flush(uart_config);
        }
    }

    size_t write(uint8_t data) override {
        if (!uart_config) return 0;
        struct uart_buf tx = { .uart_data = data, .len = StrLen(data) / 2 };
        return UART_Write(uart_config, &tx);  // Send data via UART
    }
};

}  // namespace arduino
