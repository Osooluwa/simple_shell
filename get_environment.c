#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

/**
 * _getenviron - returns the string array copy of our environ
 * @argstr: The argument struct
 *
 * Return: Always 0
 */

char **_getenviron(info_t *argstr)
{
	if (!argstr->environ || argstr->new_env)
	{
		argstr->environ = str_list(argstr->env);
		argstr->new_env = 0;
	}

	return (argstr->environ);
}
