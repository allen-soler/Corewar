/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_point.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:07:22 by bghandou          #+#    #+#             */
/*   Updated: 2019/06/04 18:13:26 by bghandou         ###   ########.fr       */
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
		while (haystack[i] == needle[j])
		{
			if (needle[i] == '\0')
				return (&haystack[i]);
			i++;
		}
	}
	return (NULL);
}
