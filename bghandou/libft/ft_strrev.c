/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 14:19:54 by bghandou          #+#    #+#             */
/*   Updated: 2018/11/11 14:36:42 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	char	stock;
	int		length;
	int		i;
	int		k;

	length = ft_strlen(str);
	i = 0;
	k = length - 1;
	stock = 0;
	while (i < length / 2)
	{
		stock = str[i];
		str[i] = str[k];
		str[k] = stock;
		i++;
		k--;
	}
	return (str);
}
