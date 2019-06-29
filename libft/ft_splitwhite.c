/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitwhite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 14:58:05 by bghandou          #+#    #+#             */
/*   Updated: 2019/06/21 19:36:37 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


//
#include <stdio.h> //bro

static size_t	ft_countwords(const char *s)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	if (s[0] != ' ' || s[0] != '\t')
		count++;
	while (s[i] != '\0')
	{
		if ((s[i] ==  ' ' || s[i] == '\t') && (!(s[i + 1] == '\t'
			|| s[i + 1] == ' ' || s[i + 1] == '\0')))
			count++;
		i++;
	}
	return (count);
}

static size_t	ft_countchar(const char *s)
{
	size_t	count;

	count = 0;
	while ((s[count] != ' ' && s[count] != '\t') && s[count] != '\0')
		count++;
	return (count);
}

static char		*ft_strcpy_cust(char const *s, char *arr)
{
	size_t		i;

	i = 0;
	while (!(s[i] == ' ' || s[i] == '\t') && s[i] != '\0')
	{
		arr[i] = s[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

char			**ft_splitwhite(char const *s)
{
	char	**arr;
	size_t	row;
	size_t	col;

	row = 0;
	col = 0;
	if (!s)
		return (NULL);
	if (!(arr = (char**)malloc(sizeof(char*) * (ft_countwords(s) + 1))))
		return (0);
	while (s[col] != '\0' && row < ft_countwords(s))
	{
		if ((s[col] != ' ' || s[col] != '\t') && s[col] != '\0')
		{
			if (!(arr[row] = (char*)malloc(sizeof(char) *
							ft_countchar(s + col) + 1)))
				return (0);
			ft_strcpy_cust(s + col, arr[row]);
			col += ft_countchar(s + col);
			row++;
		}
		col++;
	}
	arr[row] = NULL;
	return (arr);
}
