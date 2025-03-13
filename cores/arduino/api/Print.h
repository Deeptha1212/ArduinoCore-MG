/*
  Print.h - Base class that provides print() and println()
  Copyright (c) 2014 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef Print_h
#define Print_h

#include <inttypes.h>
#include <stdio.h> // for size_t
// #include "Arduino.h"
#include"Printable.h"
#include "String.h"
namespace arduino {

class Print
{
public:

  virtual size_t write(uint8_t) = 0;
  size_t write(const char *str);
  size_t write(const uint8_t *buffer, size_t size);

  size_t print(const char[]);
  size_t print(char);
  size_t print(int, int = 10);
  size_t print(unsigned int, int = 10);
  size_t print(long, int = 10);
  size_t print(unsigned long, int = 10);
  size_t print(long long, int = 10);
  size_t print(unsigned long long, int = 10);
  size_t print(double, int = 2);
  size_t print(const Printable&);

  size_t print(const String &s);  // ✅ Add this line
  size_t println(const String &s); // ✅ Add println for String
  size_t print(unsigned char, int = 10);
  size_t println(unsigned char, int = 10);


  size_t println(void);
  size_t println(const char[]);
  size_t println(char);
  size_t println(int, int = 10);
  size_t println(unsigned int, int = 10);
  size_t println(long, int = 10);
  size_t println(unsigned long, int = 10);
  size_t println(long long, int = 10);
  size_t println(unsigned long long, int = 10);
  size_t println(double, int = 2);
  size_t println(const Printable&);

protected:
  size_t printNumber(unsigned long, uint8_t);
  size_t printULLNumber(unsigned long long, uint8_t);
  size_t printFloat(double, uint8_t);
};

}  // ✅ Ensure the namespace exists
using namespace arduino;

#endif
