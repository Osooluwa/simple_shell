#include "shell.h"

/**
 * _memset - A function that fills memory with a constant byte
 * @m: The pointer to the memory
 * @b: The byte to address
 * @f: The amount of bytes to be filled
 *
 * Return: pointer to the memory
 */

char *_memset(char *m, char b, unsigned int f)
{
	unsigned int n;

	for (n = 0; n < f; n++)
		m[n] = b;
	return (m);
}

/**
 * free_str - A function that frees a string of strings
 * @s: string of strings
 */
void free_str(char **s)
{
	char **p = s;

	if (!s)
		return;
	while (*s)
		free(*s++);
	free(p);
}

/**
 * _realloc - A function that reallocates a block of memory
 * @ptr: The pointer to previous allocated block of memory
 * @prev: The byte size of the previous block
 * @new_bk: The byte size of the new block
 *
 * Return: pointer to da ol'block nameen.
 */

void *_realloc(void *ptr, unsigned int prev, unsigned int new_bk)
{
	char *p;

	if (!ptr)
		return (malloc(new_bk));
	if (!new_bk)
		return (free(ptr), NULL);
	if (new_bk == prev)
		return (ptr);

	p = malloc(new_bk);
	if (!p)
		return (NULL);

	prev = prev < new_bk ? prev : new_bk;
	while (prev--)
		p[prev] = ((char *)ptr)[prev];
	free(ptr);
	return (p);
}
