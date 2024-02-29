#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

/**
 * _isalpha - A function that checks if a char is an alphabet
 * @c: The input character
 *
 * Return: 1 if c is an alphabet, 0 if not alphabet
 */

int _isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * _delim - checks if character is a delimeter
 * @c: character  to check
 * @delim: delimeter string
 * Return: if true return 1, if false return 0
 */

int _delim(char c, char *delim)
{
	return (strchr(delim, c) != NULL);
}

/**
 * interactive_mode - A function for shell in interactive mode
 * @stradd: The struct address
 *
 * Return: 1 if in interactive mode, 0 if not
 */

int interactive_mode(info_t *stradd)
{
	int is_stdin_tty = isatty(STDIN_FILENO);
	int readfd_limit = 2;

	if (is_stdin_tty && stradd->readfd <= readfd_limit)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
