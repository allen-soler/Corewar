#include "../includes/asm.h"

int		counting_label(t_par *lst, int nb, t_inst *inst)
{
	int		i;
	t_par	*tmp;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		if (tmp->type == 6)
			i = op_tab[nb_op(tmp->param)].encoding_byte > 0 ? i + 2 : i + 1;
		else if (tmp->type == 1)
			i += 1;
		else if (tmp->type == 2 || tmp->type == 15 || tmp->type == 4 || tmp->type == 9)
			i += 2;
		else if (tmp->type == 3 || tmp->type == 5)
			i += 4;
		inst->param_steps += 1;
		tmp = tmp->next;
		if (tmp)
			if (tmp->type == 6 || tmp->type == 7)
				break ;
	}
	return (i);
}

int		label_aff(t_par *lst, t_par *tmp, int nb, t_inst *inst)
{
	int i;

	i = 0;
	while (tmp)
	{
		if (tmp->pos == lst->pos)
			break ;
		if (tmp->type == 6)
			i = op_tab[nb_op(tmp->param)].encoding_byte > 0 ? i + 2 : i + 1;
		else if (tmp->type == 1)
			i += 1;
		else if (tmp->type == 2 || tmp->type == 15 || tmp->type == 4 || tmp->type == 9)
			i += 2;
		else if (tmp->type == 3 || tmp->type == 5)
			i += 4;
		tmp = tmp->next;
	}
	return (-i);
}

int		label_start(t_par *lst, t_par *tmp, int nb, t_inst *inst)
{
	int i;

	i = 0;
	while (tmp)
	{
		if (lst == tmp)
			break ;
		if (tmp->type == 6)
			i = op_tab[nb_op(tmp->param)].encoding_byte > 0 ? i + 2 : i + 1;
		else if (tmp->type == 1)
			i += 1;
		else if (tmp->type == 2 || tmp->type == 15 || tmp->type == 4 || tmp->type == 9)
			i += 2;
		else if (tmp->type == 3 || tmp->type == 5)
			i += 4;
		tmp = tmp->next;
	}
	nb = counting_label(lst->next, nb, inst);
	return (i < nb ? i = -(nb - i) : i);
}

void	direct_lab(t_par *lst, t_inst *inst, t_par *tmp, int nb)
{
	nb = lst->lbl_ptr->pos < tmp->pos ? label_aff(tmp, lst->lbl_ptr, nb, inst)\
		 : label_start(lst->lbl_ptr, tmp, nb, inst);
	if (lst->type == 5)
		write_byte(inst, nb, 4);
	else if (lst->type == 15 || lst->type == 9)
		write_byte(inst, nb, 2);
}

void	check_type(t_par *lst, t_inst *inst, t_par *tmp, int nb)
{
	if (lst->type == 1)
		inst->tab[inst->size++] = ft_atoi(lst->param);
	else if (lst->type == 2 || lst->type == 3 || lst->type == 5
			|| lst->type == 15)
	{
		if (lst->type == 2)
			write_byte(inst, ft_atoi(lst->param), 2);
		else if (lst->type == 3)
			write_byte(inst, ft_atoi(lst->param), 4);
		else
			direct_lab(lst, inst, tmp, nb);
		inst->size += 1;
	}
	else if (lst->type == 4 || lst->type == 9)
	{
		if (lst->type == 4)
			write_byte(inst, ft_atoi(lst->param), 2);
		else if (lst->type == 9)
			direct_lab(lst, inst, tmp, nb);
		inst->size += 1;
	}
}

void	encoding(t_par *lst, int fd, t_inst *inst)
{
	int		i;
	t_par	*tmp;

	inst->size = 0;
	ft_bzero(inst->tab, CHAMP_MAX_SIZE + 1);
	while (lst)
	{
		if (lst->type == 6)
		{
			tmp = lst;
			i = nb_op(lst->param);
			inst->tab[inst->size++] = i + 1;
			if (op_tab[i].encoding_byte > 0)
				get_binary(lst->next, inst, op_tab[i].param_nb, inst->size);
		}
		else
			check_type(lst, inst, tmp, i);
		lst = lst->next;
	}
}
