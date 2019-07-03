#include "../includes/asm.h"

int		to_bin(char	*bin)
{
	char	*start = &bin[0];
	int		res;

	res = 0;
	while (*start)
	{
		res = res << 1;
		if (*start++ == '1') 
			res = res ^ 1;
	}
	return (res);
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

int		testing(t_par *lst, int size)
{
	t_par *tmp;
	int i = 0;

	tmp = lst;
	ft_printf("----------------\n");
	while (tmp)
	{
		if (tmp->type == 6)
			i += 2 + size;
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
	ft_printf("%i %i %i\n", i, i + size, size);
	ft_printf("----------------\n");
	return (i + size);
}

void	direct_lab(t_par *lst, t_inst *inst)
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
			inst->tab[inst->size += 1] = testing(lst->lbl_ptr, inst->size + 2);
		}
	}
	inst->size += 1;
}

void	check_type(t_par *lst, t_inst *inst)
{
	if (lst->type == 1)
		inst->tab[inst->size++] = ft_atoi(lst->param);
	else if (lst->type == 2 || lst->type == 3 || lst->type == 5
			|| lst->type == 15)
		direct_lab(lst, inst);
	else if (lst->type == 4 || lst->type == 9)
		return ;
}

int		size_inst(t_par *lst
void	encoding(t_par *lst, int fd)
{
	int		i;
	int		j;
	t_inst	inst;

	inst.size = 0;
	ft_bzero(inst.tab, CHAMP_MAX_SIZE + 1);
	while (lst)
	{
		if (lst->type == 6)
		{
			i = 0;
			while (op_tab[i].name)
			{
				if (ft_strcmp(lst->param, op_tab[i].name) == 0)
					break ;
				i++;
			}
			inst.tab[inst.size++] = i + 1;
			if (op_tab[i].encoding_byte > 0)
				get_binary(lst->next, &inst, op_tab[i].param_nb, inst.size);
		}
		else
			check_type(lst, &inst);
		lst = lst->next;
	}
	write(fd, inst.tab, inst.size);
}
