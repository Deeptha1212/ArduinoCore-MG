#include <sys/stat.h>
#include <errno.h>


// #include "cores/arduino/Arduino.h"
#pragma once

extern "C" {
    #include "api/HardwareSerial.h"
}

// Get process ID (not relevant for microcontrollers)
int _getpid(void) {
    return 1;
}

// Kill a process (not implemented)
int _kill(int pid, int sig) {
    errno = EINVAL;
    return -1;
}

// Redirect `printf()` and `write()` output to Serial
int _write(int file, char *ptr, int len) {
    for (int i = 0; i < len; i++) {
        arduino::Serial0.write(ptr[i]); 
    }
    return len;
}

// Reentrant version of _write (for Newlib)
int _write_r(struct _reent *r, int file, char *ptr, int len) {
    return _write(file, ptr, len);
}

// Close a file (not used in embedded)
int _close(int file) {
    return -1;
}

// Get file status (mark as character device)
int _fstat(int file, struct stat *st) {
    st->st_mode = S_IFCHR;  // Tell the system it's a character device (Serial)
    return 0;
}

// Check if file is a terminal (always true for Serial)
int _isatty(int file) {
    return 1;
}

// Seek in a file (not supported)
int _lseek(int file, int ptr, int dir) {
    return 0;
}

// Read (no input handling, return 0)
int _read(int file, char *ptr, int len) {
    return 0;
}

// Open a file (not supported)
int _open(const char *path, int flags, ...) {
    return -1;
}

// Wait for a process (not applicable)
int _wait(int *status) {
    return -1;
}

// Remove a file (not applicable)
int _unlink(const char *name) {
    return -1;
}

// Get system times (not applicable)
int _times(void *buf) {
    return -1;
}

// Get file status (again, mark as character device)
int _stat(const char *file, struct stat *st) {
    st->st_mode = S_IFCHR;
    return 0;
}

// Create a new link (not supported)
int _link(const char *old, const char *new_path) {
    return -1;
}

// Fork a process (not possible)
int _fork(void) {
    return 0;
}

// Execute a new process (not possible)
int _execve(const char *name, char *const argv[], char *const env[]) {
    return -1;
}
