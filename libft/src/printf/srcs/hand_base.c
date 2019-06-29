/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 12:28:06 by nalonso           #+#    #+#             */
/*   Updated: 2019/03/01 18:24:09 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char	*ft_strupper(char *res)
{
	char	*ptr;

	ptr = res;
	while (*res)
	{
		*res = ft_toupper(*res);
		++res;
	}
	return (ptr);
}

char		*data_to_base(t_param *n, int base)
{
	char	*res;

	if (n->mod == H)
		res = ft_itoa_base(n->data.us, base);
	else if (n->mod == HH)
		res = ft_itoa_base(n->data.uc, base);
	else if (n->mod == L)
		res = ft_itoa_base(n->data.ul, base);
	else if (n->mod == LL)
		res = ft_itoa_base(n->data.ull, base);
	else if (n->mod == Z)
		res = ft_itoa_base(n->data.st, base);
	else if (n->mod == J)
		res = ft_itoa_base(n->data.uimax, base);
	else
		res = ft_itoa_base(n->data.ui, base);
	return (res);
}

void		handle_base(t_param *n, unsigned int base, t_printf *p)
{
	char	*res;
	char	i[2];
	int		err;

	res = data_to_base(n, base);
	err = (!(ft_strcmp("0", res))) ? 1 : 0;
	n->width = ((n->precision > n->width) && (n->ind & ZERO))\
				? n->precision : n->width;
	(base == 8 && ((n->ind & ZERO) && n->width <= (int)ft_strlen(res)) \
	&& n->ind & SHARP) ? n->ind &= ~ZERO : 0;
	if ((base == 8) && !(n->ind & ZERO) && (n->ind & SHARP))
		i[0] = '0';
	i[1] = '\0';
	if ((!err) && n->ind & SHARP)
		res = fstrjoin(ft_strdup_safe(i), res);
	if (((n->ind & PRECISION && !(n->ind & ZERO) && (n->precision != 0))\
		|| (err && !(n->ind & SHARP)) || (n->ind & SHARP && err\
		&& n->precision == 0 && (n->ind & ZERO || n->ind & NONE))))
		res = add_prec(res, n);
	res = add_ind(res, n);
	if (err && base == 8 && n->precision == 0 && n->ind & SHARP \
			&& !(n->precision == 0 && err && n->ind & CLEAR))
		res = fstrjoin(ft_strdup_safe(i), res);
	buffer(p, res, ft_strlen(res));
	free(res);
}

void		handle_hexa(t_param *n, unsigned int base, t_printf *p)
{
	char	*res;
	char	i[3];
	int		nb;

	res = data_to_base(n, base);
	nb = ft_strcmp("0", res);
	(n->ind & ZERO && n->ind & MINUS) ? n->ind &= ~ZERO : 0;
	(n->ind & SHARP && n->ind & ZERO && nb) ? n->width -= 2 : 0;
	n->precision = (n->ind & ZERO && n->width > n->precision) ? \
					n->width : n->precision;
	if (nb && (n->ind & SHARP) && (base == 16))
		i[0] = '0';
	if (nb && (n->ind & SHARP) && (base == 16))
		i[1] = 'x';
	i[2] = '\0';
	if (!(n->ind & PRECISION) && !(n->ind & ZERO) && (n->ind & SHARP))
		res = fstrjoin(ft_strdup_safe(i), res);
	if ((n->ind & PRECISION || n->ind & ZERO) && (n->precision || !nb))
		res = add_prec(res, n);
	if (n->ind & SHARP && (n->ind & PRECISION || n->ind & ZERO))
		res = fstrjoin(ft_strdup_safe(i), res);
	res = add_ind(res, n);
	res = (n->conv == BIGX) ? ft_strupper(res) : res;
	buffer(p, res, ft_strlen(res));
	free(res);
}

void		handle_ptr(t_param *n, t_printf *p)
{
	char	*res;

	if (n->precision == 0)
		res = ft_strdup_safe("");
	else
		res = ft_itoa_base((uintmax_t)n->data.ptr, 16);
	if (n->ind & CLEAR && n->width > n->precision)
	{
		res = fstrjoin(ft_strdup_safe("0x"), res);
		if (n->precision)
			res = add_prec(res, n);
		res = add_ind(res, n);
	}
	else
	{
		n->width -= 2;
		res = add_prec(res, n);
		res = add_ind(res, n);
		res = fstrjoin(ft_strdup_safe("0x"), res);
	}
	buffer(p, res, ft_strlen(res));
	free(res);
}
