#include "s21_string.h"


char *s21_strtok(char *str, const char *delim) {
  char *result;
  char *start_token;
  char *end_token;
  static char *last_point;

  if(str == S21_NULL) {
    str = last_point;
  }
  if(*str == '\0') {
    result = S21_NULL;
  }

  start_token = str + strspn(str, delim);
  end_token = start_token;

  if(*start_token == '\0') {
    last_point = start_token;
    result = S21_NULL;
  } else {
    last_point = start_token;
    result = start_token;
  }

  end_token = start_token + (strpbrk(start_token, delim) - start_token);
  if (end_token != S21_NULL) {
    *end_token = '\0';
    last_point = end_token + 1;
  } else {
    result = S21_NULL;
  }

  return result;
}
