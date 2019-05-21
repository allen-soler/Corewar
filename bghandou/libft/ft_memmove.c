/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 17:28:08 by bghandou          #+#    #+#             */
/*   Updated: 2018/11/12 16:30:00 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dst_b;
	char	*src_b;

	dst_b = dst;
	src_b = (char*)src;
	if (dst > src)
	{
		len -= 1;
		while ((int)len >= 0)
		{
			dst_b[len] = src_b[len];
			len--;
		}
	}
	else
		return (ft_memcpy(dst, src, len));
	return (dst);
}
