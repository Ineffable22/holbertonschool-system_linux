#include "main.h"

/**
 * sorting - Creates nodes, store data and send to sort
 * @head: pointer to struct Sort with singly linked list
 * @node: node to insert into a singly linked list
 * @op: pointer to struc Option with printing options
 *
 * Return: Pointer to struct sort
 */
sort* sorting(sort *head, sort *node, option *op)
{
	sort *tmp = head;
	//printf("%d ordeeerr\n", op->order);
	if (op->order == 0)
	{
		while (tmp->next)
			(tmp) = (tmp)->next;
		(tmp)->next = node;
		return (head);
	}
	else if (op->order == 1)
	{
		node->next = head;
		head = node;
		return (head);
	}
	else if (op->order == 2)
	{
		if (node->st_time <= tmp->st_time)
		{
			while (tmp->next && (node->st_time <= tmp->st_time))
				tmp = tmp->next;
			if (tmp->next)
			{
				node->next = tmp->next;
				tmp->next = node;
			}
			else
				(tmp)->next = node;
			return (head);
		}
		else
		{
			node->next = head;
			head = node;
			return (head);
		}
	}
	else
	{
		if (node->st_size <= tmp->st_size)
		{
			while (tmp->next && (node->st_size <= tmp->st_size))
				tmp = tmp->next;
			if (tmp->next)
			{
				node->next = tmp->next;
				tmp->next = node;
			}
			else
				(tmp)->next = node;
			return (head);
		}
		else
		{
			node->next = head;
			head = node;
			return (head);
		}
		return (head);
	}

}
/*
sort* reverse_sort(sort *head)
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
sort* time_sort(sort *head)
{
	sort *prev = NULL;
	sort *next = NULL;
	sort *current = head;
	sort *tmp = head;
	int time = 0;
	int next_time = 0;

	printf("TIME\n");
	while(head)
	{
		time = (head->st_time);
		next_time = ((head->next)->st_time);
		tmp = head;
		printf("time = %d < next_time = %d // %d\n", time, next_time, time < next_time);
		while (time < next_time)
		{
			next = tmp->next;
			tmp->next = prev;
			prev = tmp;
			tmp = next;

			tmp = tmp->next;
			time = (tmp->st_time);
			next_time = ((tmp->next)->st_time);
		}
		head = head->next;
	}
	return (current);
}

sort* size_sort(sort *head)
{
	sort *prev = NULL;
	sort *next = NULL;
	sort *current = head;
	sort *tmp = head;
	int time = 0;
	int next_time = 0;

	while(head)
	{
		time = (head->st_size);
		next_time = ((head->next)->st_size);
		tmp = head;
		while (time > next_time)
		{
			next = tmp->next;
			tmp->next = prev;
			prev = tmp;
			tmp = next;

			tmp = tmp->next;
			time = (tmp->st_size);
			next_time = ((tmp->next)->st_size);
		}
		head = head->next;
	}
	return (current);
}
*/
