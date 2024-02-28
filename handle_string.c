#include "shell.h"

/**
 * _strlen - A function that returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _strcmp - A function that compares strings
 * @s1: the first string
 * @s2: the second string
 *
 * Return: negative if s1 < s2,
 * positive if s1 > s2,
 * 0 if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * begin_with - A function that checks if needle begins with haystack
 * @string: The string to search
 * @substring: The substring to check
 *
 * Return: The address of next character or NULL
 */
char *begin_with(const char *string, const char *substring)
{
	while (*substring)
		if (*substring++ != *string++)
			return (NULL);
	return ((char *)string);
}

/**
 * _strcat - A function that concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
