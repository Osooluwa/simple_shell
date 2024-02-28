#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

/**
 * _strncpy - A function that copies a string
 * @dest: The destination string for the copied string
 * @src: The source string
 * @n: The amount of characters to be copied
 * Return: The concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int p, q;
	char *s = dest;

	for (p = 0; src[p] != '\0' && p < n - 1; p++)
	{
		dest[p] = src[p];

	}
	if (p < n)
	{
		for (q = p; q < n; q++)
		{
			dest[q] = '\0';
		}
	}
	return (s);
}

/**
 * _strncat - concatenates two strings
 * @dest: the first string
 * @src: the second string
 * @n: the amount of bytes to be maximally used
 * Return: the concatenated string
 */

char *_strncat(char *dest, char *src, int n)
{
	int p, q;
	char *s = dest;

	for (p = 0; dest[p] != '\0'; p++)
	for (q = 0; src[q] != '\0' && q < n; q++)
	{
		dest[p] = src[q];
	}
	if (q < n)
		dest[p] = '\0';
	return (s);
}

/**
 * _strchr - locates a character in a string
 * @s: the string to be parsed
 * @c: the character to look for
 * Return: (s) a pointer to the memory area s
 */

char *_strchr(char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
		{
			return (s);
		}
		s++;
	}
	return (NULL);
}
