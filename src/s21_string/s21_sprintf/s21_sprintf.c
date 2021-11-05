#include "s21_sprintf.h"
#include "../s21_string.h"
#include "math.h"

int s21_sprintf(char *str, const char *format, va_list args) {
    struct format_info info;
    char *percent_pointer;

    char *s_cursor = str; /* string cursor */
    const char *f_cursor = format;

    while (f_cursor != S21_NULL) {
        percent_pointer = strpbrk(f_cursor, "%");
        if (percent_pointer != S21_NULL) {
            memcpy(s_cursor, f_cursor, percent_pointer - f_cursor + 1);
            s_cursor += percent_pointer - f_cursor;
            f_cursor += s_cursor - str;
        } else {
            memcpy(s_cursor, f_cursor, strlen(f_cursor));
            s_cursor += strlen(f_cursor);
            *s_cursor = '\0';
            f_cursor = S21_NULL;
        }

        if (*s_cursor != '\0') {
            parse_format(&f_cursor, &info, args);
            if (*f_cursor == 'c') {
                put_char_cursoring(&s_cursor, &info, args);
            } else if (*f_cursor == 's') {
                put_string_cursoring(&s_cursor, &info, args);
            } else if (*f_cursor == 'p') {
                put_pointer_cursoring(&s_cursor, &info, args);
            } else if (*f_cursor == 'n') {
                write_count_recorded_char(s_cursor - str, &info, args);
            } else if (*f_cursor == '%') {
                *s_cursor++ = '%';
            } else if (*f_cursor == 'o') {
                put_octo_number_cursoring(&s_cursor, &info, args);
            } else if (*f_cursor == 'X') {
                info.flags |= CAPITALIZE;
                put_hex_number_cursoring(&s_cursor, &info, args);
            } else if (*f_cursor == 'x') {
                put_hex_number_cursoring(&s_cursor, &info, args);
            } else if (*f_cursor == 'd' || *f_cursor == 'i') {
                put_dec_number_cursoring(&s_cursor, &info, args);
            } else if (*f_cursor == 'u') {
                put_udec_number_cursoring(&s_cursor, &info, args);
            } else if (*f_cursor == 'e') {
                info.flags |= EXPONENT;
                real_number_to_char(&s_cursor, va_arg(args, double), &info);
            } else if (*f_cursor == 'E') {

            } else if (*f_cursor == 'g' || *f_cursor == 'G') {

            }
            if (*f_cursor == 'f') {
                f_cursor++;
            }
        }
    }
    return s_cursor - str;
}

void write_count_recorded_char(char element_count, struct format_info *info,
    va_list args) {
    void *number = va_arg(args, void *);
    if (info->qualifier == SHORT) {
        *((short *)number) = (short)(element_count);
    } else if (info->qualifier == LONG) {
        *((long *)number) = (long)(element_count);
    } else if (info->qualifier == LONG_DOUBLE) {
        *((long double *)number) = (long double)(element_count);
    }
}

void put_char_cursoring(char **str, struct format_info *info, va_list args) {
    if (!(info->flags & LEFT_JUSTIFY))
        while (--info->field_width > 0) *(*str)++ = ' ';
    *(*str)++ = va_arg(args, int);
    while (--info->field_width > 0) *(*str)++ = ' ';
}

void put_string_cursoring(char **str, struct format_info *info, va_list args) {
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

void put_pointer_cursoring(char **str, struct format_info *info, va_list args) {
    info->number_system = 16;
    info->flags |= NUMBER_SYSTEM;
    info->flags |= SIGNED;
    int_number_to_char(str, (unsigned long long)va_arg(args, void *), info);
}

void put_hex_number_cursoring(char **str, struct format_info *info,
    va_list args) {
    info->number_system = 16;
    int_number_to_char(str, (unsigned long long)va_arg(args, void *), info);
}

void put_dec_number_cursoring(char **str, struct format_info *info,
    va_list args) {
    info->number_system = 10;
    info->flags |= SIGNED;
    int_number_to_char(str, (unsigned long long)va_arg(args, void *), info);
}

void put_udec_number_cursoring(char **str, struct format_info *info,
    va_list args) {
    info->number_system = 10;
    info->flags &= ~SIGNED;
    int_number_to_char(str, (unsigned long long)va_arg(args, void *), info);
}

void put_octo_number_cursoring(char **str, struct format_info *info,
    va_list args) {
    info->number_system = 8;
    int_number_to_char(str, (unsigned long long)va_arg(args, void *), info);
}

void int_number_to_char(char **str, unsigned long number,
    struct format_info *info) {
    char aggregate;
    char sign;
    char tmp[64];
    const char *digits_template;
    int i = sizeof(short int);

    if (info->flags & CAPITALIZE) {
        digits_template = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    } else {
        digits_template = "0123456789abcdefghijklmnopqrstuvwxyz";
    }

    /* left alignment has a higher priority than zero padding */
    if (info->flags & LEFT_JUSTIFY) {
        info->flags &= ~ZERO_PADDING;
    }

    aggregate = (info->flags & ZERO_PADDING) ? '0' : ' ';

    /* get the sign of a number */
    sign = '\0';
    if (info->flags & SIGNED) {
        if ((signed long)number < 0) {
            sign = '-';
            number = -(signed long long)number;
            info->field_width--;
        } else if (info->flags & SHOW_SIGN) {
            sign = '+';
            info->field_width--;
        } else if (info->flags & SPACE_INSTEAD_SIGN) {
            sign = ' ';
            info->field_width--;
        }
    }

    /* In the 16 number system
    two characters are assigned to "0x",
    in 8 number system to 0 */
    if (info->flags & NUMBER_SYSTEM) {
        if (info->number_system == 16) {
            info->field_width -= 2;
        } else if (info->number_system == 8) {
            info->field_width -= 1;
        }
    }

    /* put the number int the buffer */
    i = 0;
    if (info->number_system & SIGNED) {
        if (number == 0) {
            tmp[i++] = '0';
        } else {
            while (number != 0) {
                tmp[i++] = digits_template[number % info->number_system];
                number = number / info->number_system;
            }
        }
    } else {
        if (number == 0) {
            tmp[i++] = '0';
        } else {
            while ((int)number != 0) {
                tmp[i++] = digits_template[-(int)(signed long long)number % info->number_system];
                number = -(int)(signed long long)number / info->number_system;
            }
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

void real_number_to_char(char **str, double number, struct format_info *info) {
    int digit;

    int i;
    char exponent_sign;
    int exponent_len;
    int exponent_val;
    char aggregate;
    char sign;

    char tmp[64] = { '\0' };

    sign = '\0';
    if (number < 0) {
        sign = '-';
        info->field_width--;
    } else if (info->flags & SHOW_SIGN) {
        sign = '+';
        info->field_width--;
    } else if (info->flags & SPACE_INSTEAD_SIGN) {
        sign = ' ';
        info->field_width--;
    }

    if (info->flags & LEFT_JUSTIFY) {
        info->flags &= ~ZERO_PADDING;
    }
    aggregate = (info->flags & ZERO_PADDING) ? '0' : ' ';

    if (info->flags & (EXPONENT | FLOAT)) {
        if (info->precision >= 0) {
            info->field_width -= info->precision;
        } else {
            info->field_width -= 6;
            info->precision = 6;
        }
    }

    /* calculating exponent size */
    if (info->flags & EXPONENT) {
        exponent_val = 0;
        exponent_len = 0;

        if (number == 0.0) {
            number = 0;
            exponent_val = 0;
        } else {
            while (number >= 1.0) {
                number /= 10.0;
                ++exponent_val;
            }
            while (number < 0.1) {
                number *= 10.0;
                --exponent_val;
            }
            exponent_val--;
            number *= 10.0;
        }

        if ((exponent_len = get_digit_count(exponent_val)) < 2) {
            exponent_len = 2;
        }
        /* additional positions for service symbols */
        info->field_width -= exponent_len + 4;

        exponent_sign = exponent_val >= 0 ? '+' : '-';
        exponent_val = exponent_val >= 0 ? exponent_val : -exponent_val;

        if (sign != '\0' && (info->flags & ZERO_PADDING)) {
            *(*str)++ = sign;
        }

        if (!(info->flags & LEFT_JUSTIFY)) {
            while (info->field_width-- > 0) {
                *(*str)++ = aggregate;
            }
        }

        if (sign != '\0' && !(info->flags & ZERO_PADDING)) {
            *(*str)++ = sign;
        }

        if (number < 0) {
            *(*str)++ = '0' - (unsigned int)number;
        } else {
            *(*str)++ = '0' + (signed int)number;
        }

        if (info->precision != 0) {
            *(*str)++ = '.';
            info->field_width -= 1;
        }

        for (; info->precision > 0; info->precision--, number *= 10) {
            if ((int)number % 10 < 0) {
                *(*str)++ = '0' + ((unsigned int)number % 10);
            } else {
                *(*str)++ = '0' + (signed int)number % 10;
            }
        }

        *(*str)++ = 'e';
        *(*str)++ = exponent_sign;

        if (exponent_val == 0) {
            *(*str)++ = '0';
            *(*str)++ = '0';
        } else {
            if (exponent_val < 9) {
                *(*str)++ = '0';
            }
            for (i = 0; exponent_val > 0; ++i) {
                tmp[i] = '0' + exponent_val % 10;
                exponent_val /= 10;
            }
            while (i > 0) {
                *(*str)++ = tmp[(i--) - 1];
            }

        }

        while (info->field_width-- > 0) {
            *(*str)++ = aggregate;
        }
    }
}
