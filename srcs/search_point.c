/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_point.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:07:22 by bghandou          #+#    #+#             */
/*   Updated: 2019/06/21 17:13:06 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

char	*skip_space(char *line)
{
	size_t	i;

	i = 0;
	if (!line)
		return (NULL);
	while (line[i] == ' ' && line[i] != '\0')
		i++;
	return (&line[i]);
}

size_t	str_repoint(char *haystack, char *needle)
{
	size_t	len;

	len = ft_strlen(needle);
	if (!needle || !haystack)
		return (0);
	if (haystack)
	{
		if (!ft_strncmp(haystack, needle, len))
			return (len);
		else
			return (0);
	}
	return (0);
}

void	travel_states(char **line, int state)
{
	if (state == 1 || state == 3 || state == 5 || state == 7)
	{
		if (**line == SPACE)
			*line = skip_space(*line);
		else
		{
		dprintf(1, "state : %d, line :%s\n", state, *line);
			dprintf(1, "EERRRRor!\n");
			exit(EXIT_FAILURE);
		}
	}
	else if (state == 2 || state == 6)
	{
		while (**line && **line != '"')
			*line = *line + 1;
	}
}
