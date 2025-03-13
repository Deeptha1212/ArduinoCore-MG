#ifndef Printable_h
#define Printable_h
// #include "cstddef"
#include "Print.h"


namespace arduino {
    class Print ;  // Forward declaration inside arduino namespace
}

class Printable
{
public:
    virtual size_t printTo(arduino::Print &p) const = 0;
};

#endif
