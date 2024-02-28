#include "shell.h"

/**
 * builtin_cmd - A function that finds a builtin command
 * @strprm: The parameter struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit()
 */
int builtin_cmd(info_t *strprm)
{
	int i, built_in = -1;
	builtin_table table[] = {
		{"exit", exit_shell},
		{"env", _env},
		{"help", cd_help},
		{"history", hist},
		{"setenv", _setenviron},
		{"unsetenv", _unsetenviron},
		{"cd", do_cd},
		{"alias", _alias},
		{NULL, NULL}
	};

	for (i = 0; table[i].type; i++)
		if (_strcmp(strprm->argv[0], table[i].type) == 0)
		{
			strprm->line_count++;
			built_in = table[i].func(strprm);
			break;
		}
	return (built_in);
}
