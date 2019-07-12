/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:47:53 by nalonso           #+#    #+#             */
/*   Updated: 2018/11/14 10:53:00 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	count_length(int nb)
{
	int count;

	count = 0;
	while (nb /= 10)
		count++;
	return (count);
}

static void	nbr_is_negative(int *n, int *bl)
{
	if (*n < 0)
	{
		*n *= -1;
		*bl = 1;
	}
}

char		*ft_itoa(int nbr)
{
	char	*res;
	int		len;
	int		negative;

	len = 1;
	negative = 0;
	if (nbr == -2147483648)
		return (ft_strdup("-2147483648"));
	nbr_is_negative(&nbr, &negative);
	len += negative + count_length(nbr);
	if ((res = (char*)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	res[len] = '\0';
	while (len--)
	{
		res[len] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (negative)
		res[0] = '-';
	return (res);
}
