#include "shell.h"

/**
 * _isalpha - to chaeck alphabetic character
 * @c: character
 * Return: Success
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * is_delim - to check delimeter
 * @c: char to check
 * @delim: delimeter string
 * Return: success
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _atoi - to convert string to integer
 * @s: string
 * Return: Success
 */

int _atoi(char *s)
{
	int n, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (n = 0; s[n] != '\0' && flag != 2; n++)
	{
		if (s[n] == '-')
			sign *= -1;

		if (s[n] >= '0' && s[n] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[n] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

/**
 * interactive - to return true in interactive mode
 * @info: struct address
 *
 * Return: succuss
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}
