#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_
// H FILE
int s21_strcmp(const char *str1, const char *str2);
int s21_strncmp(const char *str1, const char *str2, size_t n);
char *s21_strcpy(char *dest, const char *src);
char *s21_strncpy(char *dest, const char *src, size_t n);
size_t s21_strcspn(const char *str1, const char *str2);
size_t s21_strlen(const char *str);

#endif  // SRC_S21_STRING_H_
