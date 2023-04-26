#include "hsh.h"


/**
 * add_node - add_node
 *
 * @head: list_t
 * @str: const char *
 * @num: int
 *
 * Return: linked list size
 */

list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = _MEM_ALLOCATE_(sizeof(list_t));
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
 * append_node_to_end - append node
 *
 * @head: list_t
 * @str: const char *
 * @num: integer
 *
 * Return: linked list size
 */

list_t *append_node_to_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = _MEM_ALLOCATE_(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}


/**
 * write_llist_str - write str element of singly linked list
 *
 * @h: list_t ptr to first head node
 *
 * Return: linked list size
 */

size_t write_llist_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_insert_str(h->str ? h->str : "(nil)");
		_insert_str("\n");
		h = h->next;
		i++;
	}
	return (i);
}


/**
 * del_node_at_idx - remove node at the index idx
 *
 * @head: list_t address of head node
 * @index: unsigned int
 *
 * Return: 1 S, 0 F
 */
int del_node_at_idx(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

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
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * clear_llist - clear list be freeing all nodes in list
 *
 * @head_ptr: list_t ** addr to head node
 *
 * Return: nothing
 */
void clear_llist(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}

