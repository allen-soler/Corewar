/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 23:55:56 by bghandou          #+#    #+#             */
/*   Updated: 2019/01/13 18:19:19 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(intmax_t n)
{
	int		count;

	count = 0;
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static char	*ft_convert(intmax_t n, int count, char *arr, int flag)
{
	char	*board;

	board = "0123456789";
	if (flag == 1)
	{
		arr[count] = '-';
		flag = 0;
	}
	if (n / 10 > 0)
		ft_convert(n / 10, count, arr + 1, flag);
	*arr = board[n % 10];
	return (arr);
}

char		*ft_itoa(intmax_t n)
{
	int		count;
	char	*arr;
	int		flag;

	flag = 0;
	count = 0;
	arr = 0;
	if (n < 0)
	{
		n *= -1;
		flag = 1;
	}
	if (n == 0)
		return (arr = ft_strdup("0"));
	count = ft_count(n);
	if (n == -2147483648)
		count = 10;
	if (!(arr = (char*)malloc(sizeof(char) * count + 2)))
		return (0);
	if (n == -2147483648)
		return (ft_strcpy(arr, (const char*)"-2147483648"));
	arr[count + flag] = '\0';
	arr = ft_convert(n, count, arr, flag);
	arr = ft_strrev(arr);
	return (arr);
}
