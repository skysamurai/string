#include "s21_sprintf.h"

#include <limits.h>
#include <stdlib.h>

#include "parser.h"
#include "s21_string.h"

int s21_sprintf_(char *str, const char *format, va_list args) {
    format_info f_info;
    char *percent_pointer;

    char *s_cursor = str;          /* string cursor */
    const char *f_cursor = format; /*format cursor */

    while (f_cursor != S21_NULL) {
        percent_pointer = strchr(f_cursor, '%'); /* stdlib, wait for s21 */
        if (percent_pointer != S21_NULL) {
            s21_memcpy(s_cursor, f_cursor,
                       sizeof(char) * (percent_pointer - f_cursor));
            s_cursor += percent_pointer - f_cursor;
            f_cursor += percent_pointer - f_cursor + 1;
        } else {
            s21_memcpy(s_cursor, f_cursor, s21_strlen(f_cursor));
            s_cursor += s21_strlen(f_cursor);
            *s_cursor = '\0';
            f_cursor = S21_NULL;
        }

        if (f_cursor != S21_NULL && *f_cursor != '\0') {
            parse_format(&f_cursor, &f_info, args);
            if (*f_cursor == 'c') {
                put_char_cursoring(&s_cursor, &f_info, args);
            } else if (*f_cursor == 's') {
                put_string_cursoring(&s_cursor, &f_info, args);
            } else if (*f_cursor == 'p') {
                put_pointer_cursoring(&s_cursor, &f_info, args);
            } else if (*f_cursor == 'n') {
                write_count_recorded_char(s_cursor - str, &f_info, args);
            } else if (*f_cursor == '%') {
                *s_cursor++ = '%';
            } else if (*f_cursor == 'o') {
                put_octo_number_cursoring(&s_cursor, &f_info, args);
            } else if (*f_cursor == 'X') {
                f_info.flags |= CAPITALIZE;
                put_hex_number_cursoring(&s_cursor, &f_info, args);
            } else if (*f_cursor == 'x') {
                put_hex_number_cursoring(&s_cursor, &f_info, args);
            } else if (*f_cursor == 'd' || *f_cursor == 'i') {
                f_info.flags |= SIGNED;
                put_dec_number_cursoring(&s_cursor, &f_info, args);
            } else if (*f_cursor == 'u') {
                put_udec_number_cursoring(&s_cursor, &f_info, args);
            } else if (*f_cursor == 'e') {
                f_info.flags |= SIGNED;
                f_info.flags |= EXPONENT;
                real_number_to_char(&s_cursor, va_arg(args, double), &f_info);
            } else if (*f_cursor == 'E') {
            } else if (*f_cursor == 'g' || *f_cursor == 'G') {
            } else if (*f_cursor == 'f') {
            }
            f_cursor++;
        }
    }
    return s_cursor - str;
}

/* for some reason, the standard
 * function on ubuntu does not handle
 * the 'l' width flag when my function
 * handles this flag. As a result,
 * the number of recorded bits
 * is not counted */
void write_count_recorded_char(s21_size_t record_count, format_info *info,
                               va_list args) {
    void *number = va_arg(args, void *);
    if (info->qualifier == NONE) {
        *((int *)number) = (int)record_count;
    } else if (info->qualifier == SHORT) {
        *((short *)number) = (short)(record_count);
    } else if (info->qualifier == LONG) {
        *((long *)number) = (long)(record_count);
    }
}

void put_char_cursoring(char **str, format_info *info, va_list args) {
    if (!(info->flags & LEFT_JUSTIFY))
        while (--info->field_width > 0) *(*str)++ = ' ';
    *(*str)++ = va_arg(args, int);
    while (--info->field_width > 0) *(*str)++ = ' ';
}

void put_string_cursoring(char **str, format_info *info, va_list args) {
    const char *buf_string;
    int string_len;

    buf_string = va_arg(args, char *);

    if (!buf_string) buf_string = "(null)";

    string_len = strlen(buf_string);

    if (!(info->flags & LEFT_JUSTIFY))
        while (string_len < info->field_width--) *(*str)++ = ' ';
    for (int i = 0; i < string_len; ++i) *(*str)++ = *buf_string++;
    while (string_len < info->field_width--) *(*str)++ = ' ';
}

void put_pointer_cursoring(char **str, format_info *info, va_list args) {
    info->number_system = 16;
    info->flags |= NUMBER_SYSTEM;
    info->flags |= SIGNED;
    int_number_to_char(str, (long)va_arg(args, void *), info);
}

void put_hex_number_cursoring(char **str, format_info *info, va_list args) {
    info->number_system = 16;
    info->flags &= ~SIGNED;
    info->flags |= UNSIGNED;
    int_number_to_char(str, (long)va_arg(args, void *), info);
}

void put_dec_number_cursoring(char **str, format_info *info, va_list args) {
    info->number_system = 10;
    info->flags |= SIGNED;
    int_number_to_char(str, (long)va_arg(args, void *), info);
}

void put_udec_number_cursoring(char **str, format_info *info, va_list args) {
    info->number_system = 10;
    info->flags &= ~SIGNED;
    info->flags |= UNSIGNED;
    int_number_to_char(str, (long)va_arg(args, void *), info);
}

void put_octo_number_cursoring(char **str, format_info *info, va_list args) {
    info->flags &= ~SIGNED;
    info->flags |= UNSIGNED;
    info->number_system = 8;
    int_number_to_char(str, (long)va_arg(args, void *), info);
}

void int_number_to_char(char **str, unsigned long number, format_info *info) {
    char aggregate;
    char sign;
    char tmp[32];
    const char *digits_template;
    int i;

    /* select the character output case */
    if (info->flags & CAPITALIZE) {
        digits_template = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    } else {
        digits_template = "0123456789abcdefghijklmnopqrstuvwxyz";
    }

    /* left alignment has a higher priority than zero padding */
    if (info->flags & LEFT_JUSTIFY) {
        info->flags &= ~ZERO_PADDING;
    }

    if (info->flags & ZERO_PADDING) {
        aggregate = '0';
    } else {
        aggregate = ' ';
    }

    /* get the sign of a number
     * sign priority
     * ' ' > '+'
     * ' ' > '-'
     * If the number has a - sign,
     * then the minus sign is output in
     * any case, except for unsigned numbers.
     */
    sign = '\0';
    if (info->flags & SIGNED) {
        if (info->qualifier == SHORT && ((short)number) < 0) {
            number = -(short)number;
            sign = '-';
            info->field_width--;
        } else if (info->qualifier == NONE && ((int)number) < 0) {
            sign = '-';
            info->field_width--;
            number = -(int)number;
        } else if (info->qualifier == LONG && ((long)number) < 0) {
            sign = '-';
            info->field_width--;
            number = -(long)number;
        } else if (info->flags & SHOW_SIGN) {
            sign = '+';
            info->field_width--;
        } else if (info->flags & SPACE_INSTEAD_SIGN) {
            sign = ' ';
            info->field_width--;
        }
    } else {
        if (info->qualifier == SHORT) {
            number = (unsigned short)number;
        } else if (info->qualifier == NONE) {
            number = (unsigned int)number;
        } else if (info->qualifier == LONG) {
            number = (unsigned long)number;
        }
    }

    /* In the 16 number system
    two characters are assigned to "0x",
    in 8 number system to '0' */
    if (info->flags & NUMBER_SYSTEM) {
        if (info->number_system == 16) {
            info->field_width -= 2;
        } else if (info->number_system == 8) {
            info->field_width -= 1;
        }
    }

    /* put the number int the buffer */
    i = 0;
    if (number == 0) {
        tmp[i++] = '0';
    } else {
        while (number != 0) {
            tmp[i++] = digits_template[number % info->number_system];
            number = number / info->number_system;
        }
    }

    if (i > info->precision) {
        info->precision = i;
    }
    info->field_width -= info->precision;

    if (!(info->flags & (ZERO_PADDING | LEFT_JUSTIFY))) {
        while (info->field_width-- > 0) {
            *(*str)++ = ' ';
        }
    }

    if (sign != '\0') {
        *(*str)++ = sign;
    }

    if (info->flags & NUMBER_SYSTEM) {
        if (info->number_system == 16) {
            *(*str)++ = '0';
            *(*str)++ = digits_template[33];
        } else if (info->number_system == 8) {
            *(*str)++ = '0';
        }
    }

    if (!(info->flags & LEFT_JUSTIFY)) {
        while (info->field_width-- > 0) {
            *(*str)++ = aggregate;
        }
    }

    while (i < info->precision--) {
        *(*str)++ = '0';
    }

    while (i-- > 0) {
        *(*str)++ = tmp[i];
    }

    while (info->field_width-- > 0) {
        *(*str)++ = ' ';
    }
}

void real_number_to_char(char **str, double number, format_info *info) {
    char *actualStr = *str;
    int exponent;
    int exponentSign;
    int sign;
    int _precision = info->precision != -1 ? info->precision : 6;
    char *out;
    // TODO: maximum precision number? compiler/system dependency?
    // own fcvt implementation?
    out = fcvt(number, INT16_MAX, &exponent, &sign);

    if (exponent >= 0)
        exponentSign = 0;
    else
        exponentSign = -1;

    exponent = abs(exponent);
    if (exponentSign == 0)
        exponent--;
    else
        exponent++;

    if (sign != 0) *(*str)++ = '-';

    int i = 0;
    for (i = 0; out[i] != 0 && i <= _precision; i++) {
        if (i == 1) *(*str)++ = '.';
        *(*str)++ = out[i];
    }
    while (i <= _precision) {
        *(*str)++ = '0';
        i++;
    }

    *(*str)++ = 'e';
    *(*str)++ = exponentSign == 0 ? '+' : '-';
    if (exponent < 10) *(*str)++ = '0';
    if (exponent == 0) *(*str)++ = '0';
    char exponentStr[128] = {0};
    i = 126;
    while (exponent != 0) {
        exponentStr[i--] = (exponent % 10) + '0';
        exponent /= 10;
    }
    i++;
    while (i <= 126) {
        *(*str)++ = exponentStr[i];
        i++;
    }
}
