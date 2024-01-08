#include "shell.h"

/**
 * _erratoi - to convert string to integer
 * @s: string
 *
 * Return: success
 */
int _erratoi(char *s)
{
	int n = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (n = 0; s[n] != '\0'; n++)
	{
		if (s[n] >= '0' && s[n] <= '9')
		{
			result *= 10;
			result += (s[n] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - to print error message
 * @info: parameter
 * @estr: string with an error
 *
 * Return: success
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - to print decimal
 * @input: input
 * @fd: filedescriptor
 *
 * Return: succuss
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int n, count = 0;
	unsigned int _abc_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abc_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abc_ = input;
	current = _abc_;
	for (n = 1000000000; n > 1; n /= 10)
	{
		if (_abc_ / n)
		{
			__putchar('0' + current / n);
			count++;
		}
		current %= n;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - to convert function
 * @num: number
 * @base: base
 * @flags: flags
 *
 * Return: success
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long s = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		s = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[s % base];
		s /= base;
	} while (s != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - to replace first instance of '#' with '\0'
 * @buf: address
 *
 * Return: success
 */
void remove_comments(char *buf)
{
	int n;

	for (n = 0; buf[n] != '\0'; n++)
		if (buf[n] == '#' && (!n || buf[n - 1] == ' '))
		{
			buf[n] = '\0';
			break;
		}
}
