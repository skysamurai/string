#ifndef SRC_S21_PARSER_
#define SRC_S21_PARSER_
#include "stdarg.h"

/* flags */
#define LEFT_JUSTIFY (1U << 0U)       /* '-' left alignment */
#define SHOW_SIGN (1U << 1U)          /* '+' display '+' or '-' */
#define SPACE_INSTEAD_SIGN (1U << 2U) /* ' ' replace '+' sign with space */
#define NUMBER_SYSTEM (1U << 3U)      /* '#' display number system */
#define ZERO_PADDING (1U << 4U)       /* '0' fill with zeros */

/* sprintf string format */
#define SIGNED (1U << 5U)             /* signed number */
#define CAPITALIZE (1U << 6U)         /* output in capital letters */
#define EXPONENT (1U << 7U)           /* output in exponential form */
#define FLOAT (1U << 8U)              /* float type */
#define SHORTEST_FLOAT

/* qualifier specifier */
#define NONE_SPEC ' '
#define LONG 'l'
#define SHORT 'h'
#define DOUBLE 'd'

struct format_info {
    unsigned flags;
    int field_width;
    int precision;
    int qualifier;
    int number_system;
};

void parse_format(const char **format, struct format_info *info, va_list args);
void p_flag(const char **format, struct format_info *info);
void p_width(const char **format, struct format_info *info, va_list args);
void p_precision(const char **format, struct format_info *info, va_list args);
void p_qualifier(const char **format, struct format_info *info);

int is_digit(char chr);
int is_hexdec_digit(char chr);
/*int is_specifer(char chr);*/
int atoi_cursoring(const char **cursor);
int get_dec_digit_count(int number);

#endif /* SRC_S21_PARSER_ */
