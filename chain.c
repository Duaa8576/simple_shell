#include "shell.h"

/**
 * is_chain - test if current char is chain
 * @info: the parameter
 * @buf: the char buffer
 * @p: address of position
 *
 * Return: Success
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t k = *p;

	if (buf[k] == '|' && buf[k + 1] == '|')
	{
		buf[k] = 0;
		k++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[k] == '&' && buf[k + 1] == '&')
	{
		buf[k] = 0;
		k++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[k] == ';')
	{
		buf[k] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = k;
	return (1);
}

/**
 * check_chain - checks continue chaining
 * @info: the parameter
 * @buf: char buffer
 * @p: address
 * @i: position in buf
 * @len: length of buf
 *
 * Return: Success
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t k = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			k = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			k = len;
		}
	}

	*p = k;
}

/**
 * replace_alias - replces an aliases
 * @info: the parameter
 *
 * Return: Success
 */
int replace_alias(info_t *info)
{
	int r;
	list_t *node;
	char *p;

	for (r = 0; r < 10; r++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces var
 * @info: the parameter
 *
 * Return: Success
 */
int replace_vars(info_t *info)
{
	int r = 0;
	list_t *node;

	for (r = 0; info->argv[r]; r++)
	{
		if (info->argv[r][0] != '$' || !info->argv[r][1])
			continue;

		if (!_strcmp(info->argv[r], "$?"))
		{
			replace_string(&(info->argv[r]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[r], "$$"))
		{
			replace_string(&(info->argv[r]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[r][1], '=');
		if (node)
		{
			replace_string(&(info->argv[r]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[r], _strdup(""));

		}
		return (0);
}

/**
 * replace_string - replaces
 * @old: address
 * @new: string
 *
 * Return: Success
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
