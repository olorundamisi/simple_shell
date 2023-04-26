#include "hsh.h"


/**
 * list_len - find the size or length of list_t
 *
 * @h: list_t containing pointer to head node
 *
 * Return: list_t size
 */

size_t list_len(const list_t *h)
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
 * list_to_strings - generate array of `str` of list_t
 *
 * @head: list_t *
 *
 * Return: read the code
 */

char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = _MEM_ALLOCATE_(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = _MEM_ALLOCATE_(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * write_llist - write all elements of list_t
 *
 * @h: list_t * ptr
 *
 * Return: list_t size
 */

size_t write_llist(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_insert_str(change_num_base(h->num, 10, 0));
		_insert_character(':');
		_insert_character(' ');
		_insert_str(h->str ? h->str : "(nil)");
		_insert_str("\n");
		h = h->next;
		i++;
	}
	return (i);
}


/**
 * node_sw - node starts with
 *
 * @node: list_t *
 * @prefix: char * string
 * @c: character c
 *
 * Return: read teh code
 */

list_t *node_sw(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = _starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}


/**
 * get_node_idx - get_node_idx
 *
 * @head: list_t *
 * @node: list_t *
 *
 * Return: read the code
 */

ssize_t get_node_idx(list_t *head, list_t *node)
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
