#include "shell.h"

/**
 * chain_delim - A function that tests if the current character
 * in a buffer is a chain delimeter
 * @strprm: The parameter struct
 * @bff: The character buffer
 * @pos: The address of current position in buffer
 *
 * Return: 1 if chain delimeter, 0 if not
 */

int chain_delim(info_t *strprm, char *bff, size_t *pos)
{
	size_t q = *pos;

	if (bff[q] == '|' && bff[q + 1] == '|')
	{
		bff[q] = 0;
		q++;
		strprm->cmd_buf_type = CMD_OR;
	}
	else if (bff[q] == '&' && bff[q + 1] == '&')
	{
		bff[q] = 0;
		q++;
		strprm->cmd_buf_type = CMD_AND;
	}
	else if (bff[q] == ';')
	{
		bff[q] = 0;
		strprm->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*pos = q;
	return (1);
}

/**
 * chain_checker - A function that checks to allow
 * continuous chaining based on last status
 * @strprm: The parameter struct
 * @bff: The character buffer
 * @pos: The address of current position in buffer
 * @n: The starting position in buffer
 * @length: The length of buffer
 *
 * Return: Void
 */

void chain_checker(info_t *strprm, char *bff, size_t *pos, size_t n, size_t length)
{
	size_t q = *pos;

	if (strprm->cmd_buf_type == CMD_AND)
	{
		if (strprm->status)
		{
			bff[n] = 0;
			q = length;
		}
	}
	if (strprm->cmd_buf_type == CMD_OR)
	{
		if (!strprm->status)
		{
			bff[n] = 0;
			q = length;
		}
	}

	*pos = q;
}

/**
 * alias_rep - A function that replaces an aliases in the tokenized string
 * @strprm: The parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */

int alias_rep(info_t *strprm)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_beginswith(strprm->alias, strprm->argv[0], '=');
		if (!node)
			return (0);
		free(strprm->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		strprm->argv[0] = p;
	}
	return (1);
}

/**
 * vrb_rep - A function that replaces variables in the tokenized string
 * @strprm: The parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */

int vrb_rep(info_t *strprm)
{
	int i = 0;
	list_t *node;

	for (i = 0; strprm->argv[i]; i++)
	{
		if (strprm->argv[i][0] != '$' || !strprm->argv[i][1])
			continue;

		if (!_strcmp(strprm->argv[i], "$?"))
		{
			str_rep(&(strprm->argv[i]),
					_strdup(dig_converter(strprm->status, 10, 0)));
			continue;
		}
		if (!_strcmp(strprm->argv[i], "$$"))
		{
			str_rep(&(strprm->argv[i]),
					_strdup(dig_converter(getpid(), 10, 0)));
			continue;
		}
		node = node_beginswith(strprm->env, &strprm->argv[i][1], '=');
		if (node)
		{
			str_rep(&(strprm->argv[i]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		str_rep(&strprm->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * str_rep - A function that replaces a string
 * @oldstr: The address of the string to be replaced
 * @newstr: The new string
 *
 * Return: 1 if replaced, 0 otherwise
 */

int str_rep(char **oldstr, char *newstr)
{
	free(*oldstr);
	*oldstr = newstr;
	return (1);
}
