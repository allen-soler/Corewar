/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_comma.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 19:40:00 by bghandou          #+#    #+#             */
/*   Updated: 2019/07/08 18:58:59 by bghandou         ###   ########.fr       */
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

static int	space_comma(char *line, size_t i, int row)
{
	size_t	count;
	size_t	j;

	count = 0;
	j = 0;
	while ((line[i + j] == ' ' || line[i + j] == '\t' || line[i + j] == ',')
			&& count <= 1)
	{
		if (line[i + j] == ',')
			count++;
		j++;
	}
	if (count == 1 || (count == 0 && line[i + j] == '\0'))
		return (j);
	else
		error_row("Invalid use of commas for arguments.", row);
	return (j);
}

int			check_comma(char *line, int row)
{
	size_t	i;
	size_t	count;
	int		err;
	size_t	len;

	i = 0;
	count = 0;
	err = 0;
	len = ft_strlen(line);
	while (line && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == ',')
		return (1);
	while (i <= len && line[i] != '\0' && err == 0)
	{
		if (line[i] == ' ' || line[i] == ',' || line[i] == '\t')
			i += space_comma(line, i, row);
		i++;
	}
	err += check_end_comma(line);
	if (i <= len && line[i] == ',')
		return (1);
	return (err);
}
