/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 16:11:26 by jallen            #+#    #+#             */
/*   Updated: 2019/01/29 14:49:55 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void		search_arg2(t_param *new, va_list al)
{
	if (new->conv > D && new->conv < F)
	{
		if (new->mod == H)
			new->data.us = va_arg(al, int);
		else if (new->mod == HH)
			new->data.uc = va_arg(al, int);
		else if (new->mod == L)
			new->data.ul = va_arg(al, unsigned long);
		else if (new->mod == LL)
			new->data.ull = va_arg(al, unsigned long long);
		else if (new->mod == Z)
			new->data.st = va_arg(al, size_t);
		else if (new->mod == J)
			new->data.uimax = va_arg(al, uintmax_t);
		else
			new->data.ui = va_arg(al, unsigned int);
	}
	else if (new->conv == F)
	{
		if (new->mod == BIGL)
			new->data.ld = va_arg(al, long double);
		else
			new->data.d = va_arg(al, double);
	}
}

void			search_arg(t_param *new, va_list al)
{
	if (new->conv == P)
		new->data.ptr = va_arg(al, void *);
	else if (new->conv == S)
		new->data.str = va_arg(al, char *);
	else if (new->conv == C)
		new->data.c = va_arg(al, int);
	else if (new->conv == D)
	{
		if (new->mod == H)
			new->data.s = va_arg(al, int);
		else if (new->mod == HH)
			new->data.sc = va_arg(al, int);
		else if (new->mod == L)
			new->data.l = va_arg(al, long);
		else if (new->mod == LL)
			new->data.ll = va_arg(al, long long);
		else if (new->mod == Z)
			new->data.sst = va_arg(al, ssize_t);
		else if (new->mod == J)
			new->data.imax = va_arg(al, intmax_t);
		else
			new->data.i = va_arg(al, int);
	}
	else
		search_arg2(new, al);
}

void			convert_arg(t_printf *p)
{
	if (p->curr->conv == S)
		handle_str(p->curr, p);
	else if (p->curr->conv == P)
		handle_ptr(p->curr, p);
	else if (p->curr->conv == D)
		handle_integer(p->curr, p);
	else if (p->curr->conv == O)
		handle_base(p->curr, 8, p);
	else if (p->curr->conv == X || p->curr->conv == BIGX)
		handle_hexa(p->curr, 16, p);
	else if (p->curr->conv == U)
		handle_base(p->curr, 10, p);
	else if (p->curr->conv == C)
		handle_c(p->curr, p);
	else if (p->curr->conv == F)
		handle_float(p->curr, p);
	else if (p->curr->conv == B)
		handle_base(p->curr, 2, p);
}

void			search_width_precision(t_printf *p)
{
	if (ft_isdigit(*p->inp))
	{
		p->curr->width = ft_atoi(p->inp);
		while (ft_isdigit(*p->inp))
			++p->inp;
	}
	if (*p->inp == '.')
	{
		++p->inp;
		p->curr->precision = ft_atoi(p->inp) > 0 ? ft_atoi(p->inp) : 0;
		while (ft_isdigit(*p->inp))
			++p->inp;
		p->curr->ind |= PRECISION;
	}
	if (p->curr->width > 0 && !(p->curr->ind & ZERO))
		p->curr->ind |= CLEAR;
	if (!(p->curr->ind & CLEAR) && !(p->curr->ind & ZERO))
		p->curr->ind |= NONE;
}

void			parse_flags(t_printf *p, va_list al)
{
	while (ft_strchr("#+- 0*", *p->inp))
	{
		if (*p->inp == '#')
			p->curr->ind |= SHARP;
		else if (*p->inp == '+')
			p->curr->ind |= PLUS;
		else if (*p->inp == '-')
			p->curr->ind |= MINUS;
		else if (*p->inp == ' ')
			p->curr->ind |= SPACE;
		else if (*p->inp == '0')
			p->curr->ind |= ZERO;
		else if (*p->inp == '*')
			p->curr->ind |= WILDCARD;
		++p->inp;
	}
	if (p->curr->ind & WILDCARD)
	{
		p->curr->ind &= ~WILDCARD;
		if ((p->curr->width = va_arg(al, int)) < 0)
			p->curr->ind |= MINUS;
		p->curr->ind |= CLEAR;
	}
}
