/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floats.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 12:13:23 by nalonso           #+#    #+#             */
/*   Updated: 2019/01/21 12:42:34 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static double	ft_dabs(double n)
{
	return (n < 0 ? -n : n);
}

static double	ft_pow(double n, int pow)
{
	return (pow ? n * ft_pow(n, pow - 1) : 1);
}

void			float_indentation(char *res, t_param *a, \
									long double n, t_printf *p)
{
	char i;

	i = 0;
	if (n < 0.0 || a->ind & SPACE || a->ind & PLUS)
	{
		if (a->ind & ZERO)
			--a->width;
		(a->ind & SPACE) ? i = ' ' : 0;
		(a->ind & PLUS) ? i = '+' : 0;
		(n < 0.0) ? i = '-' : 0;
	}
	if (i && a->ind & ZERO)
		res = add_char(add_ind(res, a), i);
	else if (i && a->ind & CLEAR)
		res = add_ind(add_char(res, i), a);
	else if (i && a->ind & NONE)
		res = add_char(res, i);
	else
		res = add_ind(res, a);
	buffer(p, res, ft_strlen(res));
	free(res);
}

void			dtoa_string(long double n, t_param *a, long value, t_printf *p)
{
	int		len;
	char	s[256];
	char	*buff;
	long	tmp;

	ft_memset(s, '\0', 256);
	buff = NULL;
	len = 0;
	tmp = (long)(n > 0 ? n : -n);
	buff = ft_itoa_base(tmp, 10);
	ft_strcat(s, buff);
	free(buff);
	len = ft_strlen(s);
	if (a->precision != 0)
	{
		s[len++] = '.';
		len += a->precision;
		buff = ft_itoa_base(value, 10);
		if (a->precision > (int)ft_strlen(buff))
			buff = fstrjoin(buff, new_str('0', a->precision - ft_strlen(buff)));
		ft_strcat(s, buff);
		free(buff);
	}
	buff = ft_strdup_safe(s);
	float_indentation(buff, a, n, p);
}

void			handle_float(t_param *a, t_printf *p)
{
	long double			n;
	long double			dec;
	long long			value;

	n = (a->mod == BIGL) ? a->data.ld : a->data.d;
	value = 0;
	if (!(a->ind & PRECISION))
		a->precision = 6;
	dec = ft_dabs(n);
	dec = (dec - (long long)(ft_dabs(n))) * ft_pow(10, a->precision + 1);
	dec = ((long long)dec % 10 > 4) ? dec / 10 + 1 : dec / 10;
	value = (long long)dec;
	dtoa_string(n, a, value, p);
}
