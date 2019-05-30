#include "../includes/vm.h"

t_process		*new_process(int player)
{
	t_process	*new;

	if (!(new = (t_process *)malloc(sizeof(t_process))))
		return (NULL);			// or maybe exit ????
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
