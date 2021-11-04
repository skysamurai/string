#include "s21_string.h"
#include <stdlib.h>
void *s21_memchr(const void *str, int c, s21_size_t n)
{
    void *res = S21_NULL;
    s21_size_t i = 0;
    while ((*((char *)str + i) != c) & (i < n))
    {
        i++;
    }
    if (*((char *)str + i) == c)
        res = (char *)str + i;
    return res;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n)
{
    int res = 0;
    s21_size_t i = 0;
    while ((res == 0) & (i < n))
    {
        res = *((char *)str1 + i) - *((char *)str2 + i);
        i++;
    }
    return res;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n)
{
    for (s21_size_t i = 0; i < n; i++)
    {
        *((char *)dest + i) = *((char *)src + i);
    }
    return dest;
}

void *s21_memmove(void *dest, const void *src, s21_size_t n)
{
    void *temp;
    temp = malloc(n * sizeof(char));
    s21_memcpy(temp, src, n);
    s21_memcpy(dest, temp, n);
    free(temp);
    return dest;
}

void *s21_memset(void *str, int c, s21_size_t n)
{
    for (s21_size_t i = 0; i < n; i++)
    {
        *((char *)str + i) = c;
    }
    return str;
}

char *s21_strchr(const char *str, int c)
{
    int i = 0;
    while ((*(str + i) != '\0') & ((*(str + i) != c)))
    {
        i++;
    }
    return (char *)str + i;
}

s21_size_t s21_strlen(const char *str)
{
    return (s21_strchr(str, 0) - str);
}

void *s21_to_upper(const char *str)
{
    int n = s21_strlen(str);
    void *temp = malloc(n * sizeof(char));
    for (int i = 0; i < n; i++)
    {
        if ((*((char *)str + i) > 96) & (*((char *)str + i) < 123))
        {
            *((char *)temp + i) = *((char *)str + i) - 32;
        }
        else
        {
            *((char *)temp + i) = *((char *)str + i);
        }
    }
    return (char *)temp;
}

void *s21_to_lower(const char *str)
{
    int n = s21_strlen(str);
    void *temp = malloc(n * sizeof(char));
    for (int i = 0; i < n; i++)
    {
        if ((*((char *)str + i) > 64) & (*((char *)str + i) < 91))
        {
            *((char *)temp + i) = *((char *)str + i) + 32;
        }
        else
        {
            *((char *)temp + i) = *((char *)str + i);
        }
    }
    return (char *)temp;
}

char *s21_strcpy(char *dest, const char *src)
{
    s21_size_t n = s21_strlen(src);
    s21_memcpy(dest, src, n);
    return dest;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index)
{
    s21_size_t n_src = s21_strlen(src), n_str = s21_strlen(str);
    void *temp;
    if (start_index > n_src - 1)
    {
        temp = S21_NULL;
    }
    else
    {
        int n = n_src + n_str;
        temp = malloc(n * sizeof(char));
        s21_memcpy(temp, (char *)src, start_index);
        s21_memcpy((char *)(temp + start_index), (char *)str, n_str);
        s21_memcpy(((char *)temp + start_index + n_str), ((char *)src + start_index), n_src - start_index);
    }
    return temp;
}

char *s21_strpbrk(const char *str1, const char *str2)
{
    char *returnVal = S21_NULL;
    int i = 0;
    while (str1[i] != '\0' && returnVal == S21_NULL)
    {
        for (int j = 0; str2[j] != '\0'; j++)
        {
            if (str1[i] == str2[j])
            {
                returnVal = ((char *)str1) + i;
                break;
            }
        }
        i++;
    }
    return returnVal;
}

void *s21_trim(const char *src, const char *trim_chars)
{
    int i = 0, j = s21_strlen(src);
    char tp[2] = {*(char *)(src + i), '\0'};
    while (s21_strpbrk(trim_chars, tp) != S21_NULL)
    {
        i++;
        tp[0] = *(char *)(src + i);
    }
    tp[0] = *(char *)(src + j - 1);
    while (s21_strpbrk(trim_chars, tp) != S21_NULL)
    {
        j--;
        tp[0] = *(char *)(src + j);
    }
    void *temp = malloc((j - i) * sizeof(char));
    s21_memcpy(temp, (char *)(src + i), j - i + 1);
    return temp;
}

char *s21_strstr(const char *haystack, const char *needle) {
    int i = 0, j = 0, n_haystack = s21_strlen(haystack), n_needle = s21_strlen(needle);
    while ((j < n_needle) && (i < n_haystack)) {
        j = 0;
        while (needle[j] != haystack[i]) {
            i++;
        }
        int k = i;
        while ((needle[j] == haystack[k]) && (k < n_haystack) && (j < n_needle)) {
            j++;
            k++;
        }
        i++; 
    }
    return (char *)haystack + i;
}