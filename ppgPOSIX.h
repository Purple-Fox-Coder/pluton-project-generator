#ifndef PPG_POSIX
#define PPG_POSIX

#include <stdint.h>

#include <unistd.h>

int32_t plRead(int fd, void* buf, size_t count) {
  return read(fd, buf, count);
}
int32_t plWrite(int fd, const void* buf, size_t count) {
  return write(fd, buf, count);
}

int plOpen(const char* pathname, int flags, int mode) {
  return open(pathname, flags, mode);
}
int plClose(int fd) {
  return close(fd);
}

#endif  // PPG_POSIX
