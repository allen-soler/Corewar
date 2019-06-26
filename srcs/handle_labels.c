/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_labels.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:12:21 by bghandou          #+#    #+#             */
/*   Updated: 2019/06/26 17:00:41 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

static int	in_labelchar(char car)
{
	int		i;

	i = -1;
	while (LABEL_CHARS[++i])
	{
		if (LABEL_CHARS[i] == car)
			return(1);
	}
	return (0);
}
/*
int			set_label(char **line, t_par **list)
{
	size_t	i;

	i = 0;
	while (*line[i] != '\0' &&  *line[i] != ':' && in_labelchar(*line[i]) == 1)
		;
	if (*line[i]
}
*/
int			direct_label(t_par **list, char *arg)
{
	int		i;
	int		len;
	char	*stock;

	i = 0;
	len = ft_strlen(arg);
	stock = ft_memalloc(len + 1);
	dprintf(1, "PASS!\n");
	while (arg[i] && in_labelchar(arg[i]) == 1)
	{
		stock[i] = arg[i];
		i++;
	}
	stock[i] = '\0';
	if (len != i)
	{
		ft_strdel(&stock);
		return (1);
	}
	else
		add_parameter(*list, stock, 5); 
	ft_strdel(&stock);
	return (0);
}
