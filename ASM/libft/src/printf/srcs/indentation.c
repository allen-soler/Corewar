/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indentation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 11:21:13 by nalonso           #+#    #+#             */
/*   Updated: 2019/01/21 12:43:21 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*new_str(char c, int size)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc_safe(sizeof(char) * size + 1);
	while (i < size)
		str[i++] = c;
	str[i] = '\0';
	return (str);
}

char	*add_ind(char *str, t_param *node)
{
	int		len;
	char	*new;
	char	*ind;

	len = ft_strlen(str);
	if (len >= node->width)
		return (str);
	else
	{
		if (node->ind & CLEAR || node->conv == P || node->ind & MINUS)
			ind = new_str(' ', node->width - len);
		else
			ind = new_str('0', node->width - len);
		if (node->ind & MINUS)
			new = fstrjoin(str, ind);
		else
			new = fstrjoin(ind, str);
	}
	return (new);
}

char	*add_prec(char *str, t_param *node)
{
	int		len;
	char	*new;

	if (!(node->ind & PRECISION) && !(node->ind & ZERO))
		return (str);
	if (node->ind & ZERO && node->ind & PRECISION)
	{
		node->ind &= ~ZERO;
		node->ind |= CLEAR;
	}
	len = ft_strlen(str);
	if (node->precision == 0)
	{
		free(str);
		return (ft_strdup_safe(""));
	}
	if (len >= node->precision)
		return (str);
	else
		new = fstrjoin(new_str('0', node->precision - len), str);
	return (new);
}
