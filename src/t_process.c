#include "vm.h"

t_process		*new_process(int player, int alive, int pid)
{
	t_process	*new;

	if (!(new = (t_process *)malloc(sizeof(t_process))))
		return (NULL);
	ft_bzero(new, sizeof(t_process));
	ft_bzero(new->regs, sizeof(int) * REG_NUMBER);
	new->alive = alive;
	new->player = player;
	new->regs[0] = player;
	new->pid = pid + 1;
	new->cycle = 0;
	new->prev = NULL;
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
	t_process 	*tmp;

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
		new->prev = tmp;
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
		new->prev = NULL;
		*head = new;
	}
}

int			count_processes(t_process *head)
{
	if (!head) return 0;
	return 1 + count_processes(head->next);
}

void			delete_process(t_process **head, t_process *ptr)
{
	t_process 	*tmp;

	//DEBUG(ft_printf("There're %d processes still.\n", count_processes(*head)))
	tmp = *head;
	if (tmp)
	{
		if (ptr == *head)
		{
			*head = (*head)->next;
			free(tmp);
			if (*head)
				(*head)->prev = NULL;
		}
		while (tmp && tmp->next)
		{
			if (ptr == tmp->next)
			{
				if (ptr->next)
				{
					tmp->next = ptr->next;
					ptr->next->prev = tmp;
				}
				else
				{
					tmp->next = NULL;
				}
				free(ptr);
			}
			tmp = tmp->next;
		}
	}
}
