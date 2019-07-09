/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   para_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 16:10:03 by bghandou          #+#    #+#             */
/*   Updated: 2019/07/10 01:25:09 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		fix_leak(t_par **list, intmax_t stock, int n, int row)
{
	char	*dest;

	dest = ft_itoa(stock);
	*list = add_parameter(*list, dest, n, row);
	free(dest);
}

static void	add_par_extra(t_par *list, char *inst, int type, int row)
{
	t_par *tmp;

	tmp = list;
	if (!(tmp = malloc(sizeof(t_par))))
		return ;
	tmp->param = ft_strdup(inst);
	tmp->type = type;
	tmp->row = row;
	tmp->cnt = 0;
	tmp->pos = 0;
	tmp->lbl_ptr = NULL;
	tmp->next = NULL;
	while (list->next)
		list = list->next;
	list->next = tmp;
}

t_par		*add_parameter(t_par *list, char *inst, int type, int row)
{
	t_par	*tmp;
	t_par	*head;

	head = list;
	tmp = NULL;
	if (!list)
	{
		if (!(list = malloc(sizeof(t_par))))
			return (NULL);
		list->param = ft_strdup(inst);
		list->type = type;
		list->row = row;
		list->lbl_ptr = NULL;
		list->next = NULL;
		head = list;
	}
	else
		add_par_extra(list, inst, type, row);
	return (head);
}
