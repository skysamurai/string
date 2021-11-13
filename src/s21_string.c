#include "s21_string.h"

#include <errno.h>
#include <stdlib.h>

size_t s21_strspn(const char *str1, const char *str2) {
    int n_str1 = s21_strlen(str1), n_str2 = s21_strlen(str2), flag = 1;
    size_t res_len = 0;
    for (int i = 0; i < n_str1 && flag; i++) {
        if (s21_strchr(str2, (str1 + i)[0]) != NULL) {
            res_len++;
        } else {
            flag = 0;
        }
    }
    return res_len;
}

int s21_sprintf(char *str, char *format, ...) {
    va_list args;
    int changes_count;
    va_start(args, format);
    changes_count = s21_sprintf_(str, format, args);
    va_end(args);
    return changes_count;
}

void *s21_memchr(const void *str, int c, s21_size_t n) {
    void *res = S21_NULL;
    s21_size_t i = 0;
    while ((str != NULL) && (*((char *)str + i) != c) && (i < n)) {
        i++;
    }
    if ((str != NULL) && (*((char *)str + i) == c)) res = (char *)str + i;
    return res;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
    int res = 0, n_str1 = s21_strlen(str1), n_str2 = s21_strlen(str2);
    s21_size_t i = 0;
    if (n_str1 > n_str2) res = 1;
    if (n_str1 < n_str2) res = -1;
    if (n_str1 == n_str2) {
        while ((res == 0) & (i < n)) {
            res = *((char *)str1 + i) - *((char *)str2 + i);
            i++;
        }
    }
    return res;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
    s21_size_t i;
    for (i = 0; i < n; i++) {
        *((char *)dest + i) = *((char *)src + i);
    }
    *((char *)dest + i) = '\0';
    return dest;
}

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
    void *temp;
    temp = malloc(n * sizeof(char));
    s21_memcpy(temp, src, n);
    s21_memcpy(dest, temp, n);
    free(temp);
    return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
    for (s21_size_t i = 0; i < n; i++) {
        *((char *)str + i) = c;
    }
    return str;
}

char *s21_strchr(const char *str, int c) {
    char *res = S21_NULL;
    int i = 0;
    while (((str + i)[0] != c) && (((str + i)[0]) != '\0')) {
        i++;
    }
    if ((str + i)[0] == c) {
        res = (char *)(str + i);
    }
    return res;
}

s21_size_t s21_strlen(const char *str) { return (s21_strchr(str, 0) - str); }

void *s21_to_upper(const char *str) {
    int n = s21_strlen(str);
    void *temp = malloc(n * sizeof(char));
    for (int i = 0; i < n; i++) {
        if ((*((char *)str + i) > 96) & (*((char *)str + i) < 123)) {
            *((char *)temp + i) = *((char *)str + i) - 32;
        } else {
            *((char *)temp + i) = *((char *)str + i);
        }
    }
    return (char *)temp;
}

void *s21_to_lower(const char *str) {
    int n = s21_strlen(str);
    void *temp = malloc(n * sizeof(char));
    for (int i = 0; i < n; i++) {
        if ((*((char *)str + i) > 64) & (*((char *)str + i) < 91)) {
            *((char *)temp + i) = *((char *)str + i) + 32;
        } else {
            *((char *)temp + i) = *((char *)str + i);
        }
    }
    return (char *)temp;
}

char *s21_strcpy(char *dest, const char *src) {
    s21_size_t n = s21_strlen(src);
    s21_memcpy(dest, src, n);
    return dest;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
    s21_size_t n_src = s21_strlen(src), n_str = s21_strlen(str);
    void *temp;
    if (start_index > n_src - 1) {
        temp = S21_NULL;
    } else {
        int n = n_src + n_str;
        temp = malloc(n * sizeof(char));
        s21_memcpy(temp, (char *)src, start_index);
        s21_memcpy((char *)(temp + start_index), (char *)str, n_str);
        s21_memcpy(((char *)temp + start_index + n_str),
                   ((char *)src + start_index), n_src - start_index);
    }
    return temp;
}

char *s21_strpbrk(const char *str1, const char *str2) {
    char *returnVal = S21_NULL;
    int i = 0;
    while (str1[i] != '\0' && returnVal == S21_NULL) {
        for (int j = 0; str2[j] != '\0'; j++) {
            if (str1[i] == str2[j]) {
                returnVal = ((char *)str1) + i;
                break;
            }
        }
        i++;
    }
    return returnVal;
}

void *s21_trim(const char *src, const char *trim_chars) {
    void *temp;
    if (trim_chars == S21_NULL) {
        temp = (char *)src;
    } else {
        int i = 0, j = s21_strlen(src);
        char tp[2] = {*(char *)(src + i), '\0'};
        while (s21_strpbrk(trim_chars, tp) != S21_NULL) {
            i++;
            tp[0] = *(char *)(src + i);
        }
        tp[0] = *(char *)(src + j - 1);
        while (s21_strpbrk(trim_chars, tp) != S21_NULL) {
            j--;
            tp[0] = *(char *)(src + j);
        }
        temp = malloc((j - i) * sizeof(char));
        s21_memcpy(temp, (char *)(src + i), j - i + 1);
    }
    return temp;
}

char *s21_strrchr(const char *str, int c) {
    char *returnVal = NULL;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c) {
            returnVal = (((char *)str) + i);
        }
    }
    return returnVal;
}

char *s21_strtok(char *str, const char *delim) {
    char *result;
    char *start_token;
    char *end_token;
    static char *last_point = S21_NULL;

    if (str != S21_NULL) {
        last_point = str;
    }
    start_token = last_point;

    if (start_token != S21_NULL) {
        start_token +=
            s21_strspn(start_token, delim); /* clear delim from start */
        end_token = start_token;

        if (*start_token == '\0') {
            last_point = S21_NULL;
            result = S21_NULL;
        } else {
            result = start_token;
        }

        end_token =
            start_token + (s21_strpbrk(start_token, delim) - start_token);
        if (end_token != S21_NULL) {
            *end_token = '\0';
            last_point = end_token + 1;
        } else {
            last_point = S21_NULL;
            result = start_token;
        }

    } else {
        last_point = S21_NULL;
        result = S21_NULL;
    }

    return result;
}

int s21_strcmp(const char *str1, const char *str2) {
    int res = 0;
    int n_str1 = s21_strlen(str1), n_str2 = s21_strlen(str2), i = 0;
    if (n_str1 > n_str2) res = 1;
    if (n_str1 < n_str2) res = -1;
    if (n_str1 == n_str2) {
        while ((str1[i] == str2[i]) && (n_str1)) {
            ++i;
            --n_str1;
        }
        if (n_str1 != 0) res = str1[i] - str2[i];
    }
    return res;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
    int res = 0;
    int n_str1 = s21_strlen(str1), n_str2 = s21_strlen(str2), i = 0;
    if (n_str1 == n_str2) {
        while ((str1[i] == str2[i]) && (n) && (i < n_str1)) {
            ++i;
            --n;
        }
    }
    if (n != 0) res = str1[i] - str2[i];
    return res;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
    s21_size_t i = 0;
    while (i < n) {
        dest[i] = src[i];
        ++i;
        if (src[i] != 0) dest[i] = '\0';
    }
    return dest;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
    s21_size_t j, i = 0;
    int flag = 1;
    while ((str1[i] != 0) && (flag != 0)) {
        j = 0;
        while ((str2[j] != 0) && (flag != 0)) {
            if (str1[i] == str2[j]) flag = 0;
            ++j;
        }
        if (flag != 0) ++i;
    }
    return i;
}

const char *s21_strerror(int errnum) {
    static const char *err;
    int errmax = 133;
    static char errZero[100] = "Success";
    char unkerr[] = "Unknown error %d";
#ifdef __APPLE__
    errmax = 106;
    s21_strcpy(errZero, "Undefined error: 0");
    s21_strcpy(unkerr, "Unknown error: %d");
#endif
    if ((errnum > 0) && (errnum <= errmax)) {
        err = sys_errlist[errnum];
    } else if (errnum == 0)
        err = errZero;
    else if ((errnum > errmax) || (errnum < 0)) {
        static char errch[512];
        s21_sprintf(errch, unkerr, errnum);
        err = errch;
    }
    return err;
}

char *s21_strcat(char *dest, const char *src) {
    char *a = dest;
    for (; *dest != '\0'; dest++) {
    }
    for (; *src != '\0'; src++) {
    }
    *dest = *src;
    return a;
}

char *s21_strstr(const char *haystack, const char *needle) {
    char *res = S21_NULL;
    int i = 0, j = 0, n_haystack = s21_strlen(haystack),
        n_needle = s21_strlen(needle);
    while ((j < n_needle) && (i < n_haystack)) {
        j = 0;
        while (needle[j] != haystack[i]) {
            i++;
        }
        int k = i;
        while ((needle[j] == haystack[k]) && (k < n_haystack) &&
               (j < n_needle)) {
            j++;
            k++;
        }
        i++;
    }
    if (i != 0) res = (char *)haystack + i - 1;
    if (n_needle == 0) res = (char *)haystack;
    return res;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
    char *a = dest;
    s21_size_t i = 0;
    int n_dest = s21_strlen(dest), n_src = s21_strlen(src);
    for (; *dest != '\0'; dest++) {
    }
    for (i = 0; i < n && i < (n_src + n_dest); i++) {
        *(dest + i) = *(src + i);
    }
    return a;
}