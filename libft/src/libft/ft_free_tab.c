/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 11:06:58 by nalonso           #+#    #+#             */
/*   Updated: 2019/02/12 16:12:40 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_free_tab(char **tab)
{
	char	**ptr;

	ptr = tab;
	while (tab != NULL && *tab != NULL)
	{
		free(*tab);
		tab += 1;
	}
	if (tab)
		free(ptr);
}
