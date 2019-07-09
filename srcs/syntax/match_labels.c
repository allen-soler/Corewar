/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_labels.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 15:10:25 by bghandou          #+#    #+#             */
/*   Updated: 2019/07/09 12:38:42 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

t_par	*search_label(t_par *to_label, t_par *tmp, int *count)
{
	t_par	*search_lab;

	search_lab = tmp;
	while (search_lab)
	{
		if (search_lab->type == 7)
		{
			if (ft_strcmp(search_lab->param, to_label->param) == 0)
			{
				*count = *count + 1;
				return (search_lab);
			}
		}
		search_lab = search_lab->next;
	}
	error_row("Did not find matchine label.", to_label->row);
	return (0);
}

void	match_labels(t_par *tmp, t_par *head)
{
	int		count;
	int		count_ptrs;
	t_par	*tmp2;

	tmp = head;
	count = 0;
	count_ptrs = 0;
	tmp2 = head;
	while (tmp)
	{
		if (tmp->type == 5 || tmp->type == 9)
			tmp->lbl_ptr = search_label(tmp, head, &count);
		tmp = tmp->next;
	}
	while (tmp2 && count > 0)
	{
		if (tmp2->type == 5 || tmp2->type == 9)
			count_ptrs++;
		tmp2 = tmp2->next;
	}
	if (!count || (count != count_ptrs))
		error_row("Did not find matching label(s) to argument(s).", tmp->row);
}
