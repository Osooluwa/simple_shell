#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

/**
 * info_init - A function that initializes info_t struct
 * @info: struct address
 *
 * Return: No return
 */

void info_init(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * info_set - A function that initializes info_t struct
 * @info: struct address
 * @agv: argument vector
 *
 * Return: No return
 */
void info_set(info_t *info, char **agv)
{
	int n = 0;

	info->fname = agv[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (n = 0; info->argv && info->argv[n]; n++)
			;
		info->argc = n;

		alias_rep(info);
		vrb_rep(info);
	}
}

/**
 * info_free - A function that frees info_t struct fields
 * @info: The struct address
 * @af: true if it is freeing all fields
 *
 * Return: No return
 */
void info_free(info_t *info, int af)
{
	free_str(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (af)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		free_str(info->environ);
			info->environ = NULL;
		free_ptr((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
