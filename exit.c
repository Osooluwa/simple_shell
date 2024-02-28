#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

/**
 * exit_shell - A function that exits the shell
 * @argstr: The argument struct
 *
 * Return: Any given exit status return exit,
 * 0 if info.argv[0] != "exit"
 */

int exit_shell(info_t *argstr)
{
	int ex_it;

	if (argstr->argv[1])
	{
		ex_it = _strtoi(argstr->argv[1]);
		if (ex_it == -1)
		{
			argstr->status = 2;
			error_printer(argstr, "Illegal number: ");
			_eputs(argstr->argv[1]);
			_eputchar('\n');
			return (1);
		}
		argstr->err_num = _strtoi(argstr->argv[1]);
		return (-2);
	}
	argstr->err_num = -1;
	return (-2);
}
