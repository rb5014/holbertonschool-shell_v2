#include "custom_std_functions.h"

/**
 * _strndup - Duplicates a string up to a maximum number of characters.
 * @s: The string to be duplicated.
 * @n: The maximum number of characters to duplicate.
 * Return: On success, returns a pointer to the duplicated string. Returns NULL
 * if the memory allocation fails or if s is NULL.
 */
char *_strndup(const char *s, size_t n)
{
	size_t len = _strlen(s), i;
	char *dup = NULL;

	if (n < len)
	{
		len = n;
	}

	dup = malloc(len + 1); /* +1 for null terminator */

	if (dup == NULL)
	{
		return (NULL);
	}

	for (i = 0; i < len; i++)
	{
		dup[i] = s[i];
	}
	dup[len] = '\0'; /* Ensure null termination */

	return (dup);
}
