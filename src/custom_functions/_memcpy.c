#include "custom_functions.h"

/**
 * _memcpy - Copy memory area
 * @dest: Pointer to the destination array where the content is to be copied
 * @src: Pointer to the source of data to be copied
 * @n: Number of bytes to copy
 *
 * Return: Pointer to the destination array
 */
void *_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char *d = dest;
	const unsigned char *s = src;

	while (n--)
	{
		*d++ = *s++;
	}

	return (dest);
}
