#include "main.h"

/**
 * split_token_with_delim - Splits a token by a given delimiter
 * @token: The token to be split
 * @delim: The delimiter to split the token by
 * @nb_args: Pointer to an int where the number of split parts is stored
 *
 * Return: Array of split parts of the token
 */
char **split_token_with_delim(char *token, char *delim, int *nb_args)
{
	char *found_op = _strstr(token, delim);

	if (found_op != NULL)
	{
		size_t index = found_op - token;
		/* Allocate memory for arguments + NULL terminator */
		char **args = malloc(sizeof(char *) * 4);

		if (index > 0)
		{ /* Delimiter is not at the beginning */
			args[(*nb_args)++] = _strndup(token, index);
		}

		args[(*nb_args)++] = _strdup(delim); /* Add the delimiter */

		if (index < _strlen(token) - _strlen(delim))
		{ /* Delimiter is not at the end */
			args[(*nb_args)++] = _strdup(found_op + _strlen(delim));
		}
		args[*nb_args] = NULL; /* Null-terminate the array */
		return (args);
	}
	else
	{
		return (NULL);
	}

}


