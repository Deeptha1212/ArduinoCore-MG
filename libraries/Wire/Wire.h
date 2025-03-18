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

#ifndef WIRE_H
#define WIRE_H



#include "api/HardwareI2C.h"
#include "RingBuffer.h"
#include "variant.h"
#include "i2c.h"

 // WIRE_HAS_END means Wire has end()
#define WIRE_HAS_END 1
extern int _instanceNumber; 
extern uint8_t temp1[256]; 

namespace arduino {

class TwoWire : public HardwareI2C
{
  public:
    TwoWire(uint8_t _instanceNumber);
    void begin() override;
    void begin(uint8_t address) override;
    
    void end() override;
    // void onReceive(void (*function)(int)) override;
    // void onRequest(void (*function)()) override;
    void setClock(uint32_t);

    void beginTransmission(uint8_t);
    uint8_t endTransmission(bool stopBit);
    uint8_t endTransmission(void);

    size_t requestFrom(uint8_t address, size_t quantity, bool stopBit);
    size_t requestFrom(uint8_t address, size_t quantity);

    size_t write(uint8_t data);
    size_t write(const uint8_t * data, size_t quantity);
 
    size_t read(uint8_t address, RingBuffer& rxBuffer, size_t quantity);

    virtual int available(void);
    virtual int read(void);
    virtual int peek(void);
    virtual void flush(void);

    inline size_t write(unsigned long n) { return write((uint8_t)n); }
    inline size_t write(long n) { return write((uint8_t)n); }
    inline size_t write(unsigned int n) { return write((uint8_t)n); }
    inline size_t write(int n) { return write((uint8_t)n); }
    using Print::write;



 private:
     // Store the instance number
    // RX Buffer
   
    uint8_t tempBuffer[256];  // Temporary buffer to hold data for custom transmission
    size_t tempBufferLength;  // To track the length of data in the tempBuffer
    bool transmissionBegun;
    RingBufferN<256> rxBuffer;

    //TX buffer
    RingBufferN<256> txBuffer;
    uint8_t txAddress;


    // TWI clock frequency
    static const uint32_t TWI_CLOCK = 100000;
};

}

extern arduino::TwoWire Wire0;
extern arduino::TwoWire Wire1;




#endif  // WIRE_H

