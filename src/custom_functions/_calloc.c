#include "custom_functions.h"

/**
 * _calloc - allocates memory for an array, using malloc.
 * @nmemb: number of elements.
 * @size: size of each element.
 *
 * Return: pointer to the allocated memory.
 */
void *_calloc(size_t nmemb, size_t size)
{
	unsigned int i;
	char *memory;

	if (nmemb == 0 || size == 0)
		return (NULL);

	memory = malloc(nmemb * size);
	if (!memory)
		return (NULL);

	for (i = 0; i < (nmemb * size); i++)
		memory[i] = 0;

	return ((void *)memory);
}
