// secufile (c) Mozilla 2025

#include <cstdio>
#include <cstring>
#include <sys/types.h>
#include <unistd.h>

extern "C" {

__attribute__((always_inline, hot)) ssize_t interposed_pwrite(int fd,
                                                              const void *buf,
                                                              size_t count,
                                                              off_t offset) {
  static bool logged = false;
  if (!logged) {
    printf("Interposed\n");
    logged = true;
  }
  return pwrite(fd, buf, count - 1, offset);
}

} // extern "C"

// Interposition structures for ARM64 - these tell dyld to replace system calls
struct interpose_s {
  void *new_func;
  void *orig_func;
};

#define INTERPOSE_FUNCTION(NEW_FUNC, ORIG_FUNC)                                \
  __attribute__((used)) static const struct interpose_s _interpose_##ORIG_FUNC \
      __attribute__((section("__DATA,__interpose"))) = {(void *)(NEW_FUNC),    \
                                                        (void *)(ORIG_FUNC)}
INTERPOSE_FUNCTION(interposed_pwrite, pwrite);
