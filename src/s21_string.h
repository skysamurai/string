#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_

#ifndef S21_SIZE_T
#define S21_SIZE_T
typedef unsigned int s21_size_t;
#endif  // S21_SIZE_T
#ifndef S21_NULL
#define S21_NULL ((void *)0)
#endif  // S21_NULL
void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memmove(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strchr(const char *str, int c);
s21_size_t s21_strlen(const char *str);
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);
char *s21_strcpy(char *dest, const char *src);

char *s21_strpbrk(const char *str1, const char *str2);

char *s21_strrchr(const char *str, int c);

#endif  // SRC_S21_STRING_H_
