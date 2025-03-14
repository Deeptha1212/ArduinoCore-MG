#ifndef STRING_H
#define STRING_H

#include <cstddef>  // For size_t

namespace arduino {

    class String {
    private:
        char* buffer;  // Pointer to dynamically allocated memory
        size_t len;    // Current length of the string (not including null-terminator)
        size_t capacity;  // Total capacity of the buffer

        void reserve(size_t size);  // Reserves memory for the string
        void invalidate();  // Clears the current string

    public:
        // Default constructor
        String();

        // Constructor from a C-string
        String(const char* cstr);

        // Copy constructor
        String(const String& other);

        // Move constructor
        String(String&& other) noexcept;

        // Destructor
        ~String();

        bool concat(char c);

        String& operator+=(char c);
        // Copy assignment operator
        String& operator=(const String& other);

        // Move assignment operator
        String& operator=(String&& other) noexcept;

        // Assignment from a C-string
        String& operator=(const char* cstr);

        // Concatenates a C-string to the current string
        bool concat(const char* str);

        // Returns the length of the string
        size_t length() const;

        // Returns the C-string (null-terminated)
        const char* c_str() const;
    };

} // namespace arduino

#endif // STRING_H
