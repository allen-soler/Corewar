/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 18:03:20 by bghandou          #+#    #+#             */
/*   Updated: 2018/11/10 21:46:08 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s_b;

	s_b = (unsigned char*)s;
	i = 0;
	while (i < n)
	{
		if (s_b[i] == (unsigned char)c)
			return (s_b + i);
		i++;
	}
	return (NULL);
}
