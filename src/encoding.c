#include "../includes/asm.h"

void		nb_inst(t_par **lst)
{
	int		i;

	i = 0;
	while (*lst)
	{
		if (i == 0 && (*lst)->type == 6)
			break ;
		else if ((*lst)->type == 6 &&  i == 1)
			break ;
		i++;
		*lst = (*lst)->next;
	}
}

void	get_binary(t_par *lst, t_inst *inst, int nb)
{
	t_par	*tmp;
	int		i;
	int		bin;

	i = 0;
	bin = 6;
	tmp = lst;
	while (i < nb)
	{
		if (tmp->type == 1)
			inst->tab[1] = 0b01 << bin | inst->tab[1];
		else if (tmp->type == 2 || tmp->type == 3 || tmp->type == 5)
			inst->tab[1] = 0b10 << bin | inst->tab[1];
		else if (tmp->type == 4 || tmp->type == 15)
			inst->tab[1] = 0b11 << bin | inst->tab[1];
		tmp = tmp->next;
		bin -= 2;
		i++;
	}
	inst->size = 2;
}

void	encoding(t_par *lst, int fd)
{
	int		i;
	t_inst	inst;

	i = 0;
	ft_bzero(inst.tab, CHAMP_MAX_SIZE + 1);
	nb_inst(&lst);
	while (op_tab[i].name)
	{
		if (ft_strcmp(lst->param, op_tab[i].name) == 0)
			break ;
		i++;
	}
	inst.tab[0] = i + 1;
	get_binary(lst->next, &inst, op_tab[i].param_nb);
	write(fd, inst.tab, inst.size);
}
