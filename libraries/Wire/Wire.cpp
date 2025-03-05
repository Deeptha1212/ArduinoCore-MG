/*
 * TWI/I2C library for Arduino Zero
 * Copyright (c) 2015 Arduino LLC. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

extern "C" {
#include <string.h>
}

#include <Arduino.h>
// #include <wiring_private.h>
#include "Wire.h"

using namespace arduino;
extern uint8_t tempBuffer[256];  
extern uint8_t temp1[256]; 


// Constructor just takes instance number
TwoWire::TwoWire(uint8_t _instanceNumber) {
    _instanceNumber = _instanceNumber;
}

void TwoWire::begin() {
    // Set default clock rate (e.g., 1000 for 1 kHz)
    setClock(1000);  
    I2C_Init(_instanceNumber, 1000);  // Initialize I2C with the instance and baud rate
}

void TwoWire::begin(uint8_t address) { 
    begin();
}

void TwoWire::end() { 
}

void TwoWire::onReceive(void (*function)(int)) { 
}

void TwoWire::onRequest(void (*function)()) { 
}



void TwoWire::setClock(uint32_t baudrate) {
    I2C_Init(_instanceNumber, baudrate);  
}
size_t TwoWire::requestFrom(uint8_t address, size_t quantity, bool stopBit)
{
    if (quantity == 0) {
        return 0;
    }

    size_t byteRead = 0;
    uint8_t temp1[quantity]; // Temporary buffer for received data

    // Transmit a request for data
    if (I2C_Transmit(_instanceNumber, address, nullptr, 0, REPEATED_START)) {
        
        // Receive data directly into temp1
        byteRead = I2C_Recieve(_instanceNumber, address, temp1, quantity, stopBit ? STOP_BIT : REPEATED_START);

        // Copy received data to rxBuffer if needed
        for (size_t i = 0; i < byteRead; i++) {
            rxBuffer.store_char(temp1[i]); // Store in buffer if required
        }
    }

    return byteRead; // Return the number of bytes received
}

// Overloaded function for backward compatibility (defaults to stopBit = true)
size_t TwoWire::requestFrom(uint8_t address, size_t quantity)
{
    return requestFrom(address, quantity, true); // Calls the main function with stopBit = true
}

// Initialize I2C transmission
void TwoWire::beginTransmission(uint8_t address) {
    txAddress = address;
    txBuffer.clear();
    transmissionBegun = true;
}


// size_t TwoWire::requestFrom(uint8_t address, size_t quantity, bool stopBit)
// {
//     if (quantity == 0) {
//         return 0;
//     }

//     size_t byteRead = 0;

//    rxBuffer.clear();  // Clear the buffer before filling it with new data
//    if(I2C_Transmit(_instanceNumber,address,tempBuffer, tempBufferLength,REPEATED_START)){
//       read(address, rxBuffer, quantity);

//       // Create a temporary array to store the data from rxBuffer
//       temp1[quantity];

//       // Copy data from rxBuffer to temp1
//       while (byteRead < quantity && rxBuffer.available()) {
//           temp1[byteRead] = read();  // Store data from rxBuffer into temp1
//           byteRead++;
//       }
//       I2C_Recieve(_instanceNumber,address, temp1, byteRead,REPEATED_START);
//       // Optionally send stop bit if required
//       if (stopBit) {
//         // Pass the temp1 array to your custom i2c_receive function
//         I2C_Recieve(_instanceNumber,address, temp1, byteRead,STOP_BIT);
//       }

//     return byteRead;  // Return the number of bytes read
// }
// }

int TwoWire::read()
{
    // Check if there's data available in the rxBuffer
    if (rxBuffer.available() > 0)
    {
        // Return the next byte from the rxBuffer
        return rxBuffer.read_char();
    }
    else
    {
        // No data available
        return -1;
    }
}

// Errors:
//  0 : Success
//  1 : Data too long
//  2 : NACK on transmit of address
//  3 : NACK on transmit of data
//  4 : Other error

uint8_t TwoWire::endTransmission()
{
  return endTransmission(true);
}

// uint8_t TwoWire::endTransmission(bool stopBit) {
//     transmissionBegun = false;

//     // If there's no data in the tempBuffer, return success
//     if (tempBufferLength == 0) {
//         return 0;  // No data to send
//     }

//     // Call the custom transmit function with tempBuffer
//     I2C_Transmit(_instanceNumber,txAddress,tempBuffer, tempBufferLength,REPEATED_START);

//     // Clear the tempBuffer after transmission
//     tempBufferLength = 0;
// }
uint8_t TwoWire::endTransmission(bool stopBit) {
    if (!transmissionBegun) {
        return 1; // Error: No transmission started
    }

    // Send the buffered data over I2C
    uint8_t result = I2C_Transmit(_instanceNumber, txAddress, txBuffer._aucBuffer, txBuffer.available(), stopBit ? STOP_BIT : REPEATED_START);

    // Reset transmission state
    transmissionBegun = false;
    tempBufferLength = 0;  // Reset buffer length after transmission

    return result;  // Ensure function always returns a value
}



size_t TwoWire::write(uint8_t ucData)
{
    // No writing if transmission hasn't begun or if the buffer is full
    if (!transmissionBegun || txBuffer.isFull()) {
        return 0;
    }

    // Store the data in the ring buffer
    txBuffer.store_char(ucData);

    // Add data to the tempBuffer if there's space
    if (tempBufferLength < sizeof(tempBuffer)) {
        tempBuffer[tempBufferLength++] = ucData;
    }

    return 1;
}


size_t TwoWire::write(const uint8_t *data, size_t quantity) {
    size_t bytesWritten = 0;

    // Ensure we don't exceed the maximum temporary array size
    size_t maxBufferSize = sizeof(tempBuffer);

    for (size_t i = 0; i < quantity; ++i) {
        // If the ring buffer is full or tempBuffer exceeds its size, stop writing
        if (txBuffer.isFull() || bytesWritten >= maxBufferSize) {
            return bytesWritten;  
        }

        // Store the byte in the ring buffer
        txBuffer.store_char(data[i]);

        // Also store the byte in the temp array for transmission
        tempBuffer[bytesWritten] = data[i];

        bytesWritten++;
    }

    return bytesWritten;  // Return total number of bytes written
}


int TwoWire::available(void)
{
  return rxBuffer.available();
}

// int TwoWire::read(void)
// {
//   return rxBuffer.read_char();
// }

int TwoWire::peek(void)
{
  return rxBuffer.peek();
}

void TwoWire::flush(void)
{
  // Do nothing, use endTransmission(..) to force
  // data transfer.
}



