#include "custom_std_functions.h"

/**
 * _strstr - locates a substring in a string.
 * @s: the string to be searched.
 * @sub_s: the string to locate.
 * Return: a pointer to the first occurrence of the
 * character c in the string s,
 * or NULL if the character is not found.
 */
char *_strstr(char *s, char *sub_s)
{
	char *p1, *p2;

	if (*sub_s == '\0')
	{
		return (s);
	}

	while (*s != '\0')
	{
		p1 = s;
		p2 = sub_s;

		while ((*p1 != '\0') && (*p2 != '\0') && (*p1 == *p2))
			p1++, p2++;

		if (*p2 == '\0')
			return (s);
		s++;
	}
	return (NULL);
}


