/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:51:52 by nalonso           #+#    #+#             */
/*   Updated: 2018/11/14 10:49:46 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		check(char c)
{
	if (c == '\n' || c == ' ' || c == '\t')
		return (1);
	return (0);
}

char			*ft_strtrim(char const *s)
{
	char			*ret;
	unsigned int	a;
	unsigned int	b;
	unsigned int	index;

	if (!s)
		return (NULL);
	if (!(*s))
		return (ft_strnew(1));
	a = 0;
	b = ft_strlen(s) - 1;
	while (check(s[a]) && s[a])
		a++;
	while (b > a && check(s[b]))
		b--;
	if (!(ret = (char *)malloc(sizeof(char) * (b - a + 2))))
		return (NULL);
	index = 0;
	while (a <= b)
		ret[index++] = s[a++];
	ret[index] = '\0';
	return (ret);
}
