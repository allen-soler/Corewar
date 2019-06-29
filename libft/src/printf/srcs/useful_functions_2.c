/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_functions_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 12:38:18 by nalonso           #+#    #+#             */
/*   Updated: 2019/01/21 12:40:13 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	*malloc_safe(size_t size)
{
	void	*tmp;

	if (!(tmp = malloc(size)))
		exit(1);
	return (tmp);
}

char	*ft_strdup_safe(const char *s1)
{
	char *cpy;

	cpy = (char *)malloc_safe(sizeof(char) * (ft_strlen(s1) + 1));
	return (ft_strcpy(cpy, s1));
}
