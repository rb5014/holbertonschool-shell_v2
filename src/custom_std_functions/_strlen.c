#include "custom_std_functions.h"

/**
 * _strlen - calculates the length of a string.
 * @s: string to calculate the length of.
 *
 * Return: length of the string.
 */
size_t _strlen(const char *s)
{
	size_t length = 0;

	while (s[length])
		length++;

	return (length);
}
