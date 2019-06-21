/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 17:12:28 by bghandou          #+#    #+#             */
/*   Updated: 2019/06/21 19:06:39 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

void	check_register(char *arg, t_par **list)
{
	int		stock;
	char	*stk;

	stock = 0;
	stk = NULL;
	if (**line == 'r')
	{
		while (ft_isdigit(*(*line + 1)) && *(*line + 1) != '\0')
		{
			*line = *line + 1;
			if (stock == 0)
				stock = **line - 48;
			else
				stock = (stock * 10) + (**line - 48);
		}
		*line = *line + 1;
		stk = ft_itoa(stock);
		if ((**line == ',' || **line == ' ' || **line == '#' || **line == '\t'
			|| **line == '\0') && stock <= 99)
			*list  = add_parameter(*list, stk, 1);
		free(stk);
	}
}

void	check_direct(char *arg, t_par **list)
{
	size_t	stock;
	char	*stk;

	stock = 0;
	stk = NULL;
	if (**line == '%')
	{
		while (ft_isdigit(*(*line + 1)) && *(*line + 1) != '\0')
		{
			*line = *line + 1;
			if (stock == 0)
				stock = **line - 48;
			else
				stock = (stock * 10) + (**line - 48);
		}
		*line = *line + 1;
		stk = ft_itoa(stock);
		if ((**line == ',' || **line == ' ' || **line == '#' || **line == '\t'
			|| **line == '\0'))
			*list  = add_parameter(*list, stk, 3);
		free(stk);
	}
}

void	check_args(char **line, t_par **list)
{
	char 	**args;
	size_t	i;

	args = ft_splitwhite(*line);
	i = -1;
	while (args[++i] != '\0')
	{
		if (args[i][0] == '#')
		{
			free(*line);
			line = NULL;
			break;
		}
		check_register(args[i], list);
		check_direct(args[i], list);
	}
/*	while (**line && **line != '\0')
	{
		check_register(line, list);
		check_direct(line, list);
		if (**line && **line == '#')
		{
			*line = NULL;
			break ;
		}
		if (**line)
			*line = *line + 1;
	}*/
}
