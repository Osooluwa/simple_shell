#include "shell.h"

/**
 * _atoi - A function that converts a string to an integer
 * @s: The string to be converted
 *
 * Return: 0 if no number is converted,
 * otherwise return the converted number
 */

int _atoi(char *s)
{
	int n = 0, sign = 1, fg = 0, out;
	unsigned int result = 0;

	while (s[n] != '\0')
	{
		if (s[n] == ' ' && fg == 0)
		{
			continue;
		}
		if (s[n] == '-')
			sign *= -1;

		if (s[n] >= '0' && s[n] <= '9')
		{
			fg = 1;
			result *= 10;
			result += (s[n] - '0');
		}
		else if (fg == 1)
		{
			break;
		}
		n++;
	}

	if (sign == -1)
	{
		out = -result;
	}
	else
	{
		out = result;
	}
	return (out);
}
