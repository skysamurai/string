#include "s21_sprintf.h"

#include <math.h>
//#include <stdlib.h>

#include "../s21_string.h"

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

void int_number_to_char(char **str, unsigned long long int number,
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
                tmp[i++] = digits_template[-(int)(signed long long)number %
                                           info->number_system];
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

double absf(double num) { return num > 0 ? num : -num; }
int abs(int num) { return num > 0 ? num : -num; }

#define	NDIG		350
char* cvt(double arg, int ndigits, int *decptp, int *signp, int eflag)
{
	register int decpt;
	double fi, fj;
	register char *p, *p1;
	static char buf[NDIG] = { 0 };
	double modf();

	if (ndigits < 0)
		ndigits = 0;
	if (ndigits >= NDIG-1)
		ndigits = NDIG-2;

	decpt = 0;
	*signp = 0;
	p = &buf[0];

	if (arg == 0) {
		*decptp = 0;
		while (p < &buf[ndigits])
			*p++ = '0';
		*p = '\0';
		return(buf);
	} else if (arg < 0) {
		*signp = 1;
		arg = -arg;
	}

	arg = modf(arg, &fi);
	p1 = &buf[NDIG];

	/*
	 * Do integer part
	 */
	*decptp = decpt;

	/*
	 * do fraction part
	 * p pts to where fraction should be concatenated
	 * p1 is how far conversion must go to
	 */
	p1 = &buf[ndigits];
	if (eflag==0) {
		/* fcvt must provide ndigits after decimal pt */
		p1 += decpt;
		/* if decpt was negative, we might done for fcvt */
		if (p1 < &buf[0]) {
			buf[0] = '\0';
			return(buf);
		}
	}
	while (p <= p1 && p < &buf[NDIG]) {
		arg *= 10;
		arg = modf(arg, &fj);
		*p++ = (int)fj + '0';
	}
	/*
	 * if we converted all the way to the end of the
	 * buf, don't mess with rounding since there's nothing
	 * significant out here anyway
	 */
	if (p1 >= &buf[NDIG]) {
		buf[NDIG-1] = '\0';
		return(buf);
	}
	/*
	 * round by adding 5 to last digit and propagating
	 * carries
	 */
	p = p1;
	*p1 += 5;
	while (*p1 > '9') {
		*p1 = '0';
		if (p1 > buf)
			++*--p1;
		else {
			*p1 = '1';
			(*decptp)++;
			if (eflag == 0) {
				if (p > buf)
					*p = '0';
				p++;
			}
		}
	}
	*p = '\0';
	return(buf);
}

fcvt(double arg, int ndigits, int *decptp, int *signp)
{
	return(cvt(arg, ndigits, decptp, signp, 0));
}

void real_number_to_char(char **str, double number, struct format_info *info) {
    double integral;
    double fractional;
    int exponent = 0;

    double numberBackup = number;
    // разделение целой и дробной части
    fractional = modf(number, &integral);
    // целая и дробная часть до всего
    printf("int:\t\t%100.100f\n", integral);
    printf("frac:\t\t%100.100f\n", fractional);
    // для операция ниже, в принципе можно использовать absf выше
    if (integral < 0) integral *= -1;

    // приводит numberCopy к инту и умножает его, пока его целая часть не станет
    // подходящей, парралельная считая экспоненту
    double numberCopy = number;
    if (integral >= 10) {
        while ((int)numberCopy >= 10 || (int)numberCopy <= -10) {
            exponent++;
            numberCopy /= 10.0;
        }
    } else if (integral == 0) {
        while ((int)numberCopy == 0) {
            exponent--;
            numberCopy *= 10.0;
        }
    }
    // то же самое что и с экспонентой, но чуть другим способом, пока хз как
    // красивее сделать. Вот тут точность теряется от спама modf и
    // умножения/деленя на 10, что с этим делать тоже пока хз
    if (integral >= 10)
        while ((int)integral >= 10) {
            // printf("--shift to left...\n");
            number /= 10.0;
            fractional = modf(number, &integral);
        }
    else if ((int)integral == 0) {
        while ((int)integral == 0) {
            // printf("--shift to right...\n");
            number *= 10.0;
            fractional = modf(number, &integral);
        }
    }
    //Обновялем целую и дробную часть, я хз что там навреху
    number = numberBackup;
    fractional = modf(number, &integral);

    char *outputPrecision;
    int sign;
    outputPrecision = fcvt(number,30, &exponent, &sign);

    printf("fracS\t\t0.%s?\n", outputPrecision);
    printf("num\t\t%.100lf\n", number);
    // TODO: вообще проблема перевода дабла в строку не решена, но
    // форматирование самого числа пока оно в double трудностей не представляет
    printf("AFTER CHANGE:\n");
    // printf("int: %100.100f\n", integral);
    // printf("frac: %100.100f\n", fractional);
    printf("exp: %d\n", exponent);
}
