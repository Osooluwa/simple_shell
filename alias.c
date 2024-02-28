#include "shell.h"

/**
 * hist - A function that displays history list. It does one command by line,
 * and it is preceded by line numbers, starting from 0.
 * @argstr: The struct containing arguments for function prototypes.
 * Return: 0 always
 */

int hist(info_t *argstr)
{
	print_list_t(argstr->history);
	return (0);
}

/**
 * set_alias - A function that sets alias to string
 * @parstr: The parameter struct
 * @str: The string alias
 *
 * Return: 0 on success, 1 if failed
 */

int set_alias(info_t *parstr, char *str)
{
	char *set;

	set = _strchr(str, '=');
	if (!set)
	{
		return (1);
	}
	if (!*++set)
	{
		return (unset_alias(parstr, str));
	}
	set_alias(parstr, str);
	return (add_node(&(parstr->alias), str, 0) == NULL);
}

/**
 * unset_alias - A function that unsets alias from string
 * @parstr: The parameter struct
 * @str: The string alias
 *
 * Return: 0 on success, 1 on error
 */

int unset_alias(info_t *parstr, char *str)
{
	char *unset, p;
	int rtr;

	unset = _strchr(str, '=');
	if (!unset)
		return (1);
	p = *unset;
	*unset = 0;
	rtr = rem_node(&(parstr->alias),
		index_node(parstr->alias, node_beginswith(parstr->alias, str, -1)));
	*unset = p;
	return (rtr);
}


/**
 * print_alias -  A function that prints an alias string
 * @node: The alias node
 *
 * Return: 0 on success, 1 on error
 */

int print_alias(list_t *node)
{
	char *print = NULL, *q = NULL;

	if (node)
	{
		print = _strchr(node->str, '=');
		q = node->str;
		while (q <= print)
		{
			_putchar(*q);
			_putchar('\'');
			_puts(print + 1);
			_puts("'\n");
			q++;
		}
		return (0);
	}
	return (1);
}

/**
 * _alias - A function that acts as the alias builtin
 * @info: The parameter struct
 * 
 * Return: Always 0
 */
int _alias(info_t *parstr)
{
	int n = 0;
	char *s = NULL;
	list_t *node = NULL;

	if (parstr->argc == 1)
	{
		node = parstr->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (n = 1; parstr->argv[n]; n++)
	{
		s = _strchr(parstr->argv[n], '=');
		if (s)
			set_alias(parstr, parstr->argv[n]);
		else
			print_alias(node_beginswith(parstr->alias, parstr->argv[n], '='));
	}

	return (0);
}
