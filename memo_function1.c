#include "shell.h"

/**
 * *_memset - to fill memory
 * @s: pointer
 * @b: byte fo fill
 * @n: amount of bytes
 * Return: Success
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int u;

	for (u = 0; u < n; u++)
		s[u] = b;
	return (s);
}

/**
 * ffree - to free string of strings
 * @pp: string of strings
 */
void ffree(char **pp)
{
	char **f = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(f);
}

/**
 * _realloc - to reallocate memory
 * @ptr: pointer
 * @old_size: previous block size in byte
 * @new_size: new block size in byte
 *
 * Return: success
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *s;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	s = malloc(new_size);
	if (!s)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (s);
}
