#ifndef FT_FT_H

#define FT_FT_H

#include <stddef.h>

int     ft_isdigit(int c);

int     ft_isprint(int c);

size_t  ft_strlen(const char *s);

int     ft_atoi(const char *nptr);

char    *ft_strchr(const char *s, int c);

char    *ft_substr(char const *s, unsigned int start, size_t len);

#endif