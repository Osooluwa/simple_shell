#include "shell.h"

/**
 * **strtow - A function that splits a string into words.
 * Repeat delimiters are ignored
 * @str: The input string
 * @d: The delimeter string
 *
 * Return: A pointer to an array of strings, or
 * NULL on failure
 */

char **strtow(char *str, char *d)
{
	int n, p, q, c, words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (n = 0; str[n] != '\0'; n++)
		if (!_delim(str[n], d) && (_delim(str[n + 1], d) || !str[n + 1]))
			words++;

	if (words == 0)
		return (NULL);
	s = malloc((1 + words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (n = 0, p = 0; p < words; p++)
	{
		while (_delim(str[n], d))
			n++;
		q = 0;
		while (!_delim(str[n + q], d) && str[n + q])
			q++;
		s[p] = malloc((p + 1) * sizeof(char));
		if (!s[p])
		{
			for (q = 0; q < p; q++)
				free(s[q]);
			free(s);
			return (NULL);
		}
		for (c = 0; c < q; c++)
			s[p][c] = str[n++];
		s[p][c] = 0;
	}
	s[p] = NULL;
	return (s);
}

#include "shell.h"

/**
 * **strtow2 - A function that splits a string into words.
 * Repeat delimiters are ignored
 * @str: The input string
 * @d: The delimeter string
 *
 * Return: A pointer to an array of strings, or
 * NULL on failure
 */

char **strtow2(char *str, char d)
{
	int n, p, q, c, words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (n = 0; str[n] != '\0'; n++)
		if ((str[n] != d && str[n + 1] == d) ||
				    (str[n] != d && !str[n + 1]) || str[n + 1] == d)
			words++;
	if (words == 0)
		return (NULL);
	s = malloc((1 + words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (n = 0, p = 0; p < words; p++)
	{
		while (str[n] == d && str[n] != d)
			n++;
		q = 0;
		while (str[n + q] != d && str[n + q] && str[n + q] != d)
			q++;
		s[p] = malloc((q + 1) * sizeof(char));
		if (!s[p])
		{
			for (q = 0; q < p; q++)
				free(s[q]);
			free(s);
			return (NULL);
		}
		for (c = 0; c < q; c++)
			s[p][c] = str[n++];
		s[p][c] = 0;
	}
	s[p] = NULL;
	return (s);
}
