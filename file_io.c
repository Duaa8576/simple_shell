#include "shell.h"

/**
 * get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return:Success
 */

char *get_history_file(info_t *info)
{
	char *buf, *d;

	d = _getenv(info, "HOME-");
	if (!d)
	return (NULL);
	buf = malloc(sizeof(char) * (_strlen(d) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, d);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - creates a file, or appends to file
 * @info: the parameter
 *
 * Return: Success
 */
int write_history(info_t *info)
{
	ssize_t f;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	f = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (f == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, f);
		_putfd('\n', f);
	}
	_putfd(BUF_FLUSH, f);
	close(f);
	return (1);
}

/**
 * read_history - reads history from file
 * @info: the parameter
 *
 * Return: Succuss
 */
int read_history(info_t *info)
{
	int r, last = 0, linecount = 0;
	ssize_t f, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	f = open(filename, O_RDONLY);
	free(filename);
	if (f == -1)
		return (0);
	if (!fstat(f, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(f, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(f);
	for (r = 0; r < fsize; r++)
		if (buf[r] == '\n')
		{
			buf[r] = 0;
			build_history_list(info, buf + last, linecount++);
			last = r + 1;
		}
	if (last != r)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - adds entry to linked list
 * @info: structure containing argument
 * @buf: buffer
 * @linecount: the history linecount
 *
 * Return: 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - renumbers history linked list
 * @info: structure containing argument
 *
 * Return: Success
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int n = 0;

	while (node)
	{
		node->num = n++;
		node = node->next;
	}
	return (info->histcount = n);
}
