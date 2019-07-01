/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_half.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:53:16 by bghandou          #+#    #+#             */
/*   Updated: 2019/07/01 13:21:42 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

t_par	*class_1(t_par *tmp, t_par *head)
{
	tmp = tmp->next;
	if (tmp && (tmp->type == 3 || tmp->type == 5)
			&& remaining_tokens(tmp))
		return (tmp->next);
	error_custom("Invalid argument(s) for 'live'.\n", head);
	return (tmp);
}

t_par	*class_2(t_par *tmp, t_par *head)
{
	tmp = tmp->next;
	if (tmp && (tmp->type == 3 || tmp->type == 5)
			&& remaining_tokens(tmp))
	{
		tmp = convert_size_direct(tmp);
		return (tmp->next);
	}
	error_custom("Invalid argument(s) for 'zjmp' | 'fork' | 'lfork' \
match.\n", head);
	return (tmp);
}

t_par	*class_3(t_par *tmp, t_par *head)
{
	tmp = tmp->next;
	if (tmp && (tmp->type == 3 || tmp->type == 5
				|| tmp->type == 4 || tmp->type == 9))
	{
		tmp = tmp->next;
		if (tmp && (tmp->type == 1) && remaining_tokens(tmp))
			return (tmp->next);
	}
	error_custom("Invalid argument(s) for 'ld' | 'lld'.\n", head);
	return (tmp);
}

t_par	*class_4(t_par *tmp, t_par *head)
{
	tmp = tmp->next;
	if (tmp && (tmp->type == 1))
	{
		tmp = tmp->next;
		if (tmp && (tmp->type == 1 || tmp->type == 4 || tmp->type == 9)
				&& remaining_tokens(tmp))
			return (tmp->next);
	}
	error_custom("Invalid argument(s) for 'st'.\n", head);
	return (tmp);
}
