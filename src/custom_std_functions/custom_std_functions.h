#ifndef CUSTOM_FUNCTIONS_H
#define CUSTOM_FUNCTIONS_H

#include <stdlib.h> /* For size_t, malloc, free, etc. */
#include <stdio.h> /* For printf in printenv*/


size_t _strlen(const char *s);
void *_calloc(size_t nmemb, size_t size);
char *_strcpy(char *dest, const char *src);
char *_strncpy(char *dest, const char *src, size_t n);
char *_strcat(char *dest, const char *src);
char *_strdup(const char *s);
char *_strndup(const char *s, size_t n);
void *_memcpy(void *dest, const void *src, size_t n);
void *_realloc(void *ptr, size_t old_size, size_t new_size);
int _strcmp(const char *s1, const char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_getenv(const char *name, char **env);
int _setenv(const char *name, const char *value, int overwrite, char ***env);
int _unsetenv(const char *name, char ***env);
int add_env_var(const char *name, const char *value,
				char ***env, int env_size);
int update_env_var(const char *name, const char *value, char ***env);
char *_strchr(char *s, char c);
char *_strstr(char *s, char *sub_s);
int _isnumber(char *str);
int _atoi(const char *str);

#endif /* CUSTOM_FUNCTIONS_H */
