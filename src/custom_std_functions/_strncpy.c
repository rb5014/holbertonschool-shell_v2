#include "custom_std_functions.h"

/**
 * _strncpy - copies the string pointed to by src, including the null byte,
 * to the buffer pointed to by dest.
 * @dest: destination string.
 * @src: source string.
 *
 * Return: pointer to dest.
 */
char *_strncpy(char *dest, const char *src, size_t n)
{
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[i] = src[i];
	for ( ; i < n; i++)
		dest[i] = '\0';

	return (dest);
}
