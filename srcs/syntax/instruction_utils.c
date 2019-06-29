/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:46:44 by bghandou          #+#    #+#             */
/*   Updated: 2019/06/28 12:38:29 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

t_par	*convert_size_direct(t_par *list)
{
	if (list->type == 3)
	{
		list->type = 2;
		return (list);
	}
	return (list);
}

int		check_class(int	cur)
{
	int class;
	
	class = 0;
	if (cur == 0 || cur == 11)
		class = 7;
	else if (cur == 1)
		class = 8;
	else if (cur == 2)
		class = 4;
	else if (cur == 3)
		class = 1;
	else if (cur == 4 || cur == 5)
		class = 5;
	else if (cur == 6 || cur  == 7 || cur == 8)
		class = 6;
	else if (cur == 9 || cur == 13 || cur == 14)
		class = 2;
	else if (cur == 10 || cur == 12)
		class = 3;
	else if (cur == 15)
		class = 9;
	return (class);
}

t_par	*next_inst(t_par *list)
{
	t_par	*tmp;

	tmp = list;
	while (tmp && tmp->type != 6)
		tmp = tmp->next;
	if (tmp && tmp->type == 6)
		return (tmp);
	return (list);
}
