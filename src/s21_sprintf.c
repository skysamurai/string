

#include "s21_sprintf.h"

int s21_sprintf(char *str, const char *format, va_list args) {

  struct format_info info;

  char* buf_string;
  char *s_cursor = str;
  const char *f_cursor = format;

  for(s_cursor, f_cursor; *f_cursor != '\0'; ++f_cursor) {

    if(*f_cursor != '%') {
      *s_cursor++ = *f_cursor;
      continue;
    }

    parse_format_flag(&f_cursor, &info, args);
    parse_field_width(&f_cursor, &info, args);
    parse_precision(&f_cursor, &info, args);
    parse_qualifier(&f_cursor, &info, args);

    info.number_system = 10;
    if(*f_cursor == 'c') {
      put_char_cursoring(&s_cursor, &info, args);
    } else if(*f_cursor == 's') {
      put_string_cursoring(&s_cursor, &info, args);
    } else if(*f_cursor == 'p') {
      put_pointer_cursoring(&s_cursor, &info, args);
    } else if(*f_cursor == 'n') {
      write_count_writen_char(s_cursor - str, &info, args);
    } else if(*f_cursor == '%') {
      *s_cursor++ = '%';
    } else if(*f_cursor == 'o') {
      put_octo_number_cursoring(&s_cursor, &info, args);
    } else if(*f_cursor == 'X') {
      info.number_flags |= CAPITALIZE;
      put_hex_number_cursoring(&s_cursor, &info, args);
    } else if(*f_cursor == 'x') {
      put_hex_number_cursoring(&s_cursor, &info, args);
    } else if(*f_cursor == 'd' || *f_cursor == 'i') {
      put_dec_number_cursoring(&s_cursor, &info, args);
    } else if(*f_cursor == 'u') {
      put_udec_number_cursoring(&s_cursor, &info, args);
    } else if(*f_cursor == 'e') {

    } else if(*f_cursor == 'E') {

    } else if(*f_cursor == 'g' || *f_cursor == 'G') {

    } if (*f_cursor == 'f') {

    }
  }
  *s_cursor = '\0';
  return s_cursor - str;
}

void parse_format_flag(const char **format, struct format_info *info, va_list args) {
  int is_found = 1;
  info->number_flags = 0;
  while(**format && is_found) {
    ++(*format);
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
      info->number_flags |= SHOW_NUMBER_SYSTEM;
    }
    else if(**format == '0') {
      info->number_flags |= ZERO_PADDING;
    } else {
      is_found = 0;
    }
  }
}

void parse_field_width(const char **format, struct format_info *info, va_list args) {
  info->field_width = -1;
  if(is_digit(**format)) {
    info->field_width = atoi_cursoring(format);
  } else if (**format == '*') {
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
  if(**format == 'l' && *(*format + 1) == 'l') {
    info->qualifier = LONG_LONG;
    (*format) += 2;
  } else if(**format == 'h') {
    info->qualifier = SHORT;
    (*format) += 1;
  } else if(**format == 'l') { 
    info->qualifier = LONG;
    (*format) += 1;
  } else if(**format == 'L') {
    info->qualifier = LONG_DOUBLE;
    (*format) += 1;
  }
}

void write_count_writen_char(char element_count, struct format_info *info, va_list args) {
  void *number = va_arg(args, void *);
  if(info->qualifier == LONG_LONG) {
    *((long long *)number) = (long long)(element_count);
  } else if(info->qualifier == SHORT) {
    *((short *)number) = (short)(element_count);
  } else if(info->qualifier == LONG) {
    *((long *)number) = (long)(element_count);
  } else if(info->qualifier == LONG_DOUBLE) {
    *((long double*)number) = (long double)(element_count);
  }
}

int is_digit(char chr) {
  return (chr >= '0') && (chr <= '9');
}

int is_hexdec_digit(char chr) {
  return is_digit(chr) || (chr >= 'a') && (chr <= 'f') || (chr >= 'A') && (chr <= 'F');
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

void put_string_cursoring(char **str, struct format_info *info, va_list args) {
  const char *buf_string;
  int string_len;

  buf_string = va_arg(args, char *);

  if(!buf_string)
    buf_string = "(null)";

  string_len = strlen(buf_string);

  if (!(info->number_flags & LEFT_ALIGMENT))
    while (string_len < info->field_width--)
      *(*str)++ = ' ';
  for (int i = 0; i < string_len; ++i)
    *(*str)++ = *buf_string++;
  while (string_len < info->field_width--)
    *(*str)++ = ' ';
}

void put_pointer_cursoring(char **str, struct format_info *info, va_list args) {
  info->number_system = 16;
  info->number_flags |= SHOW_NUMBER_SYSTEM;
  info->number_flags |= SIGNED;
  int_number_to_char(str, (unsigned long long) va_arg(args, void *), info);
}

void put_hex_number_cursoring(char **str, struct format_info *info, va_list args) {
  info->number_system = 16;
  int_number_to_char(str, (unsigned long long) va_arg(args, void *), info);
}

void put_dec_number_cursoring(char **str, struct format_info *info, va_list args) {
  info->number_system = 10;
  info->number_flags |= SIGNED;
  int_number_to_char(str, (unsigned long long) va_arg(args, void *), info);
}

void put_udec_number_cursoring(char **str, struct format_info *info, va_list args) {
  info->number_system = 10;
  info->number_flags &= ~SIGNED;
  int_number_to_char(str, (unsigned long long) va_arg(args, void *), info);
}

void put_octo_number_cursoring(char **str, struct format_info *info, va_list args) {
  info->number_system = 8;
  int_number_to_char(str, (unsigned long long) va_arg(args, void *), info);
}

void int_number_to_char(char **str, unsigned long long int number, struct format_info *info) {
  int signed_number = (signed long long int)number;
  char chr;
  char sign;
  char tmp[64];
  const char *digits_template; /* numbers from 0 to Z */
  int i;

  if(info->number_flags & CAPITALIZE) {
    digits_template = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  } else {
    digits_template = "0123456789abcdefghijklmnopqrstuvwxyz";
  }

  if(info->number_flags & LEFT_ALIGMENT) {
    info->number_flags &= ~ZERO_PADDING;
  }

  if (info->number_system < 2 || info->number_system > 36) {
    return;
  }

  chr = (info->number_flags & ZERO_PADDING) ? '0' : ' ';

  sign = '\0';

  /* get sign of number */
  if(info->number_flags & SIGNED) {
    if((signed)number < 0) {
      sign = '-';
      number = - (signed)number;
      info->field_width--;
    } else if(info->number_flags & SHOW_SIGN ) {
      sign = '+';
      info->field_width--;
    } else if(info->number_flags & REPLACE_SIGN_SPACE) {
      sign = ' ';
      info->field_width--;
    }
  }

  /* In the hexadecimal number system 
  two characters are assigned to "0x" */
  if(info->number_flags & SHOW_NUMBER_SYSTEM) {
    if (info->number_system == 16) {
      info->field_width -= 2;
    } else if(info->number_system == 8) {
      info->field_width -= 1;
    }
  }

  i = 0;
  if (number == 0)
    tmp[i++]='0';
  else while(number != 0) {
    tmp[i++] = digits_template[number % info->number_system];
    number = number / info->number_system;
  }

  if(i > info->precision) {
    info->precision = i;
  }

  info->field_width -= info->precision;

  if(!(info->number_flags & (ZERO_PADDING | LEFT_ALIGMENT))) {
    while(info->field_width-- > 0) {
      *(*str)++ = ' ';
    }
  }

  if(sign != '\0') {
    *(*str)++ = sign;
  }

  if(info->number_flags & SHOW_NUMBER_SYSTEM) {
    if (info->number_system == 16) {
      *(*str)++ = '0';
      *(*str)++ = digits_template[33];
    } else if (info->number_system == 8) {
      *(*str)++ = '0';
    }
  }

  if(!(info->number_flags & LEFT_ALIGMENT)) {
    while(info->field_width-- > 0) {
      *(*str)++ = chr;
    }
  }

  while(i < info->precision--) {
    *(*str)++ = '0';
  }

  while(i-- > 0) {
    *(*str)++ = tmp[i];
  }

  while (info->field_width-- > 0)
    *(*str)++ = ' ';
}

void real_number_to_char(char **str, long double number, struct format_info *info) {
  char chr;
  char sign;
  char tmp[64];
  char digits[] = "0123456789";
  
}
