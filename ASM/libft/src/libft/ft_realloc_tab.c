/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 13:42:41 by nalonso           #+#    #+#             */
/*   Updated: 2019/03/02 13:43:16 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**realloc_tab(void **ptr, size_t new_size, size_t original_size)
{
	void	**new;
	size_t	i;

	i = -1;
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	else if (!ptr)
		return (malloc(new_size));
	else if (new_size <= original_size)
		return (ptr);
	else
	{
		new = malloc(new_size);
		if (new)
		{
			while (++i < original_size)
				new[i] = ptr[i];
			free(ptr);
		}
		return (new);
	}
}
