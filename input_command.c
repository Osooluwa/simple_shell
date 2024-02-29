#include "shell.h"

/**
 * _buffin - A function that buffers commands
 * @strprm: The parameter struct
 * @bff: The buffer address
 * @length: The length variable address
 *
 * Return: The "n" bytes read
 */
ssize_t _buffin(info_t *strprm, char **bff, size_t *length)
{
	ssize_t n = 0;
	size_t len = 0;

	if (!*length)
	{
		free(*bff);
		*bff = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		n = getline(bff, &len, stdin);
#else
		n = _getline(strprm, bff, &len);
#endif
		if (n > 0)
		{
			if ((*bff)[n - 1] == '\n')
			{
				(*bff)[n - 1] = '\0';
				n--;
			}
			strprm->linecount_flag = 1;
			cmmt_remover(*bff);
			add_histlist(strprm, *bff, strprm->histcount++);
			{
				*length = n;
				strprm->cmd_buf = bff;
			}
		}
	}
	return (n);
}

/**
 * _getinput - A function that gets a line, leaving out the newline
 * @strprm: The parameter struct
 *
 * Return: The "n" bytes read
 */

ssize_t _getinput(info_t *strprm)
{
	static char *bff;
	static size_t p, q, len;
	ssize_t n = 0;
	char **length = &(strprm->arg), *s;

	_putchar(BUF_FLUSH);
	n = _buffin(strprm, &bff, &len);
	if (n == -1)
		return (-1);
	if (len)
	{
		q = p;
		s = bff + p;

		chn_check(strprm, bff, &q, p, len);
		for (q = p; q < len; q++)
		{
			if (chain_delim(strprm, bff, &q))
				break;
		}

		p = q + 1;
			q++;
		if (p >= len)
		{
			p = len = 0;
			strprm->cmd_buf_type = CMD_NORM;
		}

		*length = s;
		return (_strlen(s));
	}

	*length = bff;
	return (n);
}

/**
 * rd_buff - A function that reads a buffer
 * @strprm: The parameter struct
 * @bff: The buffer
 * @t: buffer size
 *
 * Return: The "n" byte read
 */

ssize_t rd_buff(info_t *strprm, char *bff, size_t *t)
{
	ssize_t n = 0;

	if (*t)
		return (0);
	n = read(strprm->readfd, bff, READ_BUF_SIZE);
	if (n >= 0)
		*t = n;
	return (n);
}

/**
 * _getline - A function that gets the next line of input from STDIN
 * @strprm: The parameter struct
 * @ptr: The address of pointer to buffer
 * @length: The size of pointer buffer
 *
 * Return: "q" on success
 */
int _getline(info_t *strprm, char **ptr, size_t *length)
{
	static char bff[READ_BUF_SIZE];
	static size_t t, len;
	size_t m;
	ssize_t n = 0, q = 0;
	char *p = NULL, *size = NULL, *c;

	p = *ptr;
	if (p && length)
		q = *length;
	if (t == len)
		t = len = 0;

	n = rd_buff(strprm, bff, &len);
	if (n == -1 || (n == 0 && len == 0))
		return (-1);

	c = _strchr(bff + t, '\n');
	m = c ? 1 + (unsigned int)(c - bff) : len;
	size = _realloc(p, q, q ? q + m : m + 1);
	if (!size)
		return (p ? free(p), -1 : -1);

	if (q)
		_strncat(size, bff + t, m - t);
	else
		_strncpy(size, bff + t, m - t + 1);

	q += m - t;
	t = m;
	p = size;

	if (length)
		*length = q;
	*ptr = p;
	return (q);
}

/**
 * sigintHandler - A function for ctrl-C
 * @sig_num: The signal number
 *
 * Return: void
 */

void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("Osooluwasam$ ");
	_putchar(BUF_FLUSH);
}
