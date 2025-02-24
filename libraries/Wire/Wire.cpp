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





// #include "i2c.h"
// #include"gptimer.h"
// /*Necessary macros for I2C driver*/
// #define I2C_PIN 0x80
// #define I2C_ESO 0x40
// #define I2C_ES1 0x20
// #define I2C_ES2 0x10
// #define I2C_ENI 0x08
// #define I2C_STA 0x04
// #define I2C_STO 0x02
// #define I2C_ACK 0x01
// #define I2C_INI 0x40   
// #define I2C_STS 0x20
// #define I2C_BER 0x10
// #define I2C_AD0 0x08
// #define I2C_LRB 0x08
// #define I2C_AAS 0x04
// #define I2C_LAB 0x02
// #define I2C_BB  0x01
// #define I2C_START         (I2C_PIN | I2C_ESO | I2C_STA | I2C_ACK)
// #define I2C_STOP          (I2C_PIN | I2C_ESO | I2C_STO | I2C_ACK)
// #define I2C_REPSTART      (                 I2C_ESO | I2C_STA | I2C_ACK)
// #define I2C_IDLE          (I2C_ESO                  | I2C_ACK)
// #define I2C_NACK          (I2C_ESO)
// #define I2C_DISABLE       (I2C_PIN|I2C_ACK)
// #define I2C_OFFSET 0x100


// /* Struct to access I2C registers as 32 bit registers */
// #define I2C_REG(x) ((I2C_Type*)(I2C0_BASE + (x)*I2C_OFFSET))

// uint32_t I2C_Init(uint8_t instance_number,uint32_t clock_frequency)
// { 
//   if(instance_number>1 || instance_number<0)
// 	  return ENODEV;
//   I2C_REG(instance_number)->CTRL = I2C_PIN;//serial interface off -> equivalent to 0x80 in S1'
//   uint32_t scl_div = CLOCK_FREQUENCY_BASE/(2*2*clock_frequency);
//   I2C_REG(instance_number)->S2 = 1;//setting up clock ->equivalent to setting up register S2
//   I2C_REG(instance_number)->SCL = scl_div;
//   I2C_REG(instance_number)->CTRL = I2C_IDLE;//Enable Serial Interface thats it
//   return SUCCESS;
// }

// uint32_t I2C_Transmit(uint32_t instance_number,uint8_t slave_address,uint8_t *data,uint8_t length,uint8_t mode)
// {
//   if(instance_number>1 || instance_number<0)
//     return ENODEV;
//   if(mode & START_BIT)
//   while (!(I2C_REG(instance_number)->STATUS_b.STATUS_BB));//wait till bus is free
//   I2C_REG(instance_number)->S0=(slave_address<<1);//write data in data register
//   if(mode & START_BIT)
//   I2C_REG(instance_number)->CTRL = I2C_START;// as soon as start is initiated after start bit is given slave address along with r/~w is transmitted
//   while (((I2C_REG(instance_number)->CTRL_b.CTRL_PIN)!=0x00));// wait till the eight bits completely get transmitted
  
//   if(!(I2C_REG(instance_number)->STATUS_b.STATUS_AD0_LRB))//check whether ack is receieved from slave
//   {
  
//     log_debug("\nAck received for slave address");
        
//   }
//   else
//   {
//     log_error("\nAck not received for slave address: %x",slave_address);
//     I2C_REG(instance_number)->CTRL = I2C_STOP;
//     return ENOACKDEV;
//   }

//   for (uint32_t i=0;i<length;i++)
//   {
//     I2C_REG(instance_number)->S0=data[i];// write the data in data register
//     while (((I2C_REG(instance_number)->CTRL_b.CTRL_PIN)!=0x00));// wait till the eight bits completely get transmitted
//     if(!(I2C_REG(instance_number)->STATUS_b.STATUS_AD0_LRB))//check whether ack is receieved from slave
//     {
//       log_debug("\nAck received after writing data");
//     }
//     else
//     {
//       log_error("\nAck not received after writing data");
//       I2C_REG(instance_number)->CTRL = I2C_STOP;
//       return ENOACK;
//     }
//   }
//   if(mode & STOP_BIT)
//     I2C_REG(instance_number)->CTRL = I2C_STOP;
//   else{
//     I2C_REG(instance_number)->CTRL = I2C_REPSTART;
//     while (((I2C_REG(instance_number)->CTRL_b.CTRL_PIN)!=0x00));// wait till the eight bits completely get transmitted
//   }
//   return SUCCESS;
// }

// Auint32_t I2C_Recieve(uint32_t instance_number,uint8_t slave_address,uint8_t *data,uint8_t length,uint8_t mode)
// {
//   if(instance_number>1 || instance_number<0)
//     return ENODEV;
//   if(mode & START_BIT)
//     while (!(I2C_REG(instance_number)->STATUS_b.STATUS_BB));//wait till bus is free
//   I2C_REG(instance_number)->S0=(slave_address<<1)|1;//write data in data register
//   if(mode & START_BIT)
//   I2C_REG(instance_number)->CTRL = I2C_START;// as soon as start is initiated after start bit is given slave address along with r/~w is transmitted
//   while (((I2C_REG(instance_number)->CTRL_b.CTRL_PIN)!=0x00));// wait till the eight bits completely get transmitted
//   if(!(I2C_REG(instance_number)->STATUS_b.STATUS_AD0_LRB))//check whether ack is receieved from slave
//   {
//     log_debug("\nAck received for slave address");
//   }
//   else
//   {
//     log_error("\nAck not received for slave address: %x",slave_address);
//     I2C_REG(instance_number)->CTRL = I2C_STOP;
//     return ENOACKDEV;
//   }
//   uint8_t dummy_read;
//     for(int i=0;i<=length;i++)
//     { 
//       if(i==0)
//       {
//         if(length == 1)
//         I2C_REG(instance_number)->CTRL = I2C_NACK;
//         dummy_read = I2C_REG(instance_number)->S0;
//         continue;
//       }
//       while (((I2C_REG(instance_number)->CTRL_b.CTRL_PIN)!=0x00));// wait till the eight bits completely get transmitted
//       if(i == length-1)
//       I2C_REG(instance_number)->CTRL = I2C_NACK;
//       data[i-1] = I2C_REG(instance_number)->S0;
//     }
//     if(mode & STOP_BIT)
//     I2C_REG(instance_number)->CTRL = I2C_STOP;
//     else{
//     I2C_REG(instance_number)->CTRL = I2C_REPSTART;
//     while (((I2C_REG(instance_number)->CTRL_b.CTRL_PIN)!=0x00));// wait till the eight bits completely get transmitted
//     }
//     return SUCCESS;
// }
