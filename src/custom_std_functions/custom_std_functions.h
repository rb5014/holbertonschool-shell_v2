#ifndef CUSTOM_FUNCTIONS_H
#define CUSTOM_FUNCTIONS_H

#include <stdlib.h> /* For size_t, malloc, free, etc. */
#include <stdio.h> /* For printf in printenv*/

extern char **environ;

size_t _strlen(const char *s);
void *_calloc(size_t nmemb, size_t size);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strdup(const char *s);
void *_memcpy(void *dest, const void *src, size_t n);
void *_realloc(void *ptr, size_t old_size, size_t new_size);
int _strcmp(const char *s1, const char *s2);
char *_getenv(const char *name);

char *_strchr(char *s, char c);
int _isnumber(char *str);
int _atoi(const char *str);

#endif /* CUSTOM_FUNCTIONS_H */
