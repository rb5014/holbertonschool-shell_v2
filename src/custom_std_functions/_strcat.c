#include "custom_std_functions.h"

/**
 * _strcat - concatenates two strings.
 * @dest: destination string.
 * @src: source string.
 *
 * Return: pointer to the resulting string dest.
 */
char *_strcat(char *dest, const char *src)
{
	int dest_len = _strlen(dest);
	int i;

	for (i = 0; src[i] != '\0'; i++)
		dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';

	return (dest);
}
