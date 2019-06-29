/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 14:56:48 by bghandou          #+#    #+#             */
/*   Updated: 2018/11/09 16:33:25 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*conv;
	unsigned char	val;
	size_t			i;

	conv = b;
	val = c;
	i = 0;
	while (i < len)
	{
		conv[i] = val;
		i++;
	}
	return (b);
}
