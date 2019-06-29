/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_half.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 20:03:16 by bghandou          #+#    #+#             */
/*   Updated: 2019/06/28 13:29:55 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

t_par	*class_7(t_par *tmp, t_par *head)
{
	tmp = tmp->next;
	if (tmp->type == 1 || tmp->type == 4 || tmp->type == 3 || tmp->type == 5)
	{
		tmp = convert_size_direct(tmp); //check if value actually changes
		if (tmp->type == 5)//complete this by checking label and pointing to it etc.
		{
		//point to label
		}
		tmp = tmp->next;
		if (tmp->type == 1 || tmp->type == 3 || tmp->type == 5) 
		{
			tmp = convert_size_direct(tmp);
			if (tmp->type == 5) //create function to point to lab);
			{
			//point to label
			}
			tmp = tmp->next;
			if (tmp->type == 1)
				return (tmp->next);
		}
	}
	error_custom("Wrong argument(s) used.\n", head);
	return (tmp);
}
