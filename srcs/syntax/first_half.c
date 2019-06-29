/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_half.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:53:16 by bghandou          #+#    #+#             */
/*   Updated: 2019/06/29 14:29:57 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

t_par	*live_function(t_par *tmp, t_par *head)
{
	tmp = tmp->next;
	if ((tmp->type == 3 || tmp->type == 5)
			&& (tmp->next->type == 6 || tmp->next == NULL))
		return (tmp->next);
	else
		error_custom("Argument type 'live' doesn't match\n", head);
	return (tmp);
}
