#include <stdlib.h>

int     ft_isdigit(int c) { return (c > 47 && c < 58); }

int     ft_isprint(int c) { return ((c >= 33) && (c <= 126)); }

char    *ft_strchr(const char *s, int c)
{
    while (*s != (char)c)
    {
        if (!*s++)
            return (NULL);
    }
    return ((char*)s);
}

size_t  ft_strlen(const char *s)
{
    int len;
    int index;

    len = 0;
    index = 0;
    while (s[index] != '\0')
    {
        len++;
        index++;
    }
    return (len);
}

int     ft_atoi(const char *nptr)
{
    int value;
    int sign;
    int index;

    value = 0;
    sign = 1;
    index = 0;
    if ((nptr[index] == '+') || (nptr[index] == '-'))
    {
        if (nptr[index] == '-')
            sign = -1;
        index++;
    }
    while (ft_isdigit(nptr[index]))
    {
        value = value * 10 + (nptr[index] - '0');
        index++;
    }
    return (value * sign);
}

char    *ft_strncpy(char *dest, const char *src, size_t n)
{
    size_t index;

    index = 0;
    while (index < n)
    {
        if (src[index] != '\0')
        {
            *dest = src[index];
            index++;
        }
        else
            *dest = '\0';
		dest++;
    }
    dest -= index;
    return (dest);
}

char    *ft_substr(char const *s, unsigned int start, size_t len)
{
    char *dest;
	
    dest = NULL;
    if (ft_strlen(s) - start < len)
        return (dest);
    else
    {
        dest = malloc(sizeof(char) * len);
        if (dest)
            ft_strncpy(dest, s + start, len);
    }
    return (dest);
}