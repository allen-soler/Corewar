/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 11:23:37 by nalonso           #+#    #+#             */
/*   Updated: 2019/01/21 12:43:14 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	handle_c(t_param *n, t_printf *p)
{
	char	*ind;

	ind = NULL;
	if (!(n->ind & NONE))
	{
		n->width -= 1;
		ind = add_ind(ft_strdup_safe(""), n);
		if (n->ind & MINUS)
		{
			buffer(p, &n->data.c, 1);
			buffer(p, ind, ft_strlen(ind));
		}
		else
		{
			buffer(p, ind, ft_strlen(ind));
			buffer(p, &n->data.c, 1);
		}
		free(ind);
	}
	else
		buffer(p, &n->data.c, 1);
}

void	handle_str(t_param *n, t_printf *p)
{
	char	*res;

	res = NULL;
	if (n->data.str == NULL)
		res = ft_strndup("(null)", n->ind & PRECISION ? n->precision : 6);
	else
		res = ft_strndup(n->data.str, n->ind & PRECISION ? \
				n->precision : (int)ft_strlen(n->data.str));
	if (!(n->ind & NONE))
		res = add_ind(res, n);
	buffer(p, res, ft_strlen(res));
	free(res);
}

void	handle_percent(t_printf *p)
{
	char *ind;

	ind = add_ind(ft_strdup_safe("%"), p->curr);
	buffer(p, ind, ft_strlen(ind));
	free(ind);
}
