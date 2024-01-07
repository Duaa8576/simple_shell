#include "shell.h"

/**
 * _myenv - to print current environment
 * @info: structure
 *
 * Return: success
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - to get value
 * @info: structure
 * @name: env name
 *
 * Return: success
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *pr;

	while (node)
	{
		pr = starts_with(node->str, name);
		if (pr && *pr)
			return (pr);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - to initialize new environment
 *		or modify one
 * @info: structure
 *
 * Return: success
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect Nomber of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - to remove environment
 * @info: structure
 *
 * Return: success
 */
int _myunsetenv(info_t *info)
{
	int r;

	if (info->argc == 1)
	{
		_eputs("To few arguments.\n");
		return (1);
	}
	for (r = 1; r <= info->argc; r++)
		_unsetenv(info, info->argv[r]);

	return (0);
}

/**
 * populate_env_list - to populate env
 * @info: structure
 *
 * Return: success
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t eni;

	for (eni = 0; environ[eni]; eni++)
		add_node_end(&node, environ[eni], 0);
	info->env = node;
	return (0);
}
