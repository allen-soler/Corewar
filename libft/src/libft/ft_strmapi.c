/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:51:06 by nalonso           #+#    #+#             */
/*   Updated: 2018/11/06 17:02:40 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*nwstr;
	int		len;
	int		index;

	index = 0;
	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	if (!(nwstr = (char *)ft_memalloc(len + 1)))
		return (NULL);
	while (len--)
	{
		nwstr[index] = f(index, s[index]);
		index++;
	}
	nwstr[index] = '\0';
	return (nwstr);
}
