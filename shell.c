#include "shell.h"

/**
 * hsh - The main shell loop
 * @strprm: The parameter struct
 * @argv: The main () argument vector
 *
 * Return: 0 on success, 1 on error, or specified error code
 */

int hsh(info_t *strprm, char **argv)
{
	int builtin = 0;
	ssize_t n = 0;

	while (n != -1 && builtin != -2)
	{
		info_init(strprm);
		if (int_mode(strprm))
			_puts("OsooluwaSam$ ");
		_eputchar(BUF_FLUSH);
		n = _getinput(strprm);
		if (n != -1)
		{
			info_set(strprm, argv);
			builtin = builtin_cmd(strprm);
			if (builtin == -1)
				path_cmmd(strprm);
		}
		else if (int_mode(strprm))
			_putchar('\n');
		info_free(strprm, 0);
	}
	create_append(strprm);
	info_free(strprm, 1);
	if (!int_mode(strprm) && strprm->status)
		exit(strprm->status);
	if (builtin == -2)
	{
		if (strprm->err_num == -1)
			exit(strprm->status);
		exit(strprm->err_num);
	}
	return (builtin);
}
