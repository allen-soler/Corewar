/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:44:35 by nalonso           #+#    #+#             */
/*   Updated: 2018/11/07 11:47:45 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long	res;
	long	sign;
	int		check;

	sign = 1;
	res = 0;
	check = 2;
	while (ft_isspace((unsigned char)(*str)))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit((int)*str))
	{
		if (res > res * 10 + (*str - '0'))
			check = (sign == -1) ? 0 : -1;
		res = res * 10 + (*str++ - '0');
	}
	return (check == -1 || check == 0 ? check : (int)(res * sign));
}
