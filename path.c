#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

/**
 * path_cmmd - A function that finds a command in PATH
 * @strprm: The parameter struct
 *
 * Return: void
 */

void path_cmmd(info_t *strprm)
{
	char *path = NULL;
	int p, q;

	strprm->path = strprm->argv[0];

	if (strprm->linecount_flag == 1)
	{
		strprm->line_count++;
		strprm->linecount_flag = 0;
	}
	for (p = 0, q = 0; strprm->arg[p]; p++)
	{
		if (!_delim(strprm->arg[p], " \t\n"))
			q++;
	}
	if (!q)
		return;

	path = _findcmmd(strprm, _getenv(strprm, "PATH="), strprm->argv[0]);
	if (path)
	{
		strprm->path = path;
		_forkfunction(strprm);	}
	else
	{
	if ((int_mode(strprm) || _getenv(strprm, "PATH=")
				 || strprm->argv[0][0] == '/') && _iscmmd(strprm, strprm->argv[0]))
		_forkfunction(strprm);
		else if (*(strprm->arg) != '\n')
		{
			strprm->status = 127;
			error_printer(strprm, "not found\n");
		}
	}

}
