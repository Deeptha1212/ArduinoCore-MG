
#pragma once

#include <stdio.h>
#include <stdint.h>
#include <cstring>

#include "string.h"
#include "String.h"
#include "Printable.h"

#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2

namespace arduino {

class Print
{
  private:
    int write_error;
    size_t printNumber(unsigned long, uint8_t);
    size_t printULLNumber(unsigned long long, uint8_t);
  protected:
    void setWriteError(int err = 1) { write_error = err; }
  public:
    Print() : write_error(0) {}

    int getWriteError() { return write_error; }
    void clearWriteError() { setWriteError(0); }

    // Removed virtual write()

    // print() overloads
    size_t print(const char *);
    size_t print(const String &);
    size_t print(char);
    size_t print(unsigned char, int = DEC);
    size_t print(int, int = DEC);
    size_t print(unsigned int, int = DEC);
    size_t print(long, int = DEC);
    size_t print(unsigned long, int = DEC);
    size_t print(long long, int = DEC);
    size_t print(unsigned long long, int = DEC);
    size_t print(double, int = 2);
    size_t print(const Printable&);

    // println() overloads
    size_t println(const char *);
    size_t println(const String &);
    size_t println(char);
    size_t println(unsigned char, int = DEC);
    size_t println(int, int = DEC);
    size_t println(unsigned int, int = DEC);
    size_t println(long, int = DEC);
    size_t println(unsigned long, int = DEC);
    size_t println(long long, int = DEC);
    size_t println(unsigned long long, int = DEC);
    size_t println(double, int = 2);
    size_t println(const Printable&);
    size_t println(void);

    virtual void flush() {}

  private:
    // Internal helpers
    size_t printNumberHelper(unsigned long, uint8_t);
    size_t printULLNumberHelper(unsigned long long, uint8_t);
};

}

using arduino::Print;
