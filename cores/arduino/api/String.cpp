#include "String.h"
#include <cstdlib>
#include <cstring>

namespace arduino {

    // Default constructor
    String::String() : buffer(nullptr), len(0), capacity(0) {}

    // Constructor from C-string
    String::String(const char* cstr) : buffer(nullptr), len(0), capacity(0) {
        if (cstr) {
            len = std::strlen(cstr);
            reserve(len + 1);  // +1 for null-terminator
            std::strcpy(buffer, cstr);
        }
    }

    // Copy constructor
    String::String(const String &other) : buffer(nullptr), len(0), capacity(0) {
        if (other.buffer) {
            len = other.len;
            reserve(len + 1);  // +1 for null-terminator
            std::strcpy(buffer, other.buffer);
        }
    }

    // Move constructor
    String::String(String&& other) noexcept : buffer(other.buffer), len(other.len), capacity(other.capacity) {
        other.buffer = nullptr;
        other.len = 0;
        other.capacity = 0;
    }

    // Destructor
    String::~String() {
        if (buffer) {
            std::free(buffer); // Free the allocated memory
        }
    }

    // Copy assignment operator
    String& String::operator=(const String& other) {
        if (this != &other) {
            invalidate();  // Clear old string
            len = other.len;
            reserve(len + 1);  // +1 for null-terminator
            std::strcpy(buffer, other.buffer);
        }
        return *this;
    }

    // Move assignment operator
    String& String::operator=(String&& other) noexcept {
        if (this != &other) {
            invalidate();  // Clear old string
            buffer = other.buffer;
            len = other.len;
            capacity = other.capacity;
            other.buffer = nullptr;
            other.len = 0;
            other.capacity = 0;
        }
        return *this;
    }

    // Assignment from a C-string
    String& String::operator=(const char* cstr) {
        invalidate();  // Clear current string
        if (cstr) {
            len = std::strlen(cstr);
            reserve(len + 1);  // +1 for null-terminator
            std::strcpy(buffer, cstr);
        }
        return *this;
    }

    // Concatenates a C-string to the current string
    bool String::concat(const char* str) {
        if (str) {
            size_t strLen = std::strlen(str);
            reserve(len + strLen + 1);  // +1 for null-terminator
            std::strcpy(buffer + len, str);
            len += strLen;
            return true;
        }
        return false;
    }

    // Returns the length of the string
    size_t String::length() const {
        return len;
    }

    // Returns the C-string (null-terminated)
    const char* String::c_str() const {
        return buffer ? buffer : "";
    }

    // Ensures the buffer can hold the string of a given size
    void String::reserve(size_t size) {
        if (size > capacity) {
            capacity = size;
            buffer = (char*)std::realloc(buffer, capacity); // Reallocate buffer with new size
            if (buffer == nullptr) {
                len = 0;
                capacity = 0;
            }
        }
    }

    // Invalidates the current string
    void String::invalidate() {
        if (buffer) {
            std::free(buffer);  // Release the allocated memory
            buffer = nullptr;
        }
        len = 0;
        capacity = 0;
    }

} // namespace arduino
