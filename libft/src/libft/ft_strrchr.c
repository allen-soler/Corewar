/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:51:34 by nalonso           #+#    #+#             */
/*   Updated: 2018/11/06 17:15:26 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	ch;
	size_t	i;
	char	*str;

	str = (char *)s;
	i = 0;
	ch = (char)c;
	while (str[i])
		i++;
	i += 1;
	while (i--)
	{
		if (str[i] == ch)
			return (&str[i]);
	}
	return (NULL);
}
