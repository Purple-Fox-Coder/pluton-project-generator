#ifndef PPG_WIN
#define PPG_WIN

#include <stdint.h>
#include <io.h>

int32_t plRead(int fd, void* buf, size_t count) {
  return _read(fd, buf, count);
}
int32_t plWrite(int fd, const void* buf, size_t count) {
  return _write(fd, buf, count);
}

int plOpen(const char* pathname, int flags, int mode) {
  int tmp = 0;

  _sopen_s(&tmp, pathname, flags, _SH_DENYRW, mode);

  return tmp; // _open(pathname, flags, mode);
}
int plClose(int fd) {
  return _close(fd);
}

#endif  // PPG_WIN
