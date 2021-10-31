#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  char *result;
  char *start_token;
  char *end_token;
  static char *search_point;

  if(str == S21_NULL) {
    str = search_point;
  }
  if(*str == '\0') {
    result = S21_NULL;
  }

  start_token = str + strspn(str, delim);
  if(*start_token == '\0') {
    search_point = start_token;
    result = S21_NULL;
  }

  end_token = str + (strpbrk(str, delim) - str);
  if(*end_token == '\0') {
    search_point = end_token;
    result = S21_NULL;
  }

  *end_token = '\0';
  search_point = end_token + 1;
  return result;
}
