#include "custom_functions.h"

#include <limits.h>

/**
 * _atoi - converts a string to an integer.
 * Assumes that the input string is a valid number.
 * Checks for integer overflow.
 * @str: string to be converted.
 *
 * Return: the integer value of the string or INT_MAX/INT_MIN on overflow.
 */
int _atoi(const char *str)
{
	int res = 0;  /* Initialize result */
	int sign = 1; /* Initialize sign as positive */
	int i = 0;    /* Initialize index of first digit */

	/* If number is negative, then update sign */
	if (str[0] == '-')
	{
		sign = -1;
		i++; /* Also update index of first digit */
	}

	/* Iterate over each character of the string */
	for (; str[i] != '\0'; ++i)
	{
		/* Check for overflow */
		if ((res > INT_MAX / 10) ||
		    (res == INT_MAX / 10 && str[i] - '0' > INT_MAX % 10))
			return (sign == 1 ? INT_MAX : INT_MIN);
		res = res * 10 + str[i] - '0';
	}

	/* Return result with sign */
	return (sign * res);
}
