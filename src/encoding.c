#include "../includes/asm.h"

static size_t djb_hash(const char* cp)
{
	size_t	hash;

	hash = 5381;
	while (*cp)
		hash = 33 * hash ^ (unsigned char)*cp++;
	return (hash);
}

int		nb_op(char *src)
{
	int	i;

	i = 0;
	while (op_tab[i].name)
	{
		if (djb_hash(src) == djb_hash(op_tab[i].name))
			break ;
		i++;
	}
	return (i);
}

void	get_binary(t_par *lst, t_inst *inst, int nb, int size)
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
			inst->tab[size] = 0b01 << bin | inst->tab[size];
		else if (tmp->type == 2 || tmp->type == 3 || tmp->type == 5
				|| tmp->type == 15)
			inst->tab[size] = 0b10 << bin | inst->tab[size];
		else if (tmp->type == 4 || tmp->type == 9)
			inst->tab[size] = 0b11 << bin | inst->tab[size];
		tmp = tmp->next;
		bin -= 2;
		i++;
	}
	inst->size += 1;
}

int		counting_label(t_par *lst, int nb)
{
	int		i;
	t_par	*tmp;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		if (tmp->type == 6)
			i = op_tab[nb].encoding_byte > 0 ? i + 2 : i + 1;
		else if (tmp->type == 1)
			i += 1;
		else if (tmp->type == 2 || tmp->type == 3 || tmp->type == 5
				|| tmp->type == 15)
		{
			if (tmp->type == 2 || tmp->type == 15)
				i += 2;
			else if (tmp->type == 3 || tmp->type == 5)
				i += 4;
		}
		else if (tmp->type == 4 || tmp->type == 9)
			i += 2;
		tmp = tmp->next;
	}
	return (i);
}

int		testing(t_par *lst, t_par *n, int nb)
{
	t_par *tmp;
	int i;
	int	j;
	tmp = n;

	i = 0;
	j = counting_label(lst, nb);
	while (tmp)
	{
		if (lst == tmp)
			break ;
		if (tmp->type == 6)
			i = op_tab[nb].encoding_byte > 0 ? i + 2 : i + 1;
		else if (tmp->type == 1)
			i += 1;
		else if (tmp->type == 2 || tmp->type == 3 || tmp->type == 5
				|| tmp->type == 15)
		{
			if (tmp->type == 2 || tmp->type == 15)
				i += 2;
			else if (tmp->type == 3 || tmp->type == 5)
				i += 4;
		}
		else if (tmp->type == 4 || tmp->type == 9)
			i += 2;
		tmp = tmp->next;
	}
	if (i < j)
		i = -(j - i);
	return (i);
}

void	direct_lab(t_par *lst, t_inst *inst, t_par *tmp, int nb)
{
	if (lst->type == 2 || lst->type == 3)
	{
		if (lst->type == 2)
			inst->tab[inst->size += 1] = ft_atoi(lst->param);
		else if (lst->type == 3)
			inst->tab[inst->size += 3] = ft_atoi(lst->param);
	}
	if (lst->type == 5 || lst->type == 15)
	{
		if (lst->type == 5)
			return ;
		else if (lst->type == 15)
		{
			ft_printf("second start %i\n", inst->l_size);
			nb = testing(lst->lbl_ptr, tmp, nb);
			if (nb > 0)
				inst->tab[inst->size += 1] = nb;
			else
			{
				inst->tab[inst->size] = 0xff;
				inst->tab[inst->size += 1] = nb;
			}
		}
	}
	inst->size += 1;
}

void	check_type(t_par *lst, t_inst *inst, t_par *tmp, int nb)
{
	if (lst->type == 1)
		inst->tab[inst->size++] = ft_atoi(lst->param);
	else if (lst->type == 2 || lst->type == 3 || lst->type == 5
			|| lst->type == 15)
		direct_lab(lst, inst, tmp, nb);
	else if (lst->type == 4 || lst->type == 9)
		return ;
}

void	encoding(t_par *lst, int fd)
{
	int		i;
	int		j;
	t_par	*tmp;
	t_inst	inst;

	inst.size = 0;
	ft_bzero(inst.tab, CHAMP_MAX_SIZE + 1);
	while (lst)
	{
		if (lst->type == 6)
		{
			tmp = lst;
			i = nb_op(lst->param);
			inst.l_size = inst.size;
			inst.tab[inst.size++] = i + 1;
			ft_printf("start %i\n", inst.l_size);
			if (op_tab[i].encoding_byte > 0)
				get_binary(lst->next, &inst, op_tab[i].param_nb, inst.size);
		}
		else
			check_type(lst, &inst, tmp, i);
		lst = lst->next;
	}
	write(fd, inst.tab, inst.size);
}
