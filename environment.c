#include "shell.h"

/**
 * _env - A function that prints the current environment
 * @argstr: The argument struct
 *
 * Return: Always 0
 */

int _env(info_t *argstr)
{
	print_str(argstr->env);
	return (0);
}

/**
 * _getenv - A function that gets the value of an environment variable
 * @argstr: The argument struct
 * @name: The environment variable name
 *
 * Return: The environment value
 */

char *_getenv(info_t *argstr, const char *name)
{
	list_t *node =argstr->env;
	char *s;

	while (node)
	{
		s = begin_with(node->str, name);
		if (s && *s)
			return (s);
		node = node->next;
	}
	return (NULL);
}

/**
 * _setenviron - A function that initializes a new environment variable or
 * modifies an existing one
 * @argstr: The argument struct
 *
 * Return: Always 0
 */

int _setenviron(info_t *argstr)
{
	if (argstr->argc != 3)
	{
		printf("Wrong number of arguments\n");
		return (1);
	}
	if (_setenv(argstr, argstr->argv[1], argstr->argv[2]))
		return (0);
	return (1);
}

/**
 * _unsetenviron - A function that removes an environment variable
 * @argstr: The argument struct
 *
 * Return: Always 0
 */

int _unsetenviron(info_t *argstr)
{
	int n;

	if (argstr->argc == 1)
	{
		_eputs("Arguments too few\n");
		return (1);
	}
	for (n = 1; n <= argstr->argc; n++)
		_unsetenv(argstr, argstr->argv[n]);

	return (0);
}

/**
 * pop_environ_list - A function that populates environment linked list
 * @argstr: The argument struct
 *
 * Return: Always 0
 */

int pop_environ_list(info_t *argstr)
{
	list_t *node = NULL;
	size_t t;

	for (t = 0; environ[t]; t++)
		add_node_end(&node, environ[t], 0);
	argstr->env = node;
	return (0);
}
