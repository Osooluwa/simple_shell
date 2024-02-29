#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

/**
 * free_ptr - A function that frees a pointer and set the address to NULL
 * @ptr: The address of the pointer to freed
 *
 * Return: 1 if freed, 0 if not.
 */

int free_ptr(void **ptr)
{
	if (ptr != NULL && *ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
