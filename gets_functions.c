#include "shell.h"

/**
 * input_buf - to buffer chain commands
 * @info: parameter
 * @buf: buffer address
 * @len: len var address
 *
 * Return: success
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t c = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in buffer, fiil it */
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		c = getline(buf, &len_p, stdin);
#else
		c = _getline(info, buf, &len_p);
#endif
		if (c > 0)
		{
			if ((*buf)[c - 1] == '\n')
			{
				(*buf)[c - 1] = '\0';
				c--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/*if (_strchr(*buf, ';')) is this a command chain */
			{
				*len = c;
				info->cmd_buf = buf;
			}
		}
	}
	return (c);
}

/**
 * get_input - to get line
 * @info: parameter
 *
 * Return: success
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t n = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	n = input_buf(info, &buf, &len);
	if (n == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (n);
}

/**
 * read_buf - to read buffer
 * @info: parameter
 * @buf:buffer
 * @i: size
 *
 * Return: success
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t n = 0;

	if (*i)
		return (0);
	n = read(info->readfd, buf, READ_BUF_SIZE);
	if (n >= 0)
		*i = n;
	return (n);
}

/**
 * _getline - to get next line
 * @info: parameter
 * @ptr: pointer address to the buffer
 * @length: preallocate buffer size
 *
 * Return: success
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t n, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (n == len)
		n = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + n, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + n, k - n);
	else
		_strncpy(new_p, buf + 1, k - n + 1);

	s += k - 1;
	n = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - to block ctrl-C
 * @sig_num: signal number
 *
 * Return: success
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
