// secufile (c) Mozilla 2025

#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <dlfcn.h>
#include <fcntl.h>
#include <mach-o/loader.h>
#include <sys/_types/_off_t.h>
#include <sys/_types/_ssize_t.h>
#include <unistd.h>

int main() {
  const char *path = "pwrite_bench.dat";
  const size_t write_size = 8;
  const size_t num_writes = 100000;

  char *buf = (char *)malloc(write_size);
  memset(buf, 'A', write_size);
  buf[write_size - 1] = '\n';

  int fd = open(path, O_CREAT | O_RDWR | O_TRUNC, 0644);

  for (size_t i = 0; i < num_writes; i++) {
    off_t off = i * write_size;
    pwrite(fd, buf, write_size, off);
  }

  close(fd);
  free(buf);
  return 0;
}
