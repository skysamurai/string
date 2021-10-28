#include "string.h"
#include "stdarg.h"

int s21_sprintf(char *str, char *format, ...) {
  int element_count = -1;
  va_list args;
  va_start(args, format);
  for(char *cursor = format; *cursor; ++cursor) {
    if(*cursor == '%') {
      ++cursor;
    }
  }
  va_end(args);
  return element_count;
}