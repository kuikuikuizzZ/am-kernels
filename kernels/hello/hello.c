#include <am.h>
#include <klib-macros.h>

int main(const char *args) {
  const char *fmt =
    "1234567890";

  for (const char *p = fmt; *p; p++) {
    (*p == '%') ? putstr(args) : putch(*p);
  }
  return 0;
}
