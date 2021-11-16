#include "s21_sprintf.h"

#include <limits.h>
#include <stdlib.h>
#include <math.h>

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
                put_exp_number_cursoring(&s_cursor, &f_info, args);
            } else if (*f_cursor == 'E') {
                f_info.flags |= CAPITALIZE;
                put_exp_number_cursoring(&s_cursor, &f_info, args);
            } else if (*f_cursor == 'g' || *f_cursor == 'G') {
                f_info.qualifier = VAR_FORMAT;
                double snumber = va_arg(args, double);
                real_number_to_char(&s_cursor, (void *)&snumber, &f_info);
            } else if (*f_cursor == 'f') {
                put_flt_number_cursoring(&s_cursor, &f_info, args);
            }
            f_cursor++;
        }
    }
    return s_cursor - str;
}

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

int is_sign(char chr) {
    return chr == ' ' || chr == '+' || chr == '-';
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

    if (!(info->flags & LEFT_JUSTIFY)) {
        while (string_len < info->field_width--) { 
            *(*str)++ = ' '; 
        }
    }

    for (int i = 0; i < string_len; ++i) { 
        *(*str)++ = *buf_string++;
    }

    while (string_len < info->field_width--) {
        *(*str)++ = ' ';
    }
}

void put_pointer_cursoring(char **str, format_info *info, va_list args) {
    info->number_system = 16;
    info->flags |= SPECIAL;
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

void put_exp_number_cursoring(char **str, format_info *info, va_list args) {
    info->flags |= SIGNED;
    info->flags |= EXPONENT;
    long double dlnumber;
    double dnumber;
    if (info->qualifier == LONG) {
        dlnumber = va_arg(args, long double);
        real_number_to_char(str, (void *)&dlnumber, info);
    } else if (info->qualifier == NONE) {
        dnumber = va_arg(args, double);
        real_number_to_char(str, (void *)(&(dnumber)), info);
    }
}

void put_flt_number_cursoring(char **str, format_info *info, va_list args) {
    info->flags |= SIGNED;
    info->flags |= EXPONENT;
    float snumber = va_arg(args, double);
    real_number_to_char(str, (void *)&snumber, info);
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
    if (info->flags & SPECIAL) {
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

    if (info->flags & SPECIAL) {
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

void float_to_str(char *buffer, float number, format_info *info) {
    int number_sign;
    int exponent;
    char *number_digits;

    // i want to believe it works as it should word on Mac
    number_digits = fcvt(number, info->precision, &exponent, &number_sign);

    // inserts number sign
    if (number_sign > 0) {
        *(buffer++) = '-';
    } else if (info->flags & SHOW_SIGN) {
        *(buffer++) = '+';
    } else if (info->flags & SPACE_INSTEAD_SIGN) {
        *(buffer++) = ' ';
    }
    // insert number dot if necessary
    if (exponent <= 0) {
        *(buffer++) = '0';
        if (info->precision != 0 || info->flags & SPECIAL)
            *(buffer++) = '.';
        while (exponent++ < 0) {
            *(buffer++) = '0';
        }
    } else {
        while (exponent-- > 0) {
            *(buffer++) = *number_digits++;
        }
        if (info->precision != 0 || info->flags & SPECIAL) {
            *(buffer++) = '.';
        }
    }
    while(*number_digits != '\0') {
        *(buffer++) = *number_digits++;
    }
}

void double_to_str(char *buffer, void* number, format_info *info) {
    char *dbuf = buffer;
    int number_sign;
    int exponent;
    char *number_digits;
    char exponent_reverse[4];
    int i;


    if (info->qualifier == NONE) {
        number_digits = ecvt(*(double *)number, info->precision + 1, &exponent, &number_sign);
    } else {
        number_digits = ecvt(*(long double *)number, info->precision + 1, &exponent, &number_sign);
    }

    // insert number sign if necessary
    if (number_sign > 0) {
        *(buffer++) = '-';
    } else if (info->flags & SHOW_SIGN) {
        *(buffer++) = '+';
    } else if (info->flags & SPACE_INSTEAD_SIGN) {
        *(buffer++) = ' ';
    }
    // output of a normalized number
    *(buffer++) = *number_digits++;

    // put dot after normalized number
    if (info->flags & SPECIAL || info->precision != 0)
        *(buffer++) = '.';

    // mantiss output
    while ((info->precision)-- > 0) {
        *(buffer++) = *(number_digits++);
    }

    if (info->flags & CAPITALIZE) {
        *(buffer++) = 'E';
    } else {
        *(buffer++) = 'e';
    }

    // The exponent always has a sign,
    // so we don't have to equate it to zero
    if (exponent > 0) {
        *(buffer++) = '+';
        exponent -= 1;
    } else {
        *(buffer++) = '-';
        exponent = -exponent;
        exponent += 1;
    }

    if (exponent == 0) {
        *(buffer++) = '0';
        *(buffer++) = '0';
    } else {
        if (exponent <= 9) {
            *(buffer++) = '0';
        }
        for (i = 0; exponent > 0; ++i) {
            exponent_reverse[i] = '0' + exponent % 10;
            exponent /= 10;
        }
        while (i > 0) {
            *(buffer++) = exponent_reverse[(i--) - 1];
        }
    }

}

void real_number_to_char(char **str, void *number, format_info *info) {
    int i = 0;
    char placeholder;

    if (info->precision == -1) {
        info->precision = 6;
    }

    char str_number[512] = {0};

    // processing numbers by type
    if (info->qualifier == NONE || info->qualifier == LONG) {
        double_to_str(str_number, number, info);
    } else if (info->qualifier == SHORT) {
        float_to_str(str_number, *((float *)number), info);
    }

    info->field_width -= s21_strlen(str_number);

    if (info->flags & LEFT_JUSTIFY) {
        info->flags &= ~ZERO_PADDING;
    }

    if (info->flags & ZERO_PADDING) {
        if (is_sign(str_number[i])) {
            *(*str)++ = str_number[i++];
        }
        while (info->field_width-- > 0) {
            *(*str)++ = '0';
        }
    }

    if (!(info->flags & LEFT_JUSTIFY)) {
        while (info->field_width-- > 0) {
                *(*str)++ = ' ';
        }
    }

    while (str_number[i] != '\0') {
        *(*str)++ = str_number[i++];
    }

    while (info->field_width-- > 0) {
            *(*str)++ = ' ';
    }
}

/* if(1) {
    // if (info->qualifier == SHORT && exponent <= 0) {
    //     info->field_width += (exponent - 1);
    // }

    // // left alignment has a higher priority
    // // than filling empty space with zeros
    // if (info->flags & LEFT_JUSTIFY) {
    //     info->flags &= ~ZERO_PADDING;
    // }
    // placeholder = (info->flags & ZERO_PADDING) ? '0' : ' ';

    // char_number_sign = '\0';
    // if (number_sign != 0) {
    //     char_number_sign = '-';
    //     info->field_width--;
    // } else if (info->flags & SHOW_SIGN) {
    //     char_number_sign = '+';
    //     info->field_width--;
    // } else if (info->flags & SPACE_INSTEAD_SIGN) {
    //     char_number_sign = ' ';
    //     info->field_width--;
    // }

    // if ((info->flags & SPECIAL || info->precision > 0) && len == -1) {
    //     info->field_width--;
    // }

    // // The minimum exponent size is 2 digits,
    // // the maximum is 3.
    // // 2 digits are obtained if the number of digits
    // // in the exponent is from 0-2 (example: e+00, e+05, e+59),
    // // otherwise 3 (example e+100, e+305)
    // if (info->qualifier != SHORT) {
    //     if (get_dec_digit_count(exponent) <= 2) {
    //         info->field_width -= 2;
    //     } else {
    //         info->field_width -= 3;
    //     }

    //     // 1 sign is assigned to the exponent "e",
    //     // 1 sign is assigned to the exponent sign
    //     //  "+" or "-"
    //     info->field_width -= 2;
    // }


    // // if ZERO_PADDING (example: 000005e+5) and we have a sign,
    // // first print the sign, then zeros (example: +000005e+5)
    // if (char_number_sign != '\0' && (info->flags & ZERO_PADDING)) {
    //     *(*str)++ = char_number_sign;
    // }

    // // if there is no left alignment, first prints the placeholder
    // // " " (in the logic of the program above, we get a placeholder sign)
    // // or "0" for ZERO_PADDING
    // if (!(info->flags & LEFT_JUSTIFY)) {
    //     while (info->field_width-- > 0) {
    //         *(*str)++ = placeholder;
    //     }
    // }

    // // if there is a sign and if there are no zeros,
    // // then you can output the sign of the number
    // if (char_number_sign != '\0' && !(info->flags & ZERO_PADDING)) {
    //     *(*str)++ = char_number_sign;
    // }

    // if (info->qualifier != SHORT) {
    //     // output of a normalized number
    //     *(*str)++ = *number_digits++;

    //     // put dot after normalized number
    //     if ((info->flags & SPECIAL || info->precision != 0) && len == -1) {
    //         *(*str)++ = '.';
    //     } else if ((info->flags & SPECIAL || info->precision != 0) && len > -1) {
    //         if (len != 0) {
    //             *(*str)++ = '.';
    //         }
    //     }

    //     // mantiss output
    //     while (!(info->flags & SPECIAL) && (len > 0)) {
    //         *(*str)++ = *number_digits++;
    //         len--;
    //     }
    //     while(info->precision-- > 0 && len == -1) {
    //             *(*str)++ = *number_digits++;
    //     }

    //     if (info->flags & CAPITALIZE) {
    //         *(*str)++ = 'E';
    //     } else {
    //         *(*str)++ = 'e';
    //     }

    //     // The exponent always has a sign,
    //     // so we don't have to equate it to zero
    //     if (exponent > 0) {
    //         char_exponent_sign = '+';
    //         exponent -= 1;
    //     } else {
    //         char_exponent_sign = '-';
    //         exponent = -exponent;
    //         exponent += 1;
    //     }

    //     *(*str)++ = char_exponent_sign;

    //     if (exponent == 0) {
    //         *(*str)++ = '0';
    //         *(*str)++ = '0';
    //     } else {
    //         if (exponent <= 9) {
    //             *(*str)++ = '0';
    //         }
    //         for (i = 0; exponent > 0; ++i) {
    //             tmp_char[i] = '0' + exponent % 10;
    //             exponent /= 10;
    //         }
    //         while (i > 0) {
    //             *(*str)++ = tmp_char[(i--) - 1];
    //         }
    //     }
    // } else {
    //     if (exponent <= 0) {
    //         *(*str)++ = '0';
    //         if (info->flags & SPECIAL || info->precision != 0)
    //             *(*str)++ = '.';
    //         while (exponent++ < 0) {
    //             *(*str)++ = '0';
    //         }
    //     } else {
    //         while (exponent-- > 0) {
    //             *(*str)++ = *number_digits++;
    //         }
    //         if ((info->flags & SPECIAL || info->precision != 0) && len == -1) {
    //             *(*str)++ = '.';
    //         }
    //     }
    //     while (!(info->flags & SPECIAL) && len > 0) {
    //         if (*number_digits != '\0') {
    //             *(*str)++ = *number_digits++;
    //         }
    //         len--;
    //     }
    //     while(*number_digits != '\0' && len == -1) {
    //         *(*str)++ = *number_digits++;
    //     }
    // }

    // // If there is a free width left, fill in with spaces
    // while (info->field_width-- > 0) {
    //     *(*str)++ = ' ';
    // }
} */