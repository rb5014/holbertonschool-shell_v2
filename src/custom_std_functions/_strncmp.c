#include "custom_std_functions.h"

/**
 * _strncmp - compares up to n characters of two strings.
 * @s1: first string.
 * @s2: second string.
 * @n: maximum number of characters to compare.
 *
 * Return: 0 if the first n characters of s1 and s2 are equal, 
 * another number if not, or if the comparison ends before n characters
 * due to the end of a string.
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i = 0;

    while (i < n && s1[i] == s2[i])
    {
        if (s1[i] == '\0')
            return (0);
        i++;
    }

    if (i == n)
        return (0); /* The first n characters are equal */

    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
