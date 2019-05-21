/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 14:28:18 by bghandou          #+#    #+#             */
/*   Updated: 2019/01/13 18:18:28 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(intmax_t n, int base)
{
	int		count;

	count = 0;
	while (n > 0)
	{
		n /= base;
		count++;
	}
	return (count);
}

static char	*ft_convert(intmax_t n, char *arr, int flag, int base)
{
	char	*board;

	board = "0123456789abcdef";
	if (flag == 1)
	{
		arr[ft_count(n, base)] = '-';
		flag = 0;
	}
	if (n / base > 0)
		ft_convert(n / base, arr + 1, flag, base);
	*arr = board[n % base];
	return (arr);
}

char		*ft_itoa_base(intmax_t n, int base)
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
	count = ft_count(n, base);
	if (!(arr = (char*)malloc(sizeof(char) * count + 2)))
		return (0);
	arr[count + flag] = '\0';
	arr = ft_convert(n, arr, flag, base);
	arr = ft_strrev(arr);
	return (arr);
}
