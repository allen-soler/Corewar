/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_point.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:07:22 by bghandou          #+#    #+#             */
/*   Updated: 2019/06/16 19:42:28 by bghandou         ###   ########.fr       */
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

void	travel_states(char **line, int state)
{
	if (state == 1 || state == 3 || state == 5 || state == 7)
	{
		if (**line == SPACE)
		{
			while (**line == SPACE)
				*line = *line + 1;
		}
		else
		{
			dprintf(1, "EERRRRor!\n");
			exit(EXIT_FAILURE);
		}
	}
	else if (state == 2)
	{
		while (**line && **line != '"')
			*line = *line + 1;
	}
}
