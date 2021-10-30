#include "s21_string.h"

int s21_wrapper_sprintf(char *str, char *format, ...) {
  va_list args;
  int changes_count;
  va_start(args, format);
  changes_count = s21_sprintf(str, format, args);
  va_end(args);
  return changes_count;
}
