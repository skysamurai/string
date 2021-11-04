#ifndef SRC_S21_SPRINTF_
#define SRC_S21_SPRINTF_

#include "stdarg.h"
#include "stdio.h"
#include "string.h"

/* flags */
#define LEFT_JUSTIFY (1U << 0U)        /* left alignment */
#define SHOW_SIGN (1U << 1U)           /* display '+' or '-' */
#define SPACE_INSTEAD_SIGN (1U << 2U)  /* replace '+' sign with a space */
#define NUMBER_SYSTEM (1U << 3U)       /* display number system */
#define ZERO_PADDING (1U << 4U)        /* fill empty space right with zeros */
/* sprintf string format */
#define SIGNED (1U << 5U)      /* signed number */
#define CAPITALIZE (1U << 6U)  /* output in capital letters */
#define EXPONENT (1U << 7U)    /* output in exponential form */
#define FLOAT (1U << 8U)       /* float тип */
#define SHORTEST_FLOAT
/* qualifier specifier */
#define NONE_SPEC ' '
#define LONG 'l'
#define SHORT 'h'
#define DOUBLE 'd'
#define LONG_DOUBLE 'L'


#ifndef S21_NULL
#define S21_NULL (void*)0
#endif  /* S21_NULL */

#ifdef __S21_WORDSIZE_8
typedef unsigned long long s21_size_t;
#endif
#ifdef __S21_WORDSIZE_4
typedef unsigned long s21_size_t;
#endif


struct format_info {
    int flags;
    int field_width;
    int precision;
    int qualifier;
    int number_system;
};

int s21_sprintf(char *str, const char *format, va_list args);
void int_number_to_char(char **str, unsigned long number, struct format_info *info);
void real_number_to_char(char **str, double number, struct format_info *info);

/* specifiers parser */
void parse_format(const char **format, struct format_info *info, va_list args);
void parse_format_flag(const char **format, struct format_info *info);
void parse_field_width(const char **format, struct format_info *info, va_list args);
void parse_precision(const char **format, struct format_info *info, va_list args);
void parse_qualifier(const char **format, struct format_info *info);
void write_count_recorded_char(char element_count, struct format_info *info, va_list args);

/* support functions */
int is_digit(char chr);
int is_hexdec_digit(char chr);
int atoi_cursoring(const char **cursor);
int get_digit_count(int number);
void getSEM(unsigned int *sign, unsigned int *exponent, unsigned long long *mantiss, double number);

void put_char_cursoring(char **str, struct format_info *info, va_list args);
void put_string_cursoring(char **str, struct format_info *info, va_list args);
void put_pointer_cursoring(char **str, struct format_info *info, va_list args);
void put_hex_number_cursoring(char **str, struct format_info *info, va_list args);
void put_dec_number_cursoring(char **str, struct format_info *info, va_list args);
void put_udec_number_cursoring(char **str, struct format_info *info, va_list args);
void put_octo_number_cursoring(char **str, struct format_info *info, va_list args);

#endif  /* SRC_S21_SPRINTF_ */
