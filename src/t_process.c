#include "vm.h"

t_process		*new_process(int player)
{
	t_process	*new;

	if (!(new = (t_process *)malloc(sizeof(t_process))))
		return (NULL);
	ft_bzero(new, sizeof(t_process));
	new->player = player;
	new->regs[0] = player;
	new->next = NULL;
	return (new);
}

void	append_process(t_process **head, t_process *new)
{
	t_process *tmp;

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

void	delete_process(t_process **head, t_process *ptr)
{
	t_process *tmp;

	tmp = *head;
	if (tmp)
	{
		if (ptr == *head)
		{
			*head = (*head)->next;
			free(tmp);
			(*head)->prev = NULL;
		}
		while (tmp->next)
		{
			if (ptr == tmp->next)
			{
				tmp->next = ptr->next;
				if (ptr->next != NULL)
				{
					ptr->next->prev = tmp;
				}
				free(tmp);
			}
			tmp = tmp->next;
		}
	}
}
