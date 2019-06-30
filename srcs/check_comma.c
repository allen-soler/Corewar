/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_comma.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 19:40:00 by bghandou          #+#    #+#             */
/*   Updated: 2019/06/30 12:56:41 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

static int	check_end_comma(char *line)
{
	size_t	len;

	len = 0;
	while (line[len] != '\0' && line[len] != '#')
		len++;
	len -= 1;
	while (line[len] == ' ' || line[len] == ',')
	{
		if (line[len] == ',')
			return (1);
		len--;
	}
	return (0);

}

static int	space_comma(char *line, size_t i, t_par **list)
{
	size_t	count;

	count = 0;
	while ((line[i] == ' ' || line[i] == ',') && count <= 1)
	{
		if (line[i] == ',')
			count++;
		i++;
	}
	if (count == 1 || (count == 0 && line[i] == '\0'))
		return (i);
	else
		error_function(NULL, list);
	return (i);
}

int		check_comma(char *line, t_par **list)
{
	size_t	i;
	size_t	count;
	int		err;
	size_t	len;

	i = -1;
	count = 0;
	err = 0;
	len = ft_strlen(line);
	while (line && line[++i] == ' ')
		;
	if (line[i] == ',')
		return (1);
	while (i <= len && line[i] != '\0' && err == 0)
	{
		if (line[i] == ' ' || line[i] == ',')
			i += space_comma(line, i, list);
		i++;
	}
	err += check_end_comma(line);
	if (i <= len && line[i] == ',')
		return (1);
	return (err);
}
