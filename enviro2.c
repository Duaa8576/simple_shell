#include "shell.h"

/**
 * get_environ - to return string array
 * @info: structure
 *
 * Return: success
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - to remove environment
 * @info: structure
 * @var: string var property
 * Return: success
 *
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t n = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), n);
			n = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		n++;
	}
	return (info->env_changed);
}

/**
 * _setenv - to initialize new environment
 *
 * @info: structure
 *
 * @var: string env
 * @value: string value
 * Return: success
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node_b;
	char *c;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node_b = info->env;
	while (node_b)
	{
		c = starts_with(node_b->str, var);
		if (c && *c == '=')
		{
			free(node_b->str);
			node_b->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node_b = node_b->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
