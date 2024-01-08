#include "shell.h"

/**
 * *_strncpy - to copy string
 * @dest: destination
 * @src: source
 * @n: number or  characters
 * Return: S
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * *_strncat - to concatenate strings
 * @dest: first string
 * @src: second string
 * @n: maximam used bytes
 * Return: success
 */
char *_strncat(char *dest, char *src, int n)
{
	int p, q;
	char *s = dest;

	p = 0;
	q = 0;
	while (dest[p] != '\0')
		p++;
	while (src[q] != '\0' && q < n)
	{
		dest[p] = src[q];
		p++;
		q++;
	}
	if (q < n)
		dest[p] = '\0';
	return (s);
}

/**
 * *_strchr - to locate character
 * @s: string
 * @c: character
 * Return: success
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
