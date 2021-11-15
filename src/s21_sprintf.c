#include "s21_sprintf.h"

#include <limits.h>
#include <stdlib.h>

#include "parser.h"
#include "s21_string.h"

int s21_sprintf_(char *str, const char *format, va_list args) {
    format_info f_info;
    char *percent_pos;

    char *s_cursor = str;
    const char *f_cursor = format;

    while (f_cursor != S21_NULL) {
        // if the percent symbol is found,
        // copy the string until percent symbol
        // otherwise,
        // copy full string
        percent_pos = strchr(f_cursor, '%');
        if (percent_pos != S21_NULL) {
            s21_memcpy(s_cursor, f_cursor,
                       sizeof(char) * (percent_pos - f_cursor));
            s_cursor += percent_pos - f_cursor;
            f_cursor += percent_pos - f_cursor + 1;
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
                f_info.flags |= CAPITALIZE;
                f_info.flags |= SIGNED;
                f_info.flags |= EXPONENT;
                real_number_to_char(&s_cursor, va_arg(args, double), &f_info);
            } else if (*f_cursor == 'g' || *f_cursor == 'G') {
            } else if (*f_cursor == 'f') {
                f_info.flags |= CAPITALIZE;
                f_info.flags |= SIGNED;
                f_info.flags |= EXPONENT;
            }
            f_cursor++;
        }
    }
    return s_cursor - str;
}

// for some reason, the standard
// function on ubuntu does not handle
// the 'l' width flag when my function
// handles this flag. As a result,
// the number of recorded bits
// is not counted
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
    info->flags |= UNSIGNED;
    info->qualifier = LONG;
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
    char number_sign;
    char tmp[32];
    const char *digits_template;
    int i;

    // select the character output case
    if (info->flags & CAPITALIZE) {
        digits_template = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    } else {
        digits_template = "0123456789abcdefghijklmnopqrstuvwxyz";
    }

    // left alignment has a higher priority than zero padding
    if (info->flags & LEFT_JUSTIFY || info->precision > 0) {
        info->flags &= ~ZERO_PADDING;
    }

    if (info->flags & ZERO_PADDING) {
        aggregate = '0';
    } else {
        aggregate = ' ';
    }

    number_sign = '\0';
    if (info->flags & SIGNED) {
        if (info->qualifier == SHORT && ((short)number) < 0) {
            number = -(short)number;
            number_sign = '-';
            info->field_width--;
        } else if (info->qualifier == NONE && ((int)number) < 0) {
            number_sign = '-';
            info->field_width--;
            number = -(int)number;
        } else if (info->qualifier == LONG && ((long)number) < 0) {
            number_sign = '-';
            info->field_width--;
            number = -(long)number;
        } else if (info->flags & SHOW_SIGN) {
            number_sign = '+';
            info->field_width--;
        } else if (info->flags & SPACE_INSTEAD_SIGN) {
            number_sign = ' ';
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
        if (info->flags & SHOW_SIGN) {
            number_sign = '+';
            info->field_width--;
        }
    }

    // in the 16 number system
    // two characters are assigned to "0x",
    // in 8 number system to '0'
    if (info->flags & NUMBER_SYSTEM) {
        if (info->number_system == 16) {
            info->field_width -= 2;
        } else if (info->number_system == 8) {
            info->field_width -= 1;
        }
    }

    // put the number int the buffer
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

    if (number_sign != '\0') {
        *(*str)++ = number_sign;
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
    int i;

    int number_sign;
    char cnumber_sign;

    int exponent;
    char exponent_sign;

    char placeholder;

    char exponent_reverse[64] = {0};

    // it is needed to understand
    // the state of variables.
    // if >= 0, user`s precision
    // else if == -1, no user`s precision
    // else user`s 0 prcision
    if (info->precision > 0) {
        info->field_width -= info->precision;
    } else if (info->precision == -1) {
        info->precision = 6;
        info->field_width -= info->precision;
    } else {
        info->precision = 0;
        info->field_width -= info->precision;
    }

    char *cnumber = ecvt(number, info->precision + 1, &exponent, &number_sign);

    // left alignment has a higher priority
    // than filling empty space with zeros
    if (info->flags & LEFT_JUSTIFY) {
        info->flags &= ~ZERO_PADDING;
    }
    placeholder = (info->flags & ZERO_PADDING) ? '0' : ' ';

    cnumber_sign = '\0';
    if (number_sign != 0) {
        cnumber_sign = '-';
        info->field_width--;
    } else if (info->flags & SHOW_SIGN) {
        cnumber_sign = '+';
        info->field_width--;
    } else if (info->flags & SPACE_INSTEAD_SIGN) {
        cnumber_sign = ' ';
        info->field_width--;
    }

    // 1 sign required for "."
    info->field_width -= 1;

    // The minimum exponent size is 2 digits,
    // the maximum is 3.
    // 2 digits are obtained if the number of digits
    // in the exponent is from 0-2 (example: e+00, e+05, e+59),
    // otherwise 3 (example e+100, e+305)
    if (get_dec_digit_count(exponent) <= 2) {
        info->field_width -= 2;
    } else {
        info->field_width -= 3;
    }

    // normalized part always takes 1 character
    info->field_width -= 1;

    // The exponent always has a sign,
    // so we don't have to equate it to zero
    if (exponent > 0) {
        exponent_sign = '+';
        exponent -= 1;
    } else {
        exponent_sign = '-';
        exponent = -exponent;
        exponent += 1;
    }

    // 1 sign is assigned to the exponent "e",
    // 1 sign is assigned to the exponent sign
    //  "+" or "-"
    info->field_width -= 2;

    // if ZERO_PADDING (example: 000005e+5) and we have a sign,
    // first print the sign, then zeros (example: +000005e+5)
    if (cnumber_sign != '\0' && (info->flags & ZERO_PADDING)) {
        *(*str)++ = cnumber_sign;
    }

    // if there is no left alignment, first prints the placeholder
    // " " (in the logic of the program above, we get a placeholder sign)
    // or "0" for ZERO_PADDING
    if (!(info->flags & LEFT_JUSTIFY)) {
        while (info->field_width-- > 0) {
            *(*str)++ = placeholder;
        }
    }

    // if there is a sign and if there are no zeros,
    // then you can output the sign of the number
    if (cnumber_sign != '\0' && !(info->flags & ZERO_PADDING)) {
        *(*str)++ = cnumber_sign;
    }

    // output of a normalized number
    *(*str)++ = *cnumber++;

    // put dot after normalized number
    if (info->flags & NUMBER_SYSTEM || info->precision != 0)
        *(*str)++ = '.';

    // mantiss output
    for (; info->precision > 0; --info->precision, number *= 10) {
        *(*str)++ = *cnumber++;
    }

    // exponent output
    if (info->flags & CAPITALIZE) {
        *(*str)++ = 'E';
    } else {
        *(*str)++ = 'e';
    }

    *(*str)++ = exponent_sign;

    if (exponent == 0) {
        *(*str)++ = '0';
        *(*str)++ = '0';
    } else {
        if (exponent <= 9) {
            *(*str)++ = '0';
        }
        for (i = 0; exponent > 0; ++i) {
            exponent_reverse[i] = '0' + exponent % 10;
            exponent /= 10;
        }
        while (i > 0) {
            *(*str)++ = exponent_reverse[(i--) - 1];
        }
    }

    // If there is a free width left, fill in with spaces
    while (info->field_width-- > 0) {
        *(*str)++ = ' ';
    }
}
