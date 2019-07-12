/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_process.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allespag <allespag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 17:29:55 by allespag          #+#    #+#             */
/*   Updated: 2019/07/09 17:32:56 by allespag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_process		*new_process(int player, int alive, int pid)
{
	t_process	*new;

	if (!(new = (t_process *)malloc(sizeof(t_process))))
		return (NULL);
	ft_bzero(new, sizeof(t_process));
	ft_bzero(new->regs, sizeof(int) * REG_NUMBER);
	new->alive = 0; // this is wrong
	new->player = player;
	new->op_code = -1;
	new->pid = pid + 1;
	new->cycle = 0;
	new->next = NULL;
	return (new);
}

void			duplicate_process(t_process *dst, t_process *src)
{
	ft_memcpy(dst->regs, src->regs, sizeof(int) * REG_NUMBER);
	dst->carry = src->carry;
	dst->alive = src->alive;
	dst->player = src->player;
	dst->color = src->color;
}

void			append_process(t_process **head, t_process *new)
{
	t_process	*tmp;

	if (*head == NULL)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = new;
	}
}

void			push_process_front(t_process **head, t_process *new)
{
	t_process *tmp;

	if (*head == NULL)
		*head = new;
	else
	{
		tmp = *head;
		new->next = tmp;
		*head = new;
	}
}

// TODO: we remove this for the norm
int			count_processes(t_process *head)
{
	if (!head) return 0;
	return 1 + count_processes(head->next);
}

void			delete_process(t_process **head, t_process *ptr)
{
	t_process	*tmp;

	tmp = *head;
	if (tmp)
	{
		if (ptr == *head)
		{
			*head = (*head)->next;
			free(tmp);
			tmp = NULL;
		}
		while (tmp && tmp->next)
		{
			if (ptr == tmp->next)
			{
				if (ptr->next)
					tmp->next = ptr->next;
				else
					tmp->next = NULL;
				free(ptr);
				ptr = NULL;
			}
			tmp = tmp->next;
		}
	}
}
