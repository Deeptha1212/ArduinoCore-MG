#include "HardwareSerial.h"
#include "uart.h"
#include <cstdlib>  // For malloc/free

arduino::HardwareSerial Serial(0);
arduino::HardwareSerial Serial1(1);
arduino::HardwareSerial Serial2(2);
arduino::HardwareSerial Serial3(3);

namespace arduino {

// Constructor
HardwareSerial::HardwareSerial(uint8_t instanceno) : instance(instanceno), uart_config(nullptr) {}

// Initialize UART with baud rate only
void HardwareSerial::begin(unsigned int baudRate) {
    begin(baudRate, SERIAL_8N1);  // Default config
}

// Initialize UART with baud rate and config
void HardwareSerial::begin(unsigned int baudRate, uint16_t config) {
    // Allocate memory if not already allocated
    if (!uart_config) {
        uart_config = (UART_Config_t*)malloc(sizeof(UART_Config_t));
        if (!uart_config) return;  // Memory allocation failed
    }

    uart_config->uart_num = instance;
    uart_config->baudrate = baudRate;
    uart_config->delay = 0;
    uart_config->pullup = 1;
    uart_config->transfer_mode = DATA_SIZE_8;

    // Configure character size
    uart_config->char_size = (config & SERIAL_DATA_5) ? 5 :
                             (config & SERIAL_DATA_6) ? 6 :
                             (config & SERIAL_DATA_7) ? 7 : 8;

    // Configure parity
    uart_config->parity = (config & SERIAL_PARITY_EVEN) ? 2 :
                          (config & SERIAL_PARITY_ODD) ? 1 : 0;

    // Configure stop bits
    uart_config->stop_bits = (config & SERIAL_STOP_BIT_2) ? 2 : 1;

    // Initialize UART
    UART_Init(uart_config);
}

// End communication
void HardwareSerial::end() {
    if (uart_config) {
        uart_config->baudrate = 0;  // Disable UART
        free(uart_config);          // Free allocated memory
        uart_config = nullptr;      // Avoid dangling pointer
    }
}

// Check available bytes
int HardwareSerial::available() {
    return uart_config ? UART_Available(uart_config) : 0;
}

// Peek next byte
int HardwareSerial::peek() {
    return -1;
}

// Read a byte
int HardwareSerial::read() {
    if (!uart_config) return -1;

    uint8_t a;
    struct uart_buf rx = { .uart_data = &a, .len = 1 };

    if (UART_Read_Character(uart_config, &rx) <= 0) {
        return -1;  // No data available
    }

    return a;
}

// Flush UART buffer
void HardwareSerial::flush() {
    if (uart_config) UART_Flush(uart_config);
}

// Write a byte
size_t HardwareSerial::write(uint8_t data) {
    if (!uart_config) return 0;

    struct uart_buf tx = { .uart_data = &data, .len = 1 };
    return UART_Write(uart_config, &tx);
}

}  // namespace arduino



