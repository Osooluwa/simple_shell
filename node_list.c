#include "shell.h"
/**
 * add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new, *node;

	if (!head)
		return (NULL);

	node = *head;
	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);
	_memset((void *)new, 0, sizeof(list_t));
	new->num = num;
	if (str)
	{
		new->str = _strdup(str);
		if (!new->str)
		{
			free(new);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new;
	}
	else
		*head = new;
	return (new);
}

/**
 * print_str - A function that prints the str elements of a list_t linked list
 * @l: The pointer to first node
 *
 * Return: The "n" size of a list
 */
size_t print_str(const list_t *l)
{
	size_t n = 0;

	while (l)
	{
		_puts(l->str ? l->str : "(nil)");
		_puts("\n");
		l = l->next;
		n++;
	}
	return (n);
}

/**
 * rem_node - A function that deletes node at a given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int rem_node(list_t **head, unsigned int index)
{
	list_t *node, *previous_node;
	unsigned int n = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	for (; node; n++)
	{
		if (n == index)
		{
			previous_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		previous_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - A function that frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: no return
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	for (; node;)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
