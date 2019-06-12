/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_point.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:07:22 by bghandou          #+#    #+#             */
/*   Updated: 2019/06/12 18:03:11 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

char	*str_repoint(char *haystack, char *needle)
{
	size_t	i;

	i = 0;
	if (!needle || !haystack)
		return (NULL);
	if (haystack)
	{
		while (haystack[i] == needle[i])
		{
			i++;
			if (needle[i] == '\0')
				return (&haystack[i]);
		}
	}
	return (NULL);
}
