/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 14:58:05 by bghandou          #+#    #+#             */
/*   Updated: 2018/11/18 16:36:52 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countwords(const char *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	if (s[0] != c)
		count++;
	while (s[i] != '\0')
	{
		if (s[i] == c && (!(s[i + 1] == c || s[i + 1] == '\0')))
			count++;
		i++;
	}
	return (count);
}

static size_t	ft_countchar(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (s[count] != c && s[count] != '\0')
		count++;
	return (count);
}

static char		*ft_strcpy_cust(char const *s, char *arr, char c)
{
	size_t		i;

	i = 0;
	while (!(s[i] == c) && s[i] != '\0')
	{
		arr[i] = s[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**arr;
	size_t	row;
	size_t	col;

	row = 0;
	col = 0;
	if (!s)
		return (NULL);
	if (!(arr = (char**)malloc(sizeof(char*) * (ft_countwords(s, c) + 1))))
		return (0);
	while (s[col] != '\0' && row < ft_countwords(s, c))
	{
		if (s[col] != c && s[col] != '\0')
		{
			if (!(arr[row] = (char*)malloc(sizeof(char) *
							ft_countchar(s + col, c) + 1)))
				return (0);
			ft_strcpy_cust(s + col, arr[row], c);
			col += ft_countchar(s + col, c);
			row++;
		}
		col++;
	}
	arr[row] = NULL;
	return (arr);
}
