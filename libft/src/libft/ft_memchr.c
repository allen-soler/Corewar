/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:48:29 by nalonso           #+#    #+#             */
/*   Updated: 2018/11/09 10:01:12 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	uc;
	size_t			index;

	index = 0;
	uc = (unsigned char)c;
	while (index < n)
	{
		if (((unsigned char *)s)[index] == uc)
			return (&((unsigned char *)s)[index]);
		index++;
	}
	return (NULL);
}
