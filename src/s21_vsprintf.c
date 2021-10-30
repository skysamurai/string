#include "s21_vsprintf.h"

int s21_vsprintf(char *str, const char *format, va_list args) {
  int number_system; /* система счисления */
  int number_digits_count; /* количество цифр */
  unsigned long unsigned_number; /* число без знака */

  struct format_info info;

  char* buf_string_specifiers;
  char *s_cursor = str; /* курсор строки */
  const char *f_cursor = format; /* курсор формата */

  for(s_cursor, f_cursor; *f_cursor != '\0'; ++f_cursor) {

    if(*f_cursor != '%') {
      *s_cursor++ = *f_cursor;
      continue;
    }

    parse_format_flag(&f_cursor, &info, args);
    parse_field_width(&f_cursor, &info, args);
    parse_precision(&f_cursor, &info, args);
    parse_qualifier(&f_cursor, &info, args);

    if(*f_cursor == 'c') {
      put_char_cursoring(&s_cursor, &info, args);
    } else if(*f_cursor == 's') {

    } else if(*f_cursor == 'p') {

    } else if(*f_cursor == 'n') {

    } else if(*f_cursor == '%') {
      *s_cursor++ = '%';
    } else if(*f_cursor == 'o') {

    } else if(*f_cursor == 'X') {

    } else if(*f_cursor == 'x') {

    } else if(*f_cursor == 'd' || *f_cursor == 'i') {

    } else if(*f_cursor == 'u') {

    } else if(*f_cursor == 'e') {

    } else if(*f_cursor == 'E') {

    } else if(*f_cursor == 'g' || *f_cursor == 'G') {

    } if (*f_cursor == 'f') {

    }
  }
  *s_cursor = '\0';
}

void parse_format_flag(const char **format, struct format_info *info, va_list args) {
  info->number_flags = 0;
  while(++(*format)) {
    if(**format == '-') {
      info->number_flags |= LEFT_ALIGMENT;
    }
    else if(**format == '+') {
      info->number_flags |= SHOW_SIGN;
    }
    else if(**format == ' ') {
      info->number_flags |= REPLACE_SIGN_SPACE;
    }
    else if(**format == '#') {
      info->number_flags |= NUMBER_SYSTEM;
    }
    else if(**format == '0') {
      info->number_flags |= ZERO_PAD;
    } else {
      break;
    }
  }
}

void parse_field_width(const char **format, struct format_info *info, va_list args) {
  info->field_width = -1;
  if(is_digit(**format)) {
    info->field_width = atoi_cursoring(format);
  }
  else if (**format == '*') {
    ++(*format);
    info->field_width = va_arg(args, int);
    if (info->field_width < 0) {
      info->field_width = -info->field_width;
      info->number_flags |= LEFT_ALIGMENT;
    }
  }
}

void parse_precision(const char **format, struct format_info *info, va_list args) {
  info->precision = -1;
  if(**format == '.') {
    ++(*format);
    if(is_digit(**format)) {
      info->precision = atoi_cursoring(format);
    } else if (**format == '*') {
      ++(*format);
      info->precision = va_arg(args, int);
    }
    if(info->precision < 0) {
      info->precision = 0;
    }
  }
}

void parse_qualifier(const char **format, struct format_info *info, va_list args) {
  info->qualifier = -1;
  if (**format == 'l' && **(format + 1) == 'l') {
    info->qualifier = LONG_LONG;
    (*format) += 2;
  } else if(**format == 'h' || **format == 'l'
            || **format == 'L' || **format == 'Z') {
    info->qualifier = **format;
    ++(*format);
  }
}

int is_digit(char chr) {
  return (chr >= '0') && (chr <= '9');
}

int atoi_cursoring(const char **cursor) {
  char chr;
  int i;
  for (i = 0; is_digit(chr = **cursor); ++*cursor)
    i = i * 10 + chr - '0';
  return i;
}

void put_char_cursoring(char **str, struct format_info *info, va_list args) {
  if (!(info->number_flags & LEFT_ALIGMENT))
    while (--info->field_width > 0)
      *(*str)++ = ' ';
  *(*str)++ = va_arg(args, int);
  while (--info->field_width > 0)
    *(*str)++ = ' ';
}
