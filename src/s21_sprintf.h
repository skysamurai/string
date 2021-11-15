#ifndef SRC_S21_SPRINTF_H_
#define SRC_S21_SPRINTF_H_

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "parser.h"
#include "s21_string.h"

#ifndef S21_NULL
#define S21_NULL (void *)0
#endif /* S21_NULL */

int s21_sprintf_(char *str, const char *format, va_list args);

void int_number_to_char(char **str, unsigned long number, format_info *info);

void real_number_to_char(char **str, void *number, format_info *info);

/* specifiers parser */
void write_count_recorded_char(s21_size_t record_count, format_info *info,
                               va_list args);

/* cursoring means that function increment char pointer */
void put_char_cursoring(char **str, format_info *info, va_list args);
void put_string_cursoring(char **str, format_info *info, va_list args);
void put_pointer_cursoring(char **str, format_info *info, va_list args);
void put_hex_number_cursoring(char **str, format_info *info, va_list args);
void put_dec_number_cursoring(char **str, format_info *info, va_list args);
void put_udec_number_cursoring(char **str, format_info *info, va_list args);
void put_octo_number_cursoring(char **str, format_info *info, va_list args);

#endif  // SRC_S21_SPRINTF_H_
