#include "s21_vsprintf.h"

int s21_vsprintf(char *str, const char *format, va_list args) {
  int number_system; /* система счисления */
  int number_digits_count; /* количество цифр */
  unsigned long unsigned_number; /* число без знака */

  s21_byte_t number_flags; /* флаги для обработки числа */
  int field_width; /* минимальная ширина вывода поля */
  int precision; /* точность числа */
  int qualifier; /* описание длины */

  char* buf_string_specifiers;
  char *s_cursor = str; /* курсор строки */
  const char *f_cursor = format; /* курсор формата */

  for(s_cursor, f_cursor; *f_cursor != '\0'; ++f_cursor) {
    /* переписываем всё из формат строки до %*/
    while(*f_cursor != '%') {
      *s_cursor = *f_cursor;
      ++s_cursor;
      ++f_cursor;
    }
    /* парсинг флагов формата вывода числа */
    number_flags = 0;
    while(++f_cursor) {
      if(*f_cursor == '-') {
        number_flags |= LEFT_ALIGMENT;
      }
      else if(*f_cursor == '+') {
        number_flags |= SHOW_SIGN;
      }
      else if(*f_cursor == ' ') {
        number_flags |= REPLACE_SIGN_SPACE;
      }
      else if(*f_cursor == '#') {
        number_flags |= NUMBER_SYSTEM;
      }
      else if(*f_cursor == '0') {
        number_flags |= ZERO_PAD;
      } else {
        break;
      }
    }
    /* ширина поля */
    field_width = -1;
    if(is_digit(*f_cursor)) {
      field_width = atoi_cursoring(&f_cursor);
    }
    else if (*f_cursor == '*') {
      ++f_cursor;
      field_width = va_arg(args, int);
      if (field_width < 0) {
        field_width = -field_width;
        number_flags |= LEFT_ALIGMENT;
      }
    }
    /* вычисление точности вывода */
    precision = -1;
    if(*f_cursor == '.') {
      ++f_cursor;
      if(is_digit(*f_cursor)) {
        precision = atoi_cursoring(&f_cursor);
      } else if (*f_cursor == '*') {
        ++f_cursor;
        precision = va_arg(args, int);
      }
      if(precision < 0) {
        precision = 0;
      }
    }
    /* тип числа */
    qualifier = -1;
    

  }
}

/* проверка чара на принадлежность к числу */
int is_digit(char chr) {
  return (chr >= '0') && (chr <= '9');
}

/* реализация простого atoi с перемещением курсора */
int atoi_cursoring(const char **cursor) {
  char chr;
  int i;
  for (i = 0; is_digit(chr = **cursor); ++*cursor)
    i = i * 10 + chr - '0';
  return i;
}
