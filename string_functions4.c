#include "shell.h"

/**
 * _strlen - return string length
 * @s: check string
 *
 * Return: success
 */
int _strlen(char *s)
{
	int o = 0;

	if (!s)
	return (0);

	while (*s++)
		o++;
	return (o);
}

/**
 * _strcmp - performs comparision
 * @s1: string no. 1
 * @s2: string no. 2
 *
 * Return: success
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - check needle
 * @haystack: to search
 * @needle: to find
 *
 * Return: success
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concatenates strings
 * @dest: destination
 * @src: sourse
 *
 * Return: success
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
