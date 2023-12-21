#include "custom_std_functions.h"

/**
 * _strdup - returns a pointer to a new string which is a duplicate of the
 * string s. Memory for the new string is obtained with malloc.
 * @s: string to duplicate.
 *
 * Return: pointer to the duplicated string.
 */
char *_strdup(const char *s)
{
	char *dup;
	int i, len;

	len = _strlen(s) + 1;
	dup = malloc(len);

	if (dup == NULL)
		return (NULL);

	for (i = 0; i < len; i++)
		dup[i] = s[i];

	return (dup);
}
