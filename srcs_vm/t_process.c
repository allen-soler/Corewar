/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_process.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 17:29:55 by allespag          #+#    #+#             */
/*   Updated: 2019/07/13 10:23:52 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

t_process		*new_process(int player, int pid)
{
	t_process	*new;

	if (!(new = (t_process *)malloc(sizeof(t_process))))
	{
		exit(EXIT_FAILURE);
	}
	ft_bzero(new, sizeof(t_process));
	ft_bzero(new->regs, sizeof(int) * REG_NUMBER);
	new->alive = 0;
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

void			free_processes(t_process *head)
{
	if (head)
	{
		if (head->next)
			free_processes(head->next);
		free(head);
	}
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
