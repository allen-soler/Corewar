/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_di.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 12:05:08 by nalonso           #+#    #+#             */
/*   Updated: 2019/01/19 15:26:40 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int		is_negative(t_param *n)
{
	if (n->data.i < 0 && (n->mod == NO))
		return (-1);
	else if (n->data.l < 0 && n->mod == L)
		return (-1);
	else if (n->data.ll < 0 && n->mod == LL)
		return (-1);
	else if (n->data.s < 0 && n->mod == H)
		return (-1);
	else if (n->data.sc < 0 && n->mod == HH)
		return (-1);
	else if (n->data.sst < 0 && n->mod == Z)
		return (-1);
	else if (n->data.imax < 0 && n->mod == J)
		return (-1);
	return (1);
}

static void		to_unsigned(t_param *n, int neg)
{
	if (n->mod == NO)
		n->data.ui = neg * n->data.i;
	else if (n->mod == L)
		n->data.ul = neg * n->data.l;
	else if (n->mod == LL)
		n->data.ull = neg * n->data.ll;
	else if (n->mod == H)
		n->data.us = neg * n->data.s;
	else if (n->mod == HH)
		n->data.uc = neg * n->data.sc;
	else if (n->mod == Z)
		n->data.st = neg * n->data.sst;
	else if (n->mod == J)
		n->data.uimax = neg * n->data.imax;
}

static char		*int_indentation(char *res, int neg, t_param *n)
{
	char	f;

	if ((n->ind & PRECISION))
	{
		if (!ft_strcmp("0", res))
			ft_strclr(res);
		if (n->precision != 0)
			res = add_prec(res, n);
	}
	(n->ind & SPACE) ? f = ' ' : 0;
	f = (neg) ? '-' : 0;
	(n->ind & PLUS && !neg) ? f = '+' : 0;
	if (n->ind & ZERO && f)
	{
		--n->width;
		res = add_ind(res, n);
		res = add_char(res, f);
	}
	else
	{
		if (f)
			res = add_char(res, f);
		res = add_ind(res, n);
	}
	return (res);
}

void			handle_integer(t_param *n, t_printf *p)
{
	char	*res;
	int		neg;

	neg = is_negative(n);
	to_unsigned(n, neg);
	neg = (neg < 0) ? 1 : 0;
	res = data_to_base(n, 10);
	res = int_indentation(res, neg, n);
	buffer(p, res, ft_strlen(res));
	free(res);
}
