#include "Print.h"
#include <stdio.h>

namespace arduino {

// Print functions

size_t Print::print(const char *str) {
    if (!str) return 0;
    return printf("%s", str);
}

size_t Print::print(const String &s) {
    return printf("%s", s.c_str());
}

size_t Print::print(char c) {
    return printf("%c", c);
}

size_t Print::print(unsigned char val, int base) {
    return print((unsigned long)val, base);
}

size_t Print::print(int val, int base) {
    return print((long)val, base);
}

size_t Print::print(unsigned int val, int base) {
    return print((unsigned long)val, base);
}

size_t Print::print(long val, int base) {
    if (base == DEC) return printf("%ld", val);
    if (base == HEX) return printf("%lX", val);
    if (base == OCT) return printf("%lo", val);
    if (base == BIN) return printNumber((unsigned long)val, BIN);
    return 0;
}

size_t Print::print(unsigned long val, int base) {
    if (base == DEC) return printf("%lu", val);
    if (base == HEX) return printf("%lX", val);
    if (base == OCT) return printf("%lo", val);
    if (base == BIN) return printNumber(val, BIN);
    return 0;
}

size_t Print::print(long long val, int base) {
    if (base == DEC) return printf("%lld", val);
    if (base == HEX) return printf("%llX", val);
    if (base == OCT) return printf("%llo", val);
    if (base == BIN) return printULLNumber((unsigned long long)val, BIN);
    return 0;
}

size_t Print::print(unsigned long long val, int base) {
    if (base == DEC) return printf("%llu", val);
    if (base == HEX) return printf("%llX", val);
    if (base == OCT) return printf("%llo", val);
    if (base == BIN) return printULLNumber(val, BIN);
    return 0;
}

size_t Print::print(double val, int digits) {
    char fmt[10];
    printf(fmt, sizeof(fmt), "%%.%df", digits);
    return printf(fmt, val);
}

size_t Print::print(const Printable &p) {
    return p.printTo(*this);
}

// println functions

size_t Print::println(const char *str) {
    if (!str) return printf("\n");
    return printf("%s\n", str);
}

size_t Print::println(const String &s) {
    return printf("%s\n", s.c_str());
}

size_t Print::println(char c) {
    return printf("%c\n", c);
}

size_t Print::println(unsigned char val, int base) {
    size_t n = print(val, base);
    return n + printf("\n");
}

size_t Print::println(int val, int base) {
    size_t n = print(val, base);
    return n + printf("\n");
}

size_t Print::println(unsigned int val, int base) {
    size_t n = print(val, base);
    return n + printf("\n");
}

size_t Print::println(long val, int base) {
    size_t n = print(val, base);
    return n + printf("\n");
}

size_t Print::println(unsigned long val, int base) {
    size_t n = print(val, base);
    return n + printf("\n");
}

size_t Print::println(long long val, int base) {
    size_t n = print(val, base);
    return n + printf("\n");
}

size_t Print::println(unsigned long long val, int base) {
    size_t n = print(val, base);
    return n + printf("\n");
}

size_t Print::println(double val, int digits) {
    size_t n = print(val, digits);
    return n + printf("\n");
}

size_t Print::println(const Printable &p) {
    size_t n = print(p);
    return n + printf("\n");
}

size_t Print::println(void) {
    return printf("\n");
}

// Private helpers

size_t Print::printNumber(unsigned long n, uint8_t base) {
    char buf[65];
    char *str = &buf[sizeof(buf) - 1];
    *str = '\0';
    if (n == 0) *--str = '0';
    else {
        while (n > 0) {
            *--str = "0123456789ABCDEF"[n % base];
            n /= base;
        }
    }
    return printf("%s", str);
}

size_t Print::printULLNumber(unsigned long long n, uint8_t base) {
    char buf[65];
    char *str = &buf[sizeof(buf) - 1];
    *str = '\0';
    if (n == 0) *--str = '0';
    else {
        while (n > 0) {
            *--str = "0123456789ABCDEF"[n % base];
            n /= base;
        }
    }
    return printf("%s", str);
}



} // namespace arduino
