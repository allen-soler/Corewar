/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_systems.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 17:10:25 by bghandou          #+#    #+#             */
/*   Updated: 2019/06/19 17:35:17 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

void	free_2d(char **array)
{
	size_t	i;

	i = 0;
	while (array[i] != '\0')
		free(array[i++]);
	array = NULL;
}
