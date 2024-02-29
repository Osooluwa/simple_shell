#include "shell.h"

/**
 * list_length - A function that determines the length of linked list
 * @h: The pointer to first node
 *
 * Return: size of list
 */

size_t list_length(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * str_list - A function that returns an array of strings of the list->str
 * @head: The pointer to first node
 *
 * Return: array of strings
 */

char **str_list(list_t *head)
{
	list_t *node = head;
	size_t i = list_length(head), j;
	char **strn;
	char *str;

	if (!head || !i)
		return (NULL);
	strn = malloc(sizeof(char *) * (i + 1));
	if (!strn)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strn[j]);
			free(strn);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strn[i] = str;
	}
	strn[i] = NULL;
	return (strn);
}


/**
 * print_list_t - A function that prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */

size_t print_list_t(const list_t *h)
{
	size_t n = 0;

	while (h)
	{
		_puts(dig_converter(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		n++;
	}
	return (n);
}

/**
 * node_beginswith - A function that returns node starting with prefix
 * @node: pointer to list head
 * @prefix: string
 * @c: the next character after prefix to match
 *
 * Return: The matched node or NULL
 */

list_t *node_beginswith(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = begin_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * index_node - A function that gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: The index of node or -1
 */

ssize_t index_node(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
