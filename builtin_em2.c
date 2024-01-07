#include "shell.h"

/**
 * _myhistory - to display history list
 *
 * @info: structure
 *
 * Return: success
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - to remove alias
 * @info: parameter
 * @str: string
 *
 * Return: success
 */
int unset_alias(info_t *info, char *str)
{
	char *p, q;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	q = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = q;
	return (ret);
}

/**
 * set_alias - to set alias
 * @info: parameter
 * @str: string
 *
 * Return: success
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - to print alias
 * @node: alias node
 *
 * Return: success
 */
int print_alias(list_t *node)
{
	char *pr = NULL, *a = NULL;

	if (node)
	{
		pr = _strchr(node->str, '=');
		for (a = node->str; a <= pr; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(pr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - to mimics alias
 * @info: structure
 *
 * Return: success
 */
int _myalias(info_t *info)
{
	int r = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (r = 1; info->argv[r]; r++)
	{
		p = _strchr(info->argv[r], '=');
		if (p)
			set_alias(info, info->argv[r]);
		else
			print_alias(node_starts_with(info->alias, info->argv[r], '='));
	}

	return (0);
}
