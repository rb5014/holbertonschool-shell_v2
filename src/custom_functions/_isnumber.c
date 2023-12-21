#include "custom_functions.h"

/**
 * _isnumber - checks if a string is a valid integer number.
 * @str: string to check.
 *
 * Return: 1 if string is a number, 0 otherwise.
 */
int _isnumber(char *str)
{
	if (str == NULL || *str == '\0')
		return (0); /* String is NULL or empty */

	/* Handle negative numbers */
	if (*str == '-')
		str++;

	/* Check each character */
	while (*str != '\0')
	{
		if (*str < '0' || *str > '9')
			return (0); /* Not a number */
		str++;
	}

	return (1); /* String is a number */
}
