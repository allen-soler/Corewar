#include "vm.h"

t_process		*new_process(int player)
{
	t_process	*new;

	if (!(new = (t_process *)malloc(sizeof(t_process))))
		return (NULL);			// or maybe exit ????
	ft_bzero(new, sizeof(t_process));
	new->player = player;
	new->regs[0] = player;
	return (new);
}
