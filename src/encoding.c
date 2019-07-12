/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoding.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 00:30:29 by jallen            #+#    #+#             */
/*   Updated: 2019/07/12 11:43:24 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static int	label_aff(t_par *lst, t_par *tmp)
{
	int i;

	i = 0;
	while (tmp)
	{
		if (tmp->pos == lst->pos)
			break ;
		if (tmp->type == 6)
			i = g_op_tab[nb_op(tmp->param)].encoding_byte > 0 ? i + 2 : i + 1;
		else if (tmp->type == 1)
			i += 1;
		else if (tmp->type == 2 || tmp->type == 15
				|| tmp->type == 4 || tmp->type == 9)
			i += 2;
		else if (tmp->type == 3 || tmp->type == 5)
			i += 4;
		tmp = tmp->next;
	}
	return (-i);
}

static int	label_start(t_par *lst, t_par *tmp, int nb, t_inst *inst)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	if (tmp && lst->next && tmp->pos < lst->next->pos)
		j = 1;
	while (tmp)
	{
		if (tmp->type == 6)
			i = g_op_tab[nb_op(tmp->param)].encoding_byte > 0 ? i + 2 : i + 1;
		else if (tmp->type == 1)
			i += 1;
		else if (tmp->type == 2 || tmp->type == 15
				|| tmp->type == 4 || tmp->type == 9)
			i += 2;
		else if (tmp->type == 3 || tmp->type == 5)
			i += 4;
		tmp = tmp->next;
		if (lst == tmp)
			break ;
	}
	nb = counting_label(lst->next, inst);
	return (j == 0 ? i = -(nb - i) : i);
}

static void	direct_lab(t_par *lst, t_inst *inst, t_par *tmp, int nb)
{
	nb = lst->lbl_ptr->row < tmp->row ? label_aff(tmp, lst->lbl_ptr)\
	: label_start(lst->lbl_ptr, tmp, nb, inst);
	if (lst->type == 5)
		write_byte(inst, nb, 4);
	else if (lst->type == 15 || lst->type == 9)
		write_byte(inst, nb, 2);
}

static void	check_type(t_par *lst, t_inst *inst, t_par *tmp, int nb)
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

void		encoding(t_par *lst, t_inst *inst)
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
			if (g_op_tab[i].encoding_byte > 0)
				get_binary(lst->next, inst, g_op_tab[i].param_nb, inst->size);
		}
		else
			check_type(lst, inst, tmp, i);
		if (inst->size > CHAMP_MAX_SIZE)
			exit(ft_fprintf(2, "Champ Size too big\n"));
		lst = lst->next;
	}
}
