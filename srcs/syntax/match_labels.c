/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_labels.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 15:10:25 by bghandou          #+#    #+#             */
/*   Updated: 2019/07/01 16:07:41 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

t_par	*search_label(char *param, t_par *tmp, int *count)
{
	t_par	*search_lab;

	search_lab = tmp;
	while (search_lab)
	{
		if (search_lab->type == 7)
		{
			if (ft_strcmp(search_lab->param , param) == 0)
			{
				*count = *count + 1;
				return (search_lab);
			}
		}
		search_lab = search_lab->next;
	}
	error_custom("Did not find matching label to argument.\n", tmp);
	return (0);
}

void	match_labels(t_par *tmp, t_par *head)
{
	int		count;
	int		count_ptrs;

	tmp = head;
	count = 0;
	count_ptrs = 0;
	while (tmp)
	{
		if (tmp->type == 5 || tmp->type == 9)
			tmp->lbl_ptr = search_label(tmp->param, head, &count); //if find then do whats necessary to point ot it!
		tmp = tmp->next;
	}
	tmp = head;
	while (tmp && count > 0)
	{
		if (tmp->type == 5 || tmp->type == 9)
			count_ptrs++;
		tmp = tmp->next;
	}
	if (!count || (count != count_ptrs))
		error_custom("Did not find matching label(s) to argument(s).\n", head);
}
