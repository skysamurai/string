#include "s21_string.h"
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>
#include <inttypes.h>
#include <wchar.h>
#include <math.h>

static void print_char(char *buffer, s21_size_t *currlen, char c) {
    buffer[(*currlen)++] = c;
    return;
}

int countExp(long n) {
    int result = 0;
    if (n / 10 == 0) {
        result = 0;
    } else {
        result = 1 + countExp(n / 10);
    }
    return result;
}

int countExp_Less_than_One(long double fl) {
    int temp = fl, result = 0;
    if (temp != 0) {
        result = 0;
    } else {
        result = 1 + countExp_Less_than_One(fl * 10);
    }
    return result;
}

static void format_int(char *buffer, s21_size_t *currlen, long value, int base,
                       int width, int prec, int flags) {
    int signvalue = 0, place = 0, spadlen = 0, zpadlen = 0,
        up = (flags & FLAG_UP) ? 1 : 0;
    unsigned long unsign_val = value;
    char convert[SIZE];

    if (prec < 0) prec = 0;

    if (!(flags & FLAG_UNSIGNED)) {
        if (value < 0) {
            signvalue = '-';
            unsign_val = -value;
        } else if (flags & FLAG_PLUS) {
            signvalue = '+';
        } else if (flags & FLAG_SPACE) {
            signvalue = ' ';
        }
    }

    do {
        convert[place++] =
            (up ? "0123456789ABCDEF" : "0123456789abcdef")[unsign_val % base];
        unsign_val = unsign_val / base;
    } while (unsign_val);

#if defined(__linux__)
    if (flags & FLAG_POINTER || (flags & FLAG_NUM && base == 16)) {
        if (value != 0) {
            width -= 2;
        } else {
            width -= 4;
        }
    }
#endif
#if defined(__MACH__)
    if (flags & FLAG_POINTER) width -= 2;
#endif
    zpadlen = prec - place;
    spadlen = width - (prec > place ? prec : place) - (signvalue ? 1 : 0);

    if (zpadlen < 0) zpadlen = 0;
    if (spadlen < 0) spadlen = 0;
    if (flags & FLAG_ZERO) {
        zpadlen = (zpadlen > spadlen ? zpadlen : spadlen);
        spadlen = 0;
    }
    if (flags & FLAG_MINUS) spadlen = -spadlen;

    while (spadlen > 0) {
        print_char(buffer, currlen, ' ');
        --spadlen;
    }

#if defined(__linux__)

    if (value == 0 && (flags & FLAG_POINTER)) {
        char nil[5] = "(nil)";
        for (int i = 0; i < 5; ++i) {
            print_char(buffer, currlen, nil[i]);
        }
        flags |= FLAG_EXIT;
    }
#endif
    if (!(flags & FLAG_EXIT)) {
        if (signvalue) print_char(buffer, currlen, signvalue);

        if (flags & FLAG_POINTER || flags & FLAG_NUM) {
            if (base == 16) {
                print_char(buffer, currlen, '0');
                print_char(buffer, currlen, 'x');
            } else if (base == 8) {
                print_char(buffer, currlen, '0');
            }
        }

        if (zpadlen > 0) {
            while (zpadlen > 0) {
                print_char(buffer, currlen, '0');
                --zpadlen;
            }
        }

        while (place > 0) print_char(buffer, currlen, convert[--place]);

        while (spadlen < 0) {
            print_char(buffer, currlen, ' ');
            ++spadlen;
        }
    }
    return;
}

static void format_str(char *buffer, s21_size_t *currlen, char *value,
                       int flags, int width, int prec) {
    int padlen = 0, str_len = s21_strlen(value);
    if (str_len > prec) str_len = prec;
    padlen = width - str_len;
    if (padlen < 0) padlen = 0;
    if (flags & FLAG_MINUS) padlen = -padlen;

    for (int i = 0; padlen > 0 && i < prec; padlen--, i--)
        print_char(buffer, currlen, ' ');

    for (int i = 0; *value && i < prec; i++)
        print_char(buffer, currlen, *value++);

    for (int i = 0; padlen < 0 && i < prec; padlen--, i++)
        print_char(buffer, currlen, ' ');

    return;
}

static void format_float(char *buffer, s21_size_t *currlen, long double fvalue,
                         int width, int prec, int flags) {
    long double ufvalue, temp_ufvalue;
    unsigned long intpart = 0;
    int signvalue = 0, iplace = 0, fplace = 0, padlen = 0, exp = 0,
        up = (flags & FLAG_UP) ? 1 : 0;
    char iconvert[SIZE], fconvert[SIZE], scientific[4] = "e+00";

    if (prec < 0) prec = (flags & FLAG_NUM || flags & FLAG_DOT) ? 0 : 6;
    if (prec >= SIZE) prec = SIZE;

    ufvalue = (fvalue >= 0) ? fvalue : -fvalue;
    if (fvalue < 0)
        signvalue = '-';
    else if (flags & FLAG_PLUS)
        signvalue = '+';
    else if (flags & FLAG_SPACE)
        signvalue = ' ';
    else if (flags & FLAG_ZERO)
        signvalue = '0';

    if (flags & FLAG_MANTISSA || flags & FLAG_G) {
        temp_ufvalue = ufvalue;
        intpart = ufvalue;
        exp = intpart != 0 ? countExp(intpart)
                           : countExp_Less_than_One(temp_ufvalue);
        int temp = intpart != 0 ? exp : -exp;
        if (flags & FLAG_G) {
            if (temp < -4 || temp >= prec) {
                flags |= FLAG_MANTISSA, --prec, ++width;
            } else {
                prec -= (exp + 1);
            }
        }
    }

    if (flags & FLAG_MANTISSA) {
        ufvalue = intpart != 0 ? temp_ufvalue / pow(10, exp)
                               : temp_ufvalue * pow(10, exp);
        if (intpart == 0) scientific[1] = '-';
        if (exp > 9) {
            scientific[2] = exp / 10 + '0';
            scientific[3] = exp % 10 + '0';
        } else {
            scientific[3] = exp + '0';
        }
        if (up) scientific[0] = 'E';
    }

    intpart = ufvalue;
    ufvalue -= (int)ufvalue;
    ufvalue *= 10;
    for (int i = 0; i < prec; ++i) {
        fconvert[fplace++] = (int)ufvalue + '0';
        ufvalue = ufvalue - (int)ufvalue;
        ufvalue *= 10;
    }

    if (fplace == SIZE) fplace--;
    fconvert[fplace] = 0;

    if (ufvalue > 5) {
        int find = fplace - 1;
        int carry = 1;
        while (carry && find + 1) {
            fconvert[find]++;
            if (fconvert[find] > '9') {
                fconvert[find] = '0';
                carry = 1;
            } else {
                carry = 0;
            }
            --find;
        }
        if (carry) ++intpart;
    }

    /*  trim zeroes for spec G  */
    if (flags & FLAG_G) {
        int place = fplace - 1;
        if (place >= 0) {
            while ((fconvert[place] - '0') == 0) fconvert[place--] = '\0';
        }
    }

    do {
        iconvert[iplace++] =
            (up ? "0123456789ABCDEF" : "0123456789abcdef")[intpart % 10];
        intpart = (intpart / 10);
    } while (intpart && (iplace < SIZE));
    if (iplace == SIZE) iplace--;
    iconvert[iplace] = 0;

    /* -1 for decimal point, another -1 if we are printing a sign */
    padlen = width - iplace - prec - 1 - ((signvalue) ? 1 : 0);
    if (flags & FLAG_MANTISSA) padlen -= 4;
    if (padlen < 0) padlen = 0;
    if (flags & FLAG_MINUS) padlen = -padlen;

    if ((flags & FLAG_ZERO) && (padlen > 0)) {
        if (signvalue) {
            print_char(buffer, currlen, signvalue);
            signvalue = 0;
        }
        while (padlen > 0) {
            print_char(buffer, currlen, '0');
            --padlen;
        }
    }

    while (padlen > 0) {
        print_char(buffer, currlen, ' ');
        --padlen;
    }
    if (signvalue) print_char(buffer, currlen, signvalue);
    while (iplace > 0) print_char(buffer, currlen, iconvert[--iplace]);
    if ((prec == 0) && (flags & FLAG_NUM)) print_char(buffer, currlen, '.');
    if (prec > 0) {
        if (!((flags & FLAG_G) && (s21_strlen(fconvert) == 0))) {
            print_char(buffer, currlen, '.');
            for (int i = 0; i < fplace && fconvert[i] != '\0'; ++i)
                print_char(buffer, currlen, fconvert[i]);
        }
    }

    if (flags & FLAG_MANTISSA) {
        for (int i = 0; i < 4; ++i) print_char(buffer, currlen, scientific[i]);
    }

    while (padlen < 0) {
        print_char(buffer, currlen, ' ');
        ++padlen;
    }
    return;
}

static void switcher(char *buff, const char *format, va_list args) {
    char *strvalue;
    s21_size_t place = 0;
    int flags = 0, width = 0, prec = -1, state = STATE_DEFAULT;
    char ch = *format++;
    mbstate_t mbstate;
    char mbchar[4];

    while (state != STATE_DONE) {
        if ('\0' == ch) state = STATE_DONE;

        switch (state) {
            case STATE_DEFAULT:
                if (ch == '%')
                    state = STATE_FLAGS;
                else
                    print_char(buff, &place, ch);
                ch = *format++;
                break;
            case STATE_FLAGS:
                switch (ch) {
                    case '-':
                        flags |= FLAG_MINUS;
                        ch = *format++;
                        break;
                    case '+':
                        flags |= FLAG_PLUS;
                        ch = *format++;
                        break;
                    case ' ':
                        flags |= FLAG_SPACE;
                        ch = *format++;
                        break;
                    case '#':
                        flags |= FLAG_NUM;
                        ch = *format++;
                        break;
                    case '0':
                        flags |= FLAG_ZERO;
                        ch = *format++;
                        break;
                    default:
                        state = STATE_WIDTH;
                        break;
                }
                break;
            case STATE_WIDTH:
                if (isdigit(ch)) {
                    width = 10 * width + (ch - '0');
                    ch = *format++;
                } else if ('*' == ch) {
                    width = va_arg(args, int);
                    ch = *format++;
                    state = STATE_PRECISION;
                } else {
                    state = STATE_PRECISION;
                }
                break;
            case STATE_PRECISION:
                if ('.' == ch) {
                    state = STATE_MAX_PREC;
                    flags |= FLAG_DOT;
                    ch = *format++;
                } else {
                    state = STATE_LEN;
                }
                break;
            case STATE_MAX_PREC:
                if (isdigit(ch)) {
                    if (prec < 0) prec = 0;
                    prec = 10 * prec + (ch - '0');
                    ch = *format++;
                } else if ('*' == ch) {
                    prec = va_arg(args, int);
                    ch = *format++;
                    state = STATE_LEN;
                } else {
                    state = STATE_LEN;
                }
                break;
            case STATE_LEN:
                if (ch == 'h') {
                    flags |= FLAG_SHORT;
                    ch = *format++;
                    state = STATE_SPEC;
                } else if (ch == 'l') {
                    flags |= FLAG_LONG;
                    ch = *format++;
                    state = STATE_SPEC;
                } else if (ch == 'L') {
                    flags |= FLAG_LONGDOUBLE;
                    ch = *format++;
                    state = STATE_SPEC;
                } else {
                    state = STATE_SPEC;
                }
                break;
            case STATE_SPEC:
                switch (ch) {
                    case 'd':
                    case 'i':
                        {}
                        long int sign_long_int = va_arg(args, long int);
                        if (flags & FLAG_SHORT) {
                            short sign_short_int = sign_long_int;
                            format_int(buff, &place, sign_short_int, 10, width,
                                       prec, flags);
                        } else if (!(flags & FLAG_LONG)) {
                            int sign_int = sign_long_int;
                            format_int(buff, &place, sign_int, 10, width, prec,
                                       flags);
                        } else {
                            format_int(buff, &place, sign_long_int, 10, width,
                                       prec, flags);
                        }
                        break;
                    case 'u':
                        flags |= FLAG_UNSIGNED;
                        unsigned long unsign_long_int =
                            va_arg(args, unsigned long int);
                        if (flags & FLAG_SHORT) {
                            unsigned short unsign_short_int = unsign_long_int;
                            format_int(buff, &place, unsign_short_int, 10,
                                       width, prec, flags);
                        } else if (!(flags & FLAG_LONG)) {
                            unsigned unsign_int = unsign_long_int;
                            format_int(buff, &place, unsign_int, 10, width,
                                       prec, flags);
                        } else {
                            format_int(buff, &place, unsign_long_int, 10, width,
                                       prec, flags);
                        }
                        break;
                    case 'o':
                        flags |= FLAG_UNSIGNED;
                        unsign_long_int = va_arg(args, unsigned long int);
                        if (flags & FLAG_SHORT) {
                            unsigned short unsign_short_int = unsign_long_int;
                            format_int(buff, &place, unsign_short_int, 8, width,
                                       prec, flags);
                        } else if (!(flags & FLAG_LONG)) {
                            unsigned unsign_int = unsign_long_int;
                            format_int(buff, &place, unsign_int, 8, width, prec,
                                       flags);
                        } else {
                            format_int(buff, &place, unsign_long_int, 8, width,
                                       prec, flags);
                        }
                        break;
                    case 'X':
                    case 'x':
                        if (ch == 'X') flags |= FLAG_UP;
                        flags |= FLAG_UNSIGNED;
                        unsign_long_int = va_arg(args, unsigned long int);
                        if (flags & FLAG_SHORT) {
                            unsigned short unsign_short_int = unsign_long_int;
                            format_int(buff, &place, unsign_short_int, 16,
                                       width, prec, flags);
                        } else if (!(flags & FLAG_LONG)) {
                            unsigned unsign_int = unsign_long_int;
                            format_int(buff, &place, unsign_int, 16, width,
                                       prec, flags);
                        } else {
                            format_int(buff, &place, unsign_long_int, 16, width,
                                       prec, flags);
                        }
                        break;
                    case 'E':
                    case 'e':
                        if (ch == 'E') flags |= FLAG_UP;
                        flags |= FLAG_MANTISSA;
                        if (flags & FLAG_LONGDOUBLE) {
                            long double long_doub_val =
                                va_arg(args, long double);
                            format_float(buff, &place, long_doub_val, width,
                                         prec, flags);
                        } else {
                            double doub_val = va_arg(args, double);
                            format_float(buff, &place, doub_val, width, prec,
                                         flags);
                        }
                        break;
                    case 'G':
                    case 'g':
                        if (ch == 'G') flags |= FLAG_UP;
                        flags |= FLAG_G;
                        if (flags & FLAG_LONGDOUBLE) {
                            long double long_doub_val =
                                va_arg(args, long double);
                            format_float(buff, &place, long_doub_val, width,
                                         prec, flags);
                        } else {
                            double doub_val = va_arg(args, double);
                            format_float(buff, &place, doub_val, width, prec,
                                         flags);
                        }
                        break;
                    case 'f':
                        if (flags & FLAG_LONGDOUBLE) {
                            long double long_doub_val =
                                va_arg(args, long double);
                            format_float(buff, &place, long_doub_val, width,
                                         prec, flags);
                        } else {
                            double doub_val = va_arg(args, double);
                            format_float(buff, &place, doub_val, width, prec,
                                         flags);
                        }
                        break;
                    case 'c':
                        if (flags & FLAG_LONG) {
                            wchar_t *sym = (wchar_t *)va_arg(args, wchar_t *);
                            s21_memset(&mbstate, 0, sizeof(mbstate));
                            wcrtomb(mbchar, sym[0], &mbstate);
                            if (prec < 0) prec = 6;
                            format_str(buff, &place, mbchar, flags, width,
                                       prec);
                        } else {
                            print_char(buff, &place, va_arg(args, int));
                        }
                        break;
                    case 'p':
                        flags |= FLAG_POINTER;
                        unsign_long_int =
                            (unsigned long)((uintptr_t)va_arg(args, void *));
                        format_int(buff, &place, unsign_long_int, 16, width,
                                   prec, flags);
                        break;
                    case 's':
                        if (prec < 0) prec = SIZE;
                        if (flags & FLAG_LONG) {
                            wchar_t *sym = va_arg(args, wchar_t *);
                            s21_memset(&mbstate, 0, sizeof(mbstate));
                            size_t len = wcslen(sym);
                            for (size_t i = 0; i < len; i++) {
                                wcrtomb(mbchar, *sym, &mbstate);
                                sym++;
                                format_str(buff, &place, mbchar, flags, width,
                                           prec);
                            }
                        } else {
                            strvalue = va_arg(args, char *);
                            format_str(buff, &place, strvalue, flags, width,
                                       prec);
                        }
                        break;
                    case '%':
                        print_char(buff, &place, ch);
                        break;
                    case 'n': {
                        int *p_int = va_arg(args, int *);
                        *p_int = place;
                        break;
                    }
                }
                int cflags = 0;
                ch = *format++;
                state = STATE_DEFAULT;
                flags = cflags = width = 0;
                prec = -1;
                break;
            case STATE_DONE:
                break;
        }
    }
    buff[place] = '\0';
}

int s21_sprintf(char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);
    switcher(str, format, args);
    va_end(args);
    return 0;
}
