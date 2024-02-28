#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

/**
 * _unsetenv - A function that removes an environment variable
 * @argstr:The argument struct
 * @vrb: The string environment variable property
 *
 * Return: 1 on deletion, 0 if not
 */

int _unsetenv(info_t *argstr, char *vrb)
{
	list_t *node = argstr->env;
	size_t n = 0;
	char *s;

	if (!node || !vrb)
		return (0);

	while (node)
	{
		s = begin_with(node->str, vrb);
		if (s && *s == '=')
		{
			argstr->new_env = rem_node(&(argstr->env), n);
			n = 0;
			node = argstr->env;
			continue;
		}
		node = node->next;
		n++;
	}
	return (argstr->new_env);
}
