/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_labels.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 15:10:25 by bghandou          #+#    #+#             */
/*   Updated: 2019/06/30 13:26:48 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

int		search_label(char *param, t_par *tmp)
{
	dprintf(1, "name:%s\n", param);
	while (tmp)
	{
		if (tmp->type == 7)
		{
			if (ft_strcmp(tmp->param , param) == 0)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	match_labels(t_par *tmp, t_par *head)
{
	int		find;

	find = 0;
	tmp = head;
	test_print(head);
	while (tmp && !find)
	{
		if (tmp->type == 5 || tmp->type == 9)
			find = search_label(tmp->param, head);
		tmp = tmp->next;
	}
	if (!find)
		error_custom("Did not find matching label to argument.\n", head);
}
