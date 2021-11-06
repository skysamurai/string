#include "s21_sprintf.h"

void parse_format(const char **format, struct format_info *info, va_list args) {
    info->number_system = 10;
    while(**format != '\0' && !is_specifer(**format)) {
        parse_format_flag(format, info);
        parse_field_width(format, info, args);
        parse_precision(format, info, args);
        parse_qualifier(format, info);
    }
}

void parse_format_flag(const char **format, struct format_info *info) {
    int is_found = 1;
    info->flags = 0;
    while (**format != '\0' && is_found) {
        if (**format == '-') {
            info->flags |= LEFT_JUSTIFY;
            ++(*format);
        } else if (**format == '+') {
            info->flags |= SHOW_SIGN;
            ++(*format);
        } else if (**format == ' ') {
            info->flags |= SPACE_INSTEAD_SIGN;
            ++(*format);
        } else if (**format == '#') {
            info->flags |= NUMBER_SYSTEM;
            ++(*format);
        } else if (**format == '0') {
            info->flags |= ZERO_PADDING;
            ++(*format);
        } else {
            is_found = 0;
        }
    }
}

void parse_field_width(const char **format, struct format_info *info, va_list args) {
    info->field_width = -1;
    if (is_digit(**format)) {
        info->field_width = atoi_cursoring(format);
    } else if (**format == '*') {
        ++(*format);
        info->field_width = va_arg(args, int);
        if (info->field_width < 0) {
            info->field_width = -info->field_width;
            info->flags |= LEFT_JUSTIFY;
        }
    }
}

void parse_precision(const char **format, struct format_info *info, va_list args) {
    info->precision = -1;
    if (**format == '.') {
        ++(*format);
        if (is_digit(**format)) {
            info->precision = atoi_cursoring(format);
        } else if (**format == '*') {
            ++(*format);
            info->precision = va_arg(args, int);
        }
        if (info->precision < 0) {
            info->precision = 0;
        }
    }
}

void parse_qualifier(const char **format, struct format_info *info) {
    info->qualifier = -1;
    if (**format == 'h') {
        info->qualifier = SHORT;
        (*format) += 1;
    } else if (**format == 'l' || **format == 'L') {
        info->qualifier = LONG;
        (*format) += 1;
    }
}

int is_digit(char chr) {
    return (chr >= '0') && (chr <= '9');
}

int is_specifer(char chr) {
    int result = 0;
    if (chr == 'L' || chr == 'l' || chr == 'h' || chr == '%') {
        result = 0;
    } else if (chr > 'A' && chr < 'Z' || chr > 'a' && chr < 'z') {
        result = 1;
    }
    return result;
}

int get_digit_count(int number) {
    int len = 0;
    while (number % 10) {
        number /= 10;
        len++;
    }
    return len;
}

int is_hexdec_digit(char chr) {
    return ((is_digit(chr)) || ((chr >= 'a') && (chr <= 'f')) || ((chr >= 'A') && (chr <= 'F')));
}

int atoi_cursoring(const char **cursor) {
    char chr;
    int i;
    for (i = 0; is_digit(chr = **cursor); ++ * cursor)
        i = i * 10 + chr - '0';
    return i;
}

void getSEM(unsigned int *sign, unsigned int *exponent, unsigned long long *mantiss, double number) {
    unsigned long long *pnumber = (unsigned long long *) & number;
    *mantiss = *pnumber & 0xFFFFFFFFFFFFF; /* fifty two '1' */
    *exponent = (*pnumber >> 52) & 0x3FF;
    *sign = (*pnumber >> (63)) & 1;
}
