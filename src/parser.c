#include <stdarg.h>
#include "parser.h"

void parse_format(const char **format, format_info *info, va_list args) {
    info->number_system = 10;
    p_flag(format, info);
    p_width(format, info, args);
    p_precision(format, info, args);
    p_qualifier(format, info);
}

void p_flag(const char **format, format_info *info) {
    int is_found = 0;
    info->flags = 0;
    while (**format != '\0' && !is_found) {
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
            is_found = 1;
        }
    }
}

void p_width(const char **format, format_info *info, va_list args) {
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

void p_precision(const char **format, format_info *info, va_list args) {
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
            info->precision = -1;
        }
    }
}

void p_qualifier(const char **format, format_info *info) {
    info->qualifier = NONE;
    if (**format == 'h' || **format == 'f') {
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

int get_dec_digit_count(int number) {
    number = number >= 0 ? number : -number;
    int len = 0;
    while (number) {
        len++;
        number /= 10;
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
