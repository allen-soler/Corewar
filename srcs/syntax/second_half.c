/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_half.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 20:03:16 by bghandou          #+#    #+#             */
/*   Updated: 2019/07/06 19:37:07 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

t_par	*class_5(t_par *tmp, t_par *head)
{
	tmp = tmp->next;
	if (tmp && (tmp->type == 1))
	{
		tmp = tmp->next;
		if (tmp && (tmp->type == 1))
		{
			tmp = tmp->next;
			if (tmp && (tmp->type == 1) && remaining_tokens(tmp))
				return (tmp->next);
		}
	}
	error_custom("Invalid argument(s) for 'add' | 'sub'.\n", head);
	return (tmp);
}

t_par	*class_6(t_par *tmp, t_par *head)
{
	tmp = tmp->next;
	if (tmp && (tmp->type == 1 || tmp->type == 3 || tmp->type == 5
				|| tmp->type == 4 || tmp->type == 9))
	{
		tmp = tmp->next;
		if (tmp && (tmp->type == 1 || tmp->type == 3 || tmp->type == 5
					|| tmp->type == 4 || tmp->type == 9))
		{
			tmp = tmp->next;
			if (tmp && (tmp->type == 1) && remaining_tokens(tmp))
				return (tmp->next);
		}
	}
	error_custom("Invalid argument(s) for 'and' | 'or' | 'xor'.\n", head);
	return (tmp);
}

t_par	*class_7(t_par *tmp, t_par *head)
{
	tmp = tmp->next;
	if (tmp && (tmp->type == 1 || tmp->type == 4 || tmp->type == 9 ||
			tmp->type == 3 || tmp->type == 5))
	{
		tmp = convert_size_direct(tmp);
		tmp = tmp->next;
		if (tmp && (tmp->type == 1 || tmp->type == 3 || tmp->type == 5))
		{
			tmp = convert_size_direct(tmp);
			tmp = tmp->next;
			if (tmp->type == 1 && remaining_tokens(tmp))
				return (tmp->next);
		}
	}
	error_custom("Invalid argument(s) used for 'ldi' | 'lldi'.\n", head);
	return (tmp);
}

t_par	*class_8(t_par *tmp, t_par *head)
{
	tmp = tmp->next;
	if (tmp && (tmp->type == 1))
	{
		tmp = tmp->next;
		if (tmp && (tmp->type == 1 || tmp->type == 4 || tmp->type == 9
					|| tmp->type == 5 || tmp->type == 3))
		{
			tmp = convert_size_direct(tmp);
			tmp = tmp->next;
			if (tmp && (tmp->type == 1 || tmp->type == 5 || tmp->type == 3)
					&& remaining_tokens(tmp))
			{
				tmp = convert_size_direct(tmp);
				return (tmp->next);
			}
		}
	}
	error_custom("Invalid argument(s) used for 'sti'.\n", head);
	return (tmp);
}

t_par	*class_9(t_par *tmp, t_par *head)
{
	tmp = tmp->next;
	if (tmp && (tmp->type == 1) && remaining_tokens(tmp))
	{
		return (tmp->next);
	}
	error_custom("Invalid argument(s) used for 'aff'.\n", head);
	return (tmp);
}
