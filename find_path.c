#include "shell.h"

/**
 * find_path - to find cmd
 * @info: struct info
 * @pathstr: string path
 * @cmd: cmd to find
 *
 * Return: success
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int n = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[n] || pathstr[n] == ':')
		{
			path = dup_chars(pathstr, curr_pos, n);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[n])
				break;
			curr_pos = n;
		}
		n++;
	}
	return (NULL);
}

/**
 * is_cmd - to determine executable
 * @info: struct info
 * @path: file path
 *
 * Return: success
 */
int is_cmd(info_t *info, char *path)
{
	struct stat s;

	(void)info;
	if (!path || stat(path, &s))
		return (0);

	if (s.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - to duplicate characters
 * @pathstr: string path
 * @start: starting index
 * @stop: stopping index
 *
 * Return: seccuss
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int n = 0, k = 0;

	for (k = 0, n = start; n < stop; n++)
		if (pathstr[n] != ':')
			buf[k++] = pathstr[n];
	buf[k] = 0;
	return (buf);
}
