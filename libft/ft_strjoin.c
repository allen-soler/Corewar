/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 14:30:04 by bghandou          #+#    #+#             */
/*   Updated: 2018/11/28 16:32:01 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*arr;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	if (!(arr = (char*)malloc(sizeof(char) * ((i + j) + 1))))
		return (0);
	i = -1;
	j = -1;
	while (s1[++i] != '\0')
	{
		arr[i] = (char)s1[i];
	}
	while (s2[++j] != '\0')
	{
		arr[i + j] = (char)s2[j];
	}
	arr[i + j] = '\0';
	return (arr);
}
