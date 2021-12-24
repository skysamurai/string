#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_

#include <stdarg.h>

#include "stringtypes.h"

typedef struct format_info_t {
    unsigned flags;
    int field_width;
    int precision;
    int qualifier;
    int number_system;
} format_info;

#define SIZE 1000
/* states */
#define STATE_DEFAULT 0
#define STATE_FLAGS 1
#define STATE_WIDTH 2
#define STATE_PRECISION 3
#define STATE_MAX_PREC 4
#define STATE_LEN 5
#define STATE_SPEC 6
#define STATE_DONE 7

/* flags */
#define FLAG_MINUS            (1 << 0)
#define FLAG_PLUS             (1 << 1)
#define FLAG_SPACE            (1 << 2)
#define FLAG_NUM              (1 << 3)
#define FLAG_ZERO             (1 << 4)
#define FLAG_UP               (1 << 5)
#define FLAG_UNSIGNED         (1 << 6)
#define FLAG_SHORT            (1 << 7)
#define FLAG_LONG             (1 << 8)
#define FLAG_LONGDOUBLE       (1 << 9)
#define FLAG_MANTISSA         (1 << 10)
#define FLAG_G                (1 << 11)
#define FLAG_POINTER          (1 << 12)
#define FLAG_DOT              (1 << 13)
#define FLAG_EXIT             (1 << 14)

int countExp(long n);
int countExp_Less_than_One(long double fl);
int s21_sprintf(char* s, const char* format, ...);


char *s21_strtok(char *str, const char *delim);
void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memmove(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);
char *s21_strstr(const char *haystack, const char *needle);
s21_size_t s21_strspn(const char *str1, const char *str2);

char *s21_strpbrk(const char *str1, const char *str2);

char *s21_strrchr(const char *str, int c);
char *s21_strcat(char *dest, const char *src);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strcmp(const char *str1, const char *str2);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);

int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
int s21_strcmp(const char *str1, const char *str2);
char *s21_strcpy(char *dest, const char *src);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
s21_size_t s21_strlen(const char *str);

char *s21_strcat(char *dest, const char *src);

#endif  // SRC_S21_STRING_H_
