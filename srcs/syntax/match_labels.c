/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_labels.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 15:10:25 by bghandou          #+#    #+#             */
/*   Updated: 2019/06/30 18:27:17 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

int		search_label(char *param, t_par *tmp)
{
	while (tmp)
	{
		if (tmp->type == 7)
		{
			if (ft_strcmp(tmp->param , param) == 0)
				return (1);
		}
		tmp = tmp->next;
	}
	error_custom("Did not find matching label to argument.\n", tmp);
	return (0);
}

void	match_labels(t_par *tmp, t_par *head)
{
	int		find;
	int		count;

	find = 0;
	tmp = head;
	count = 0;
	while (tmp)
	{
		if (tmp->type == 5 || tmp->type == 9)
			find += search_label(tmp->param, head);
		tmp = tmp->next;
	}
	tmp = head;
	while (tmp && find > 0)
	{
		if (tmp->type == 5 || tmp->type == 9)
			count++;
		tmp = tmp->next;
	}
	if (!find || (find != count))
		error_custom("Did not find matching label(s) to argument(s).\n", head);
}
