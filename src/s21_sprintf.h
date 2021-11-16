#ifndef S21_SPRINTF_
#define S21_SPRINTF_

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "parser.h"
#include "s21_string.h"

#ifndef S21_NULL
#define S21_NULL (void *)0
#endif  /* S21_NULL */

int s21_sprintf_(char *str, const char *format, va_list args);
void int_number_to_char(char **str, unsigned long number,
                        format_info *info);
void real_number_to_char(char **str, void *number, format_info *info);
void float_to_str(char *buffer, float number, format_info *info);
void double_to_str(char *buffer, void* number, format_info *info);

void write_count_recorded_char(s21_size_t record_count, format_info *info,
                               va_list args);

// helpful things 
int is_sign(char chr);


// cursoring means that function increment char pointer
void put_char_cursoring(char **str, format_info *info, va_list args);
void put_string_cursoring(char **str, format_info *info, va_list args);
void put_pointer_cursoring(char **str, format_info *info, va_list args);
void put_hex_number_cursoring(char **str, format_info *info,
                              va_list args);
void put_dec_number_cursoring(char **str, format_info *info,
                              va_list args);
void put_udec_number_cursoring(char **str, format_info *info,
                               va_list args);
void put_octo_number_cursoring(char **str, format_info *info,
                               va_list args);
void put_exp_number_cursoring(char **str, format_info *info,
                                   va_list args);
void put_flt_number_cursoring(char **str, format_info *info,
                                   va_list args);
#endif  // S21_SPRINTF_
