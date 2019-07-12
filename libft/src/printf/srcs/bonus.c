/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 16:11:13 by jallen            #+#    #+#             */
/*   Updated: 2019/01/14 16:42:38 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int		valid_color(t_printf *p)
{
	if (*p->inp == '{')
		if (*(p->inp + 1) && ft_strchr("RBrgybmcw", *(p->inp + 1)))
			if (*(p->inp + 2) && *(p->inp + 2) == '}')
				return (1);
	return (0);
}

static char		*search_color(char cl)
{
	if (cl == 'B')
		return (BLACK);
	else if (cl == 'r')
		return (RED);
	else if (cl == 'g')
		return (GREEN);
	else if (cl == 'y')
		return (YELLOW);
	else if (cl == 'b')
		return (BLUE);
	else if (cl == 'm')
		return (MAGENTA);
	else if (cl == 'c')
		return (CYAN);
	else if (cl == 'w')
		return (WHITE);
	else
		return (RESET);
}

int				colors(t_printf *p)
{
	char	*color;

	if (valid_color(p))
	{
		++p->inp;
		color = search_color(*p->inp);
		buffer(p, color, ft_strlen(color));
		++p->inp;
		return (1);
	}
	return (0);
}

void			handle_n(t_printf *p, va_list al)
{
	write_buffer(p);
	*va_arg(al, int *) = p->len;
}

void			handle_binary(t_printf *p)
{
	char	*res;

	res = data_to_base(p->curr, 2);
	if (p->curr->ind & ZERO)
	{
		p->curr->ind &= ~ZERO;
		p->curr->ind |= CLEAR;
	}
	if (!(p->curr->ind & NONE))
		res = add_ind(res, p->curr);
	buffer(p, res, ft_strlen(res));
	free(res);
}
