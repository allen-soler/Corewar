/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_point.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:07:22 by bghandou          #+#    #+#             */
/*   Updated: 2019/07/12 16:19:40 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

char	*ignore_hash_comment(char *line)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (line && line[i] != '\0')
	{
		j = 0;
		if (line[i] == '#')
		{
			while (line[i + j] != '\0')
				j++;
			ft_bzero(&line[i], j);
		}
		i++;
	}
	return (line);
}

char	*skip_space(char *line)
{
	size_t	i;

	i = 0;
	if (!line)
		return (NULL);
	while ((line[i] == ' ' || line[i] == '\t')
		&& line[i] != '\0' && line[i] != '#')
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

void	travel_states(char **line, int state, int row)
{
	if (state == 1 || state == 3 || state == 5 || state == 7)
	{
		if (**line == SPACE || **line == '\t')
			*line = skip_space(*line);
		else
			error_row("Invalid header.", row);
	}
	else if (state == 2 || state == 6)
	{
		while (**line && **line != '"')
			*line = *line + 1;
	}
}

void	check_useless_header(char *line, t_par *list, int row)
{
	if (list && list->type == 0 && str_repoint(line, ".name") > 0)
		error_row("Misplaced header(s). \
Headers must be placed first and no duplicates allowed.", row);
	else if (list && list->next && list->type == 0 && list->next->type == 0
		&& str_repoint(line, ".comment") > 0)
		error_row("Misplaced header(s). \
Headers must be placed first and no duplicates allowed", row);
	return ;
}
