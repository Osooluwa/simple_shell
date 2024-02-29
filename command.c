#include "shell.h"

/**
 * _iscmmd - A function that determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int _iscmmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * _dupchars - A function that duplicates characters
 * @strpth: The PATH string
 * @begin: The starting index
 * @end: The stopping index
 *
 * Return: pointer to new buffer
 */
char *_dupchars(char *strpth, int begin, int end)
{
	static char buf[1024];
	int p = begin, q = 0;

	while (p < end)
	{
		if (strpth[p] != ':')
		{
			buf[q++] = strpth[p];
		}
		p++;
	}
	buf[q] = '\0';
	return (buf);
}

/**
 * _findcmmd - A function that finds command in the PATH string
 * @info: The info struct
 * @strpth: The PATH string
 * @cmd: The command to find
 *
 * Return: full path of cmd if found or NULL
 */
char *_findcmmd(info_t *info, char *strpth, char *cmd)
{
	int n = 0, current = 0;
	char *path;
	int exitCondition = 0;

	if (!strpth)
		return (NULL);
	if ((_strlen(cmd) > 2) && begin_with(cmd, "./"))
	{
		if (_iscmmd(info, cmd))
			return (cmd);
	}
	while (!exitCondition)
	{
		if (!strpth[n] || strpth[n] == ':')
		{
			path = _dupchars(strpth, current, n);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (_iscmmd(info, path))
				return (path);
			if (!strpth[n])
				break;
			current = n;
		}
		n++;
	}
	return (NULL);
}
