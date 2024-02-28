#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

/**
 * _setenv - A functions that initializes a new environment variable or
 * modifies an existing one
 * @argstr: The argument struct
 * @vrb: The string environment variable property
 * @value: The string environment variable value
 *
 *  Return: Always 0
 */

int _setenv(info_t *argstr, char *vrb, char *value)
{
	char *bff = NULL;
	list_t *node;
	char *s;

	if (!vrb || !value)
		return (0);

	bff = malloc(_strlen(vrb) + _strlen(value) + 2);
	if (!bff)
		return (1);
	_strcpy(bff, vrb);
	_strcat(bff, "=");
	_strcat(bff, value);
	node = argstr->env;
	while (node)
	{
		s = begin_with(node->str, vrb);
		if (s && *s == '=')
		{
			free(node->str);
			node->str = bff;
			argstr->new_env = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(argstr->env), bff, 0);
	free(bff);
	argstr->new_env = 1;
	return (0);
}
