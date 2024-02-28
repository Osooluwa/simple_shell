#include "shell.h"

/**
 * _histfile - A function that gets the history file
 * @strprm: The parameter struct
 *
 * Return: allocated string containg history file
 */

char *_histfile(info_t *strprm)
{
	char *buf, *dir;

	dir = _getenv(strprm, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * create_append - A function that creates a new file or
 * appends to an existing file
 * @strprm: The parameter struct
 *
 * Return: 1 on success, -1 if otherwise
 */

int create_append(info_t *strprm)
{
	ssize_t fd;
	char *filename = _histfile(strprm);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = strprm->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * readhist - A function that reads history from file
 * @strprm: The parameter struct
 *
 * Return: histcount on success, 0 if otherwise
 */

int readhist(info_t *strprm)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = _histfile(strprm);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			add_histlist(strprm, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		add_histlist(strprm, buf + last, linecount++);
	free(buf);
	strprm->histcount = linecount;
	while (strprm->histcount-- >= HIST_MAX)
		rem_node(&(strprm->history), 0);
	renum_histlist(strprm);
	return (strprm->histcount);
}

/**
 * add_histlist - A function that adds entry to a history linked list
 * @strprm: The parameter struct
 * @bff: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */

int add_histlist(info_t *strprm, char *bff, int linecount)
{
	list_t *node = NULL;

	if (strprm->history)
		node = strprm->history;
	add_node_end(&node, bff, linecount);

	if (!strprm->history)
		strprm->history = node;
	return (0);
}

/**
 * renum_histlist - A function that renumbers the history linked list
 * @strprm: The parameter struct
 *
 * Return: The new histcount
 */

int renum_histlist(info_t *strprm)
{
	list_t *node = strprm->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (strprm->histcount = i);
}
