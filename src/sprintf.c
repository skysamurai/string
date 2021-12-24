#include "s21_string.h"

int s21_sprintf(char *buf, ...) {
    char c, *mass;
    int d, score = 0;
    short int hd;
    long int ld;
    unsigned short int ho;
    unsigned long int lo;
    double e;
    unsigned int o;
    unsigned long int p;
    double f;
    va_list ptr;
    va_start(ptr, buf);
    char *format = va_arg(ptr, char *);
    token *tokens;
    while (*format != '\0') {
        if (*format == '%') {
            format++;
            score++;
            tokens = parser_format(format);
            if (tokens->perc == -5) {
                tokens->perc = va_arg(ptr, int);
            }
            if (tokens->width == -5) {
                tokens->width = va_arg(ptr, int);
            }
            char temp_buff_diff[256];
            switch (tokens->spec) {
                case 1:  // c
                    c = (char)va_arg(ptr, int);
                    s21_chtoa(c, buf, tokens->spec, tokens->flag, tokens->width,
                              tokens->perc);
                    break;
                case 2:
                case 3:  // d i
                    switch (tokens->len) {
                        case 0:
                            d = va_arg(ptr, int);
                            s21_itoa(d, buf, tokens->width, tokens->flag,
                                     tokens->spec, tokens->perc);
                            break;
                        case 1:
                            hd = (short int)va_arg(ptr, int);
                            s21_itoa(hd, buf, tokens->width, tokens->flag,
                                     tokens->spec, tokens->perc);
                            break;
                        case 2:
                            ld = va_arg(ptr, long int);
                            s21_itoa(ld, buf, tokens->width, tokens->flag,
                                     tokens->spec, tokens->perc);
                            break;
                    }
                    break;
                case 4:  // e
                    e = va_arg(ptr, double);
                    s21_etoa(e, tokens->perc, tokens->spec, temp_buff_diff,
                             tokens->flag);
                    d = s21_strlen(temp_buff_diff);
                    buf = flags_e(buf, tokens->width, tokens->flag, d,
                                  temp_buff_diff, tokens->perc, tokens->spec);
                    break;
                case 5:  // E
                    e = va_arg(ptr, double);
                    s21_etoa(e, tokens->perc, tokens->spec, temp_buff_diff,
                             tokens->flag);
                    d = s21_strlen(temp_buff_diff);
                    buf = flags_e(buf, tokens->width, tokens->flag, d,
                                  temp_buff_diff, tokens->perc, tokens->spec);
                    break;
                case 6:  // f
                    f = va_arg(ptr, double);
                    s21_dtoa(f, tokens->perc, temp_buff_diff, tokens->flag,
                             tokens->spec);
                    d = s21_strlen(temp_buff_diff);
                    buf = flags_e(buf, tokens->width, tokens->flag, d,
                                  temp_buff_diff, tokens->perc, tokens->spec);
                    break;
                case 7:
                case 8:  // g G
                    e = va_arg(ptr, double);
                    s21_etoa(e, tokens->perc, tokens->spec, temp_buff_diff,
                             tokens->flag);
                    int a = s21_strlen(temp_buff_diff);
                    s21_dtoa(e, tokens->perc, temp_buff_diff, tokens->flag,
                             tokens->spec);
                    int b = s21_strlen(temp_buff_diff);
                    if (a < b) {
                        s21_etoa(e, tokens->perc, tokens->spec, temp_buff_diff,
                                 tokens->flag);
                    }
                    d = s21_strlen(temp_buff_diff);
                    buf = flags_e(buf, tokens->width, tokens->flag, d,
                                  temp_buff_diff, tokens->perc, tokens->spec);
                    break;
                case 9:  // o
                    switch (tokens->len) {
                        case 0:
                            o = va_arg(ptr, unsigned int);
                            s21_utoa(o, buf, tokens->width, tokens->flag,
                                     tokens->spec, tokens->perc);
                            break;
                        case 1:
                            ho = (unsigned short int)va_arg(ptr, unsigned int);
                            s21_utoa(ho, buf, tokens->width, tokens->flag,
                                     tokens->spec, tokens->perc);
                            break;
                        case 2:
                            lo = va_arg(ptr, unsigned long int);
                            s21_utoa(lo, buf, tokens->width, tokens->flag,
                                     tokens->spec, tokens->perc);
                            break;
                    }
                    break;
                case 10:  // s
                    mass = va_arg(ptr, char *);
                    buf = s21_ctoa(mass, buf, tokens->spec, tokens->flag,
                                   tokens->width, tokens->perc);
                    break;
                case 11:  // u
                    switch (tokens->len) {
                        case 0:
                            o = va_arg(ptr, unsigned int);
                            s21_utoa(o, buf, tokens->width, tokens->flag,
                                     tokens->spec, tokens->perc);
                            break;
                        case 1:
                            ho = (unsigned short int)va_arg(ptr, unsigned int);
                            s21_utoa(ho, buf, tokens->width, tokens->flag,
                                     tokens->spec, tokens->perc);
                            break;
                        case 2:
                            lo = va_arg(ptr, unsigned long int);
                            s21_utoa(lo, buf, tokens->width, tokens->flag,
                                     tokens->spec, tokens->perc);
                            break;
                    }
                    break;
                case 12:  // x
                    switch (tokens->len) {
                        case 0:
                            o = va_arg(ptr, unsigned int);
                            s21_uutoa(o, buf, tokens->spec, tokens->flag,
                                      tokens->width, tokens->perc);
                            break;
                        case 1:
                            ho = (unsigned short int)va_arg(ptr, unsigned int);
                            s21_uutoa(ho, buf, tokens->spec, tokens->flag,
                                      tokens->width, tokens->perc);
                            break;
                        case 2:
                            lo = va_arg(ptr, unsigned long int);
                            s21_uutoa(lo, buf, tokens->spec, tokens->flag,
                                      tokens->width, tokens->perc);
                            break;
                    }
                    break;
                case 13:  // X
                    switch (tokens->len) {
                        case 0:
                            o = va_arg(ptr, unsigned int);
                            s21_uutoa(o, buf, tokens->spec, tokens->flag,
                                      tokens->width, tokens->perc);
                            break;
                        case 1:
                            ho = (unsigned short int)va_arg(ptr, unsigned int);
                            s21_uutoa(ho, buf, tokens->spec, tokens->flag,
                                      tokens->width, tokens->perc);
                            break;
                        case 2:
                            lo = va_arg(ptr, unsigned long int);
                            s21_uutoa(lo, buf, tokens->spec, tokens->flag,
                                      tokens->width, tokens->perc);
                            break;
                    }
                    break;
                case 14:  // p
                    p = va_arg(ptr, unsigned long int);
                    s21_uutoa(p, buf, tokens->spec, tokens->flag, tokens->width,
                              tokens->perc);
                    break;
                case 15:  // n
                    score--;
                    unsigned long int *n = va_arg(ptr, unsigned long int *);
                    *n = score;
                    score++;
                    break;
                case 16:  // %
                    *buf++ = '%';
                    score--;
                    *buf = '\0';
                    break;
            }
            while (tokens->score) {
                format++;
                score++;
                tokens->score--;
            }
            while (*buf != '\0') {
                buf++;
            }
        } else {
            *buf++ = *format++;
            score++;
            *buf = '\0';
        }
    }
    va_end(ptr);
    return s21_strlen(buf);
}

void *parser_format(const char *f) {
    static token one;
    one.score = 0;
    one.flag = 3;
    while (*f == '-' || *f == '+' || *f == ' ' || *f == '#' || *f == '0') {
        if ((one.flag = parser_flag(f)) != 3) {
            one.score++;
            f++;
        } else {
            one.flag = 3;
        }
    }
    if (*f == '*') {
        one.width = -5;
        one.score++;
        f++;
    } else if ((one.width = parser_numbers(f)) != 0) {
        int temp = one.width;
        while (temp /= 10) {
            one.score++;
            f++;
        }
        one.score++;
        f++;
    } else {
        one.width = 0;
    }
    if (*f == '.') {
        one.score++;
        f++;
        if (*f == '*') {
            one.perc = -5;
            one.score++;
            f++;
        } else if (*f == '0') {
            one.perc = 0;
            one.score++;
            f++;
        } else if ((one.perc = parser_numbers(f)) != 0) {
            int temp = one.perc;
            while (temp /= 10) {
                one.score++;
                f++;
            }
            one.score++;
            f++;
        } else {
            one.perc = 0;
        }
    } else {
        one.perc = -1;
    }
    if ((one.len = parser_lenght(f)) != 0) {
        one.score++;
        f++;
    } else {
        one.len = 0;
    }
    if ((one.spec = parser_specificator(f)) != 0) {
        one.score++;
    } else {
        one.spec = 0;
    }
    token *adress = &one;
    return one.spec == 0 ? 0 : adress;
}

int str_num(const char *str1, const char *str2) {
    int flag = 0;
    for (int i = 0; str2[i] != '\0'; i++) {
        if (*str1 == str2[i]) {
            flag = 1;
            break;
        }
    }
    return flag;
}

int parser_numbers(const char *f) {
    const char numbers[] = {"0123456789"};
    static char temp_num[256];
    static char temp_mass[256];
    int width = 0;
    *temp_num = *f;
    while (str_num(temp_num, numbers) != 0) {
        s21_strcat(temp_mass, temp_num);
        f++;
        *temp_num = *f;
    }
    width = atoi(temp_mass);
    int j = 0;
    for (int i = 0; temp_mass[i + 1] != '\0'; i++) {
        temp_mass[i] = '\0';
        j = i + 1;
    }
    temp_mass[j] = '\0';
    return width;
}

int parser_flag(const char *f) {
    int flag = 3;
    switch (*f) {
        case '-':
            flag = 1;
            break;
        case '+':
            flag = 2;
            break;
        case '#':
            flag = 4;
            break;
        case '0':
            flag = 5;
            break;
        case ' ':
            flag = 6;
            break;
    }
    return flag;
}

int parser_lenght(const char *f) {
    int flag = 0;
    switch (*f) {
        case 'h':
            flag = 1;
            break;
        case 'l':
            flag = 2;
            break;
        case 'L':
            flag = 3;
            break;
    }
    return flag;
}

int parser_specificator(const char *f) {
    int flag = 0;
    switch (*f) {
        case 'c':
            flag = 1;
            break;
        case 'd':
            flag = 2;
            break;
        case 'i':
            flag = 3;
            break;
        case 'e':
            flag = 4;
            break;
        case 'E':
            flag = 5;
            break;
        case 'f':
            flag = 6;
            break;
        case 'g':
            flag = 7;
            break;
        case 'G':
            flag = 8;
            break;
        case 'o':
            flag = 9;
            break;
        case 's':
            flag = 10;
            break;
        case 'u':
            flag = 11;
            break;
        case 'x':
            flag = 12;
            break;
        case 'X':
            flag = 13;
            break;
        case 'p':
            flag = 14;
            break;
        case 'n':
            flag = 15;
            break;
        case '%':
            flag = 16;
            break;
    }
    return flag;
}

void s21_chtoa(char sym, char *buf, int spec, int flag, int width, int perc) {
    int score = 1;
    perc = 0;
    if (flag == 1) {
        *buf = sym;
        buf++;
        buf = fill(score, width, buf, flag, perc, spec);
    } else {
        buf = fill(score, width, buf, flag, perc, spec);
        *buf = sym;
        buf++;
    }
    *buf++ = '\0';
}

void s21_itoa(long long num, char *buf, int width, int flag, int spec,
              int perc) {
    int score = 0, min = 0, q = -1;
    if (num == 0) {
        q = 0;
    }
    if (num < 0) {
        min = -1;
        num = -num;
        score++;
    } else if (flag == 2) {
        score++;
    }
    int b = 0, k = 0;
    while (num) {
        b = b * 10 + num % 10;
        num /= 10;
        k++;
        score++;
    }
    if (k < perc && flag == 2) {
        width--;
    }
    if (q == 0) {
        k = 1;
    }
    if (flag == 1) {
        buf = minus_or(min, buf, flag, spec);
        buf = record(k, b, buf, perc);
        buf = fill(score, width, buf, flag, perc, spec);
    } else if (flag == 2 || flag == 4) {
        buf = fill(score, width, buf, flag, perc, spec);
        buf = minus_or(min, buf, flag, spec);
        buf = record(k, b, buf, perc);
    } else if (flag == 5) {
        buf = minus_or(min, buf, flag, spec);
        buf = fill(score, width, buf, flag, perc, spec);
        buf = record(k, b, buf, perc);
    } else if (flag == 3) {
        buf = fill(score, width, buf, flag, perc, spec);
        buf = minus_or(min, buf, flag, spec);
        buf = record(k, b, buf, perc);
    } else if (flag == 6) {
        if ((width <= score || perc >= width) && min == 0) {
            *buf++ = ' ';
        }
        buf = fill(score, width, buf, flag, perc, spec);
        buf = minus_or(min, buf, flag, spec);
        buf = record(k, b, buf, perc);
    }
    *buf++ = '\0';
}

void s21_etoa(long double num, int perc, int spec, char *buf, int flag) {
    if (perc == -1) {
        perc = 6;
    }
    int m = 0, cut_num = 0, r = perc;
    long long k = 1;
    if (num < 0) {
        *buf++ = '-';
        num = -num;
    } else if (flag == 2) {
        *buf++ = '+';
    }
    while (num < 1 && num > 0) {
        num *= 10;
        cut_num++;
        m = -1;
    }
    while (num > 10) {
        num /= 10;
        cut_num++;
        m = 1;
    }
    while (r != 0) {
        k *= 10;
        r--;
    }
    num *= k;
    num = round(num);
    num /= k;
    double clone_perc = num;
    int clone_num2 = num;
    *buf++ = clone_num2 % 10 + '0';
    if (perc >= 1 || flag == 4) {
        *buf++ = '.';
    }
    if (spec == 4 || spec == 5) {
        for (long long clone_num = 0; perc != 0; perc--) {
            clone_perc *= 10;
            clone_num = clone_perc;
            *buf = clone_num % 10 + '0';
            if (*buf == '(') {
                *buf = '0';
            }
            buf++;
        }
    } else if (spec == 7 || spec == 8) {
        for (long long clone_num = 0; perc != 0; perc--) {
            clone_perc *= 10;
            clone_num = clone_perc;
            *buf = clone_num % 10 + '0';
            if (*buf == '(') {
                *buf = '0';
            }
            buf++;
            if (clone_perc == (int)clone_perc) {
                break;
            }
        }
    }
    if (spec == 5 || spec == 8) {
        *buf++ = 'E';
    } else {
        *buf++ = 'e';
    }
    if (m == -1) {
        *buf++ = '-';
    } else {
        *buf++ = '+';
    }
    if (cut_num < 10) {
        *buf++ = '0';
        *buf++ = cut_num + '0';
    } else {
        int cut_num_reverse = 0;
        while (cut_num) {
            cut_num_reverse = cut_num_reverse * 10 + cut_num % 10;
            cut_num /= 10;
        }
        while (cut_num_reverse) {
            *buf++ = cut_num_reverse % 10 + '0';
            cut_num_reverse /= 10;
        }
    }
    *buf++ = '\0';
}

void s21_dtoa(long double num, int perc, char *buf, int flag, int spec) {
    if (perc == -1) {
        perc = 6;
    }
    int r = perc;
    long long k = 1;
    if (num < 0) {
        *buf++ = '-';
        num = -num;
    } else if (flag == 2) {
        *buf++ = '+';
    }
    while (r != 0) {
        k *= 10;
        r--;
    }
    num *= k;
    num = roundl(num);
    num /= k;
    long long clone_num = num;
    double clone_perc = num;
    if (num < 1 && num > 0) {
        *buf++ = '0';
    } else if (num == 0) {
        buf--;
        *buf++ = '0';
    } else {
        int b = 0;
        while (clone_num) {
            b = b * 10 + clone_num % 10;
            clone_num /= 10;
        }
        while (b) {
            *buf++ = b % 10 + '0';
            b /= 10;
        }
    }
    if (perc >= 1 || flag == 4) {
        *buf++ = '.';
    }
    if (spec == 6) {
        for (; perc != 0; perc--) {
            clone_perc *= 10;
            clone_num = clone_perc;
            *buf = clone_num % 10 + '0';
            if (*buf == '(') {
                *buf = '0';
            }
            buf++;
        }
    } else if (spec == 7 || spec == 8) {
        for (; perc != 0; perc--) {
            clone_perc *= 10;
            clone_num = clone_perc;
            *buf++ = clone_num % 10 + '0';
            if (clone_perc == (int)clone_perc) {
                break;
            }
        }
    }
    *buf++ = '\0';
}

void s21_utoa(unsigned long long num, char *buf, int width, int flag, int spec,
              int perc) {
    int score = 0;
    if (flag == 4 && spec == 9) {
        score++;
    }
    if ((spec == 9 || spec == 11) && flag == 2) {
        score--;
    }
    int b = 0, k = 1;
    if (spec == 9) {
        int c = 0;
        while (num) {
            b = num % 8;
            num /= 8;
            c += b * pow(10, k - 1);
            b = 0;
            k++;
        }
        num = c;
    }
    k = 0;
    while (num) {
        b = b * 10 + num % 10;
        num /= 10;
        k++;
        score++;
    }
    if (flag == 1) {
        buf = record(k, b, buf, perc);
        buf = fill(score, width, buf, flag, perc, spec);
    } else if (flag == 2) {
        buf = fill(score, width, buf, flag, perc, spec);
        buf = record(k, b, buf, perc);
    } else if (flag == 4) {
        buf = fill(score, width, buf, flag, perc, spec);
        if (spec == 9) {
            *buf++ = '0';
        }
        buf = record(k, b, buf, perc);
    } else if (flag == 5) {
        buf = fill(score, width, buf, flag, perc, spec);
        buf = record(k, b, buf, perc);
    } else if (flag == 3) {
        buf = fill(score, width, buf, flag, perc, spec);
        buf = record(k, b, buf, perc);
    }
    *buf++ = '\0';
}

void *s21_ctoa(char *str, char *buf, int spec, int flag, int width, int perc) {
    int score = s21_strlen(str);
    if (perc >= 0) {
        str[perc] = '\0';
        if (perc > score) {
            perc = score;
        } else {
            score = perc;
        }
    }
    if (flag == 1) {
        s21_strcat(buf, str);
        while (*buf) {
            buf++;
        }
        buf = fill(score, width, buf, flag, perc, spec);
    } else if (flag == 5) {
        buf = fill(score, width, buf, flag, perc, spec);
        s21_strcat(buf, str);
    } else {
        buf = fill(score, width, buf, flag, perc, spec);
        s21_strcat(buf, str);
    }
    return buf;
}

void s21_uutoa(unsigned long long num, char *buf, int spec, int flag, int width,
               int perc) {
    int score = 0;
    char mass[16] = {"0123456789abcdef"};
    if (spec == 13) {
        mass[10] = 'A';
        mass[11] = 'B';
        mass[12] = 'C';
        mass[13] = 'D';
        mass[14] = 'E';
        mass[15] = 'F';
    }
    if (spec == 14 || flag == 4) {
        score += 2;
    }
    if (flag == 2 && spec != 14) {
        score++;
    }
    char temp_mass[256];
    int c = 0;
    while (num) {
        unsigned int b;
        b = num % 16;
        for (unsigned int i = 0, j = 0; i < 16; i++, j++) {
            if (b == i) {
                temp_mass[c] = mass[j];
                temp_mass[c + 1] = '\0';
                c++;
                break;
            }
        }
        num /= 16;
    }
    score = score + s21_strlen(temp_mass);
    c--;
    if (flag == 1) {
        if (spec == 14) {
            *buf++ = '0';
            *buf++ = 'x';
        }
        buf = record_p(c, temp_mass, buf, perc);
        buf = fill(score, width, buf, flag, perc, spec);
    } else if (flag == 2) {
        buf = fill(score, width, buf, flag, perc, spec);
        if (spec == 14) {
            *buf++ = '0';
            *buf++ = 'x';
        }
        buf = record_p(c, temp_mass, buf, perc);
    } else if (flag == 4) {
        buf = fill(score, width, buf, flag, perc, spec);
        if (spec == 12 || spec == 14) {
            *buf++ = '0';
            *buf++ = 'x';
        } else if (spec == 13) {
            *buf++ = '0';
            *buf++ = 'X';
        }
        buf = record_p(c, temp_mass, buf, perc);
    } else if (flag == 3) {
        buf = fill(score, width, buf, flag, perc, spec);
        if (spec == 14) {
            *buf++ = '0';
            *buf++ = 'x';
        }
        buf = record_p(c, temp_mass, buf, perc);
    } else if (flag == 5) {
        if (spec == 14) {
            *buf++ = '0';
            *buf++ = 'x';
        }
        buf = fill(score, width, buf, flag, perc, spec);
        buf = record_p(c, temp_mass, buf, perc);
    }
    *buf++ = '\0';
}

char *fill(int score, int width, char *buf, int flag, int perc, int spec) {
    if (score <= perc) {
        score = width - perc;
    } else {
        score = width - score;
    }
    if (flag == 5 && spec != 2 && spec != 3) {
        while (score > 0) {
            *buf++ = '0';
            score--;
        }
    } else if (flag == 5 && (spec == 2 || spec == 3) && perc == -1) {
        while (score > 0) {
            *buf++ = '0';
            score--;
        }
    } else {
        while (score > 0) {
            *buf++ = ' ';
            score--;
        }
    }
    *buf = '\0';
    return buf;
}

char *minus_or(int min, char *buf, int flag, int spec) {
    if (min == -1) {
        *buf++ = '-';
    } else if (flag == 2 && spec != 9 && spec != 11) {
        *buf++ = '+';
    }
    return buf;
}

char *record(int score, long long num, char *buf, int perc) {
    if (score < perc) {
        perc = perc - score;
        while (perc) {
            *buf++ = '0';
            perc--;
        }
    }
    while (score) {
        *buf++ = num % 10 + '0';
        num /= 10;
        score--;
    }
    return buf;
}

void *flags_e(char *buf, int width, int flag, int score, char *temp_buff_diff,
              int perc, int spec) {
    *buf = '\0';
    if (flag == 1) {
        s21_strcat(buf, temp_buff_diff);
        while (*buf != '\0') {
            buf++;
        }
        buf = fill(score, width, buf, flag, perc, spec);
    } else if (flag == 5) {
        if (*temp_buff_diff == '-' && score <= width) {
            *temp_buff_diff = '0';
            *buf++ = '-';
            score++;
        }
        buf = fill(score, width, buf, flag, perc, spec);
        s21_strcat(buf, temp_buff_diff);
    } else if (flag == 6) {
        if ((width <= score || perc >= width) && temp_buff_diff[0] != '-') {
            *buf++ = ' ';
        }
        buf = fill(score, width, buf, flag, perc, spec);
        s21_strcat(buf, temp_buff_diff);
    } else {
        buf = fill(score, width, buf, flag, perc, spec);
        s21_strcat(buf, temp_buff_diff);
    }
    return buf;
}

char *record_p(int c, char *temp_mass, char *buf, int perc) {
    if (c < perc) {
        perc = perc - c;
        while (perc != 1) {
            *buf++ = '0';
            perc--;
        }
    }
    while (c != -1) {
        *buf++ = temp_mass[c];
        temp_mass[c] = '\0';
        c--;
    }
    return buf;
}
