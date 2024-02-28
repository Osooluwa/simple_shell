#include "shell.h"

/**
 * _strtoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _strtoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * error_printer - A function that prints an error message
 * @strprm: The parameter struct
 * @err: The string that contains the specified error type
 *
 * Return: 0 if no numbers in string, or if number is converted
 * -1 on error
 */

void error_printer(info_t *strprm, char *err)
{
	_eputs(strprm->fname);
	_eputs(": ");
	dec_printer(strprm->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(strprm->argv[0]);
	_eputs(": ");
	_eputs(err);
}

/**
 * dec_printer - A function that prints a decimal
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */

int dec_printer(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * dig_converter - A function that converts digits
 * @num: The number
 * @base: The base
 * @flags: The argument flags
 *
 * Return: string
 */

char *dig_converter(long int num, int base, int flags)
{
	static char *arr;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	arr = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = arr[n % base];
		n /= base;
		}
	while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * cmmt_remover - A function replaces first instance of '#' with '\0'
 * @mdf: The address of the string to be modified
 *
 * Return: Always 0;
 */

void cmmt_remover(char *mdf)
{
	int n;

	for (n = 0; mdf[n] != '\0'; n++)
		if (mdf[n] == '#' && (!n || mdf[n - 1] == ' '))
		{
			mdf[n] = '\0';
			break;
		}
}
