#include <sys/stat.h>
#include <errno.h>
#include "Arduino.h"  // Required for Serial in Arduino
extern "C" {
    #include "api/HardwareSerial.h"
}

// Get process ID (not relevant for microcontrollers)
__attribute__((weak)) int _getpid(void) {
    return 1;
}

// Kill a process (not implemented)
__attribute__((weak)) int _kill(int pid, int sig) {
    errno = EINVAL;
    return -1;
}

// Redirect `printf()` and `write()` output to Serial
__attribute__((weak)) int _write(int file, char *ptr, int len) {
    for (int i = 0; i < len; i++) {
        arduino::Serial0.write(ptr[i]);
    }
    return len;
}

// Close a file (not used in embedded)
__attribute__((weak)) int _close(int file) {
    return -1;
}

// Get file status (mark as character device)
__attribute__((weak)) int _fstat(int file, struct stat *st) {
    st->st_mode = S_IFCHR;  // Tell the system it's a character device (Serial)
    return 0;
}

// Check if file is a terminal (always true for Serial)
__attribute__((weak)) int _isatty(int file) {
    return 1;
}

// Seek in a file (not supported)
__attribute__((weak)) int _lseek(int file, int ptr, int dir) {
    return 0;
}

// Read (no input handling, return 0)
__attribute__((weak)) int _read(int file, char *ptr, int len) {
    return 0;
}

// Open a file (not supported)
__attribute__((weak)) int _open(const char *path, int flags, ...) {
    return -1;
}

// Wait for a process (not applicable)
__attribute__((weak)) int _wait(int *status) {
    return -1;
}

// Remove a file (not applicable)
__attribute__((weak)) int _unlink(const char *name) {
    return -1;
}

// Get system times (not applicable)
__attribute__((weak)) int _times(void *buf) {
    return -1;
}

// Get file status (again, mark as character device)
__attribute__((weak)) int _stat(const char *file, struct stat *st) {
    st->st_mode = S_IFCHR;
    return 0;
}

// Create a new link (not supported)
__attribute__((weak)) int _link(const char *old, const char  *newPath) {
    return -1;
}

// Fork a process (not possible)
__attribute__((weak)) int _fork(void) {
    return 0;
}

// Execute a new process (not possible)
__attribute__((weak)) int _execve(const char *name, char *const argv[], char *const env[]) {
    return -1;
}
