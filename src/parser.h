#ifndef SRC_S21_PARSER_
#define SRC_S21_PARSER_
#include <stdarg.h>

/* flags */
#define LEFT_JUSTIFY (1U << 0U)       /* '-' left alignment */
#define SHOW_SIGN (1U << 1U)          /* '+' display '+' or '-' */
#define SPACE_INSTEAD_SIGN (1U << 2U) /* ' ' replace '+' sign with space */
#define NUMBER_SYSTEM (1U << 3U)      /* '#' display number system */
#define ZERO_PADDING (1U << 4U)       /* '0' fill with zeros */

/* sprintf string format */
#define SIGNED (1U << 5U)             /* signed number */
#define UNSIGNED (1U << 6U)           /* unsigned number */
#define CAPITALIZE (1U << 7U)         /* output in capital letters */
#define EXPONENT (1U << 8U)           /* output in exponential form */
#define FLOAT (1U << 9U)              /* float type */

/* qualifier specifier */
#define NONE ' '
#define LONG 'l'
#define SHORT 'h'
#define DOUBLE 'd'

typedef struct format_info_t {
    unsigned flags;
    int field_width;
    int precision;
    int qualifier;
    int number_system;
} format_info;

void parse_format(const char **format, format_info *info, va_list args);
void p_flag(const char **format, format_info *info);
void p_width(const char **format, format_info *info, va_list args);
void p_precision(const char **format, format_info *info, va_list args);
void p_qualifier(const char **format, format_info *info);

int is_digit(char chr);
int is_hexdec_digit(char chr);
int atoi_cursoring(const char **cursor);
int get_dec_digit_count(int number);

#endif /* SRC_S21_PARSER_ */
