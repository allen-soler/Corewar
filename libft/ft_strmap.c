/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 22:30:19 by bghandou          #+#    #+#             */
/*   Updated: 2018/11/15 09:57:16 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*arr;

	i = 0;
	arr = NULL;
	if (!s)
		return (NULL);
	if (!(arr = (char*)malloc(sizeof(char) * ft_strlen(s) + 1)))
		return (0);
	while (s[i] != '\0')
	{
		arr[i] = f(s[i]);
		i++;
	}
	arr[i] = '\0';
	return (arr);
}
