#include "shell.h"

/**
 * do_cd - A function that changes the current directory using cd
 * @argstr: The argument struct
 *
 * Return: Always 0
 */

int do_cd(info_t *argstr)
{
	char *p, *dir, buffer[1024];
	int ch_dir;

	p = getcwd(buffer, 1024);
	if (!p)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!argstr->argv[1])
	{
		dir = _getenv(argstr, "HOME=");
		if (!dir)
			ch_dir =
				chdir((dir = _getenv(argstr, "PWD=")) ? dir : "/");
		else
			ch_dir = chdir(dir);
	}
	else if (_strcmp(argstr->argv[1], "-") == 0)
	{
		if (!_getenv(argstr, "OLDPWD="))
		{
			_puts(p);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(argstr, "OLDPWD=")), _putchar('\n');
		ch_dir =
			chdir((dir = _getenv(argstr, "OLDPWD=")) ? dir : "/");
	}
	else
		ch_dir = chdir(argstr->argv[1]);
	if (ch_dir == -1)
	{
		error_printer(argstr, "cannot cd to ");
		_eputs(argstr->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(argstr, "OLDPWD", _getenv(argstr, "PWD="));
		_setenv(argstr, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * cd_help - A function that changes the current directory of the process
 * @argstr: The argument struct
 *
 * Return: Always 0
 */

int cd_help(info_t *argstr)
{
	char **arr_arg;

	arr_arg = argstr->argv;
	_puts("help call is working. The function is yet to be implemented \n");
	if (0)
		_puts(*arr_arg);
	return (0);
}
