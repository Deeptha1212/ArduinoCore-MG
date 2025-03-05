#include <sys/stat.h>
#include <errno.h>

// Dummy syscall implementations to satisfy linker requirements

int _getpid(void) {
    return 1;
}

int _kill(int pid, int sig) {
    errno = EINVAL;
    return -1;
}

int _write(int file, char *ptr, int len) {
    return len; // Pretend that all bytes were written
}

int _close(int file) {
    return -1;
}

int _fstat(int file, struct stat *st) {
    st->st_mode = S_IFCHR;
    return 0;
}

int _isatty(int file) {
    return 1;
}

int _lseek(int file, int ptr, int dir) {
    return 0;
}

int _read(int file, char *ptr, int len) {
    return 0;
}

int _open(const char *path, int flags, ...) {
    return -1;
}

int _wait(int *status) {
    return -1;
}

int _unlink(const char *name) {
    return -1;
}

int _times(void *buf) {
    return -1;
}

int _stat(const char *file, struct stat *st) {
    st->st_mode = S_IFCHR;
    return 0;
}

int _link(const char *old, const char *new) {
    return -1;
}

int _fork(void) {
    return -1;
}

int _execve(const char *name, char *const argv[], char *const env[]) {
    return -1;
}
