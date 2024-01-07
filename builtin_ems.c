#include "shell.h"

/**
 * _myexit - to exit shell
 * @info: structure
 *
 * Return: success
 *
 */
int _myexit(info_t *info)
{
	int exit_check;

	if (info->argv[1])
	{
		exit_check = _erratoi(info->argv[1]);
		if (exit_check == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - to change directry
 * @info: structure
 *
 * Return: success
 */
int _mycd(info_t *info)
{
	char *b, *dir, buffer[1024];
	int chdir_ret;

	b = getcwd(buffer, 1024);
	if (!b)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME");
		if (!dir)
			chdir_ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(b);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD")), _putchar('\n');
		chdir_ret = chdir((dir = _getenv(info, "OLDPWD")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_puts(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - to chang current process directry
 * @info: structure
 *
 * Return: success
 */
int _myhelp(info_t *info)
{
	char **arg_arr;

	arg_arr = info->argv;
	_puts("help call works, Function not yet implmented \n");
	if (0)
		_puts(*arg_arr);
	return (0);
}
