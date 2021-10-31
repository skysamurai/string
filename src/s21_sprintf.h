#ifndef SRC_S21_SPRINTF_
#define SRC_S21_SPRINTF_

#include "stdarg.h"
#include "stdio.h"
#include "string.h"

/* sprintf flags */
#define LEFT_ALIGMENT (1 << 0) /* выравние по левому краю */
#define SHOW_SIGN (1 << 1) /* отображение '+/-' */
#define REPLACE_SIGN_SPACE (1 << 2) /* замена знака '+' проблом */
#define SHOW_NUMBER_SYSTEM (1 << 3) /* отображение системы счисления */
#define ZERO_PADDING (1 << 4) /* заполнение пустого места пробелами */
/* sprintf string format */
#define SIGNED (1 << 5) /* может ли число быть знаковым */
#define CAPITALIZE (1 << 6) /* вывод заглавными буквами */
#define EXPONENT (1<< 7) /* вывод в экспоненциальной */
#define FLOAT (1 << 8) /* float тип */
/* number size format */
#define LONG 'l'
#define SHORT 'h'
#define LONG_LONG 'w'
#define LONG_DOUBLE 'L'


#ifndef __S21_NULL
#define S21_NULL (void*)0
#endif  // __S21_NULL

#ifdef __S21_WORDSIZE_8
typedef unsigned long long s21_size_t;
#endif
#ifdef __S21_WORDSIZE_4
typedef unsigned long s21_size_t;
#endif


struct format_info {
    int number_flags;    /* флаги для обработки числа */
    int field_width;            /* минимальная ширина вывода поля */
    int precision;              /* точность числа */
    int qualifier;              /* размерность */
    int number_system;          /* система счисления */
};


int s21_sprintf(char *str, const char *format, va_list args);
void int_number_to_char(char **str, unsigned long long int number, struct format_info *info);
void real_number_to_char(char **str, double number, struct format_info *info);

void parse_format_flag(const char **format, struct format_info *info);
void parse_field_width(const char **format, struct format_info *info, va_list args);
void parse_precision(const char **format, struct format_info *info, va_list args);
void parse_qualifier(const char **format, struct format_info *info);
void write_count_recorded_char(char element_count, struct format_info *info, va_list args);


int is_digit(char chr);
int is_hexdec_digit(char chr);
int atoi_cursoring(const char **cursor);


void put_char_cursoring(char **str, struct format_info *info, va_list args);
void put_string_cursoring(char **str, struct format_info *info, va_list args);
void put_pointer_cursoring(char **str, struct format_info *info, va_list args);
void put_hex_number_cursoring(char **str, struct format_info *info, va_list args);
void put_dec_number_cursoring(char **str, struct format_info *info, va_list args);
void put_udec_number_cursoring(char **str, struct format_info *info, va_list args);
void put_octo_number_cursoring(char **str, struct format_info *info, va_list args);

#endif /* SRC_S21_SPRINTF_ */
