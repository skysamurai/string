#ifndef SRC_S21_VSPRINTF_
#define SRC_S21_VSPRINTF_


#include "stdarg.h"
#include "string.h"

/* sprintf flags */
#define LEFT_ALIGMENT (1 << 0) /* выравние по левому краю */
#define SHOW_SIGN (1 << 1) /* отображение '+/-' */
#define REPLACE_SIGN_SPACE (1 << 2) /* замена знака '+' проблом */
#define NUMBER_SYSTEM (1 << 3) /* отображение системы счисления */
#define ZERO_PAD (1 << 4) /* заполнение пустого места пробелами */
/* sprintf string format */
#define SIGN (1 << 5) /* знак числа */
#define CAPITALIZE (1 << 6) /* вывод заглавными буквами */
/* number size format */
#define U_LONG 'l'
#define LONG_LONG 'w'


#ifndef __S21_NULL
#define __S21_NULL (void*)0
#endif  // SRC_S21_VSPRINTF_

typedef unsigned long long s21_size_t;
#ifdef __S21_WORDSIZE_8
#endif
#ifdef __S21_WORDSIZE_4
typedef unsigned long s21_size_t;
#endif

typedef unsigned char s21_byte_t;

struct format_info {
    s21_byte_t number_flags;    /* флаги для обработки числа */
    int field_width;            /* минимальная ширина вывода поля */
    int precision;              /* точность числа */
    int qualifier;              /* размерность */
};

int s21_vsprintf(char *str, const char *format, va_list args);
void parse_format_flag(const char **format, struct format_info *info, va_list args);
void parse_field_width(const char **format, struct format_info *info, va_list args);
void parse_precision(const char **format, struct format_info *info, va_list args);
void parse_qualifier(const char **format, struct format_info *info, va_list args);

char *number_to_char(char *str, s21_size_t num, int base, int size, int precision, int type);
int is_digit(char chr);
int atoi_cursoring(const char **cursor);
void put_char_cursoring(char **str, struct format_info *info, va_list args);

#endif /* SRC_S21_VSPRINTF_ */
