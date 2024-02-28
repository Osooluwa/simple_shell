#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

/**
 * _forkfunction - A function that executes fork
 * @strprm: The parameter struct
 *
 * Return: void
 */

void _forkfunction(info_t *strprm)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(strprm->path, strprm->argv, _getenviron(strprm)) == -1)
		{
			info_free(strprm, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(strprm->status));
		if (WIFEXITED(strprm->status))
		{
			strprm->status = WEXITSTATUS(strprm->status);
			if (strprm->status == 126)
				error_printer(strprm, "Permission not granted\n");
		}
	}
}
