/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_comma.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 19:40:00 by bghandou          #+#    #+#             */
/*   Updated: 2019/06/25 19:40:56 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

int		check_comma(char **args)
{
	size_t	i;
	size_t	j;
	size_t	len;
	size_t	count;

	i = -1;
	j = -1;
	len = 0;
	count = 0;
	if (arg[0][0] == ',')
		return (1);
	while(arg[++i])
		;
	//if 1 arg no commas
	// if 2 || 3 only in beetween
}
