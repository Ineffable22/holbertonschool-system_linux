#include "main.h"

/**
 * sorting - Creates nodes, store data and send to sort
 * @head: pointer to struct Sort with singly linked list
 * @node: node to insert into a singly linked list
 * @op: pointer to struc Option with printing options
 *
 * Return: Pointer to struct sort
 */
sort *sorting(sort *head, sort *node, option *op)
{
	sort *tmp = head, *prev = NULL, *curr = NULL;

	if (op->order == 0 || op->order == 1)
	{
		while (tmp->next && _strcmp(node->r, tmp->r) > 0)
		{
			prev = tmp;
			(tmp) = (tmp)->next;
		}
		if (tmp->next)
		{
			curr = prev->next;
			prev->next = node;
			node->next = curr;
		}
		else
			(tmp)->next = node;
		return (head);
	}
	else if (op->order == 2)
		return (order_2(node, tmp, head));
	else
		return (order_3(node, tmp, head));
}

/**
 * reverse_sort - Sort nodes in reverse
 * @head: pointer to struct Sort with singly linked list
 *
 * Return: Pointer to struct sort
 */
sort *reverse_sort(sort *head)
{
	sort *prev = NULL;
	sort *next = NULL;

	while (head)
	{
		next = (head)->next;
		(head)->next = prev;
		prev = head;
		head = next;
	}
	head = prev;
	return (head);
}

/**
 * order_2 - Sort nodes
 * @node: node to insert into a singly linked list
 * @tmp: pointer to struct Sort with singly linked list
 * @head: pointer to struct Sort with singly linked list
 *
 * Return: Pointer to struct sort
 */
sort *order_2(sort *node, sort *tmp, sort *head)
{
	sort *curr = NULL, *prev = NULL;

	if (node->st_time <= tmp->st_time)
	{
		while (tmp->next && (node->st_time < tmp->st_time))
		{
			prev = tmp;
			tmp = tmp->next;
		}
		while (tmp->next && (node->st_time == tmp->st_time)
		&& _strcmp(node->r,tmp->r) > 0)
		{
			prev = tmp;
			tmp = tmp->next;
		}
		if (tmp->next)
		{
			curr = prev->next;
			prev->next = node;
			node->next = curr;
		}
		else
			(tmp)->next = node;
	}
	else
	{
		node->next = head;
		head = node;
	}
	return (head);
}

/**
 * order_3 - Sort nodes
 * @node: node to insert into a singly linked list
 * @tmp: pointer to struct Sort with singly linked list
 * @head: pointer to struct Sort with singly linked list
 *
 * Return: Pointer to struct sort
 */
sort *order_3(sort *node, sort *tmp, sort *head)
{
	sort *curr = NULL, *prev = NULL;

	if (node->st_size <= tmp->st_size)
	{
		while (tmp->next && (node->st_size < tmp->st_size))
		{
			prev = tmp;
			tmp = tmp->next;
		}
		while (tmp->next && (node->st_size == tmp->st_size)
		&& _strcmp(node->r,tmp->r) > 0)
		{
			prev = tmp;
			tmp = tmp->next;
		}
		if (tmp->next)
		{
			curr = prev->next;
			prev->next = node;
			node->next = curr;
		}
		else
			(tmp)->next = node;
	}
	else
	{
		node->next = head;
		head = node;
	}
	return (head);
}
