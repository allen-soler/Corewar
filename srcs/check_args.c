/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 17:12:28 by bghandou          #+#    #+#             */
/*   Updated: 2019/06/21 19:43:44 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"
//need a flag system for recognizing commas!
void	check_register(char *arg, t_par **list)
{
	size_t	stock;
	char	*stk;

	stock = 0;
	stk = NULL;
	if (*arg == 'r')
	{
		while (ft_isdigit(*(arg + 1)) && (*(arg + 1)) != '\0')
		{
			arg = arg + 1;
			if (stock == 0)
				stock = *arg - 48;
			else
				stock = (stock * 10) + (*arg - 48);
		}
		arg = arg + 1;
		stk = ft_itoa(stock);
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
	if (*arg == '%')
	{
		while (ft_isdigit(*(arg + 1)) && (*(arg + 1)) != '\0')
		{
			arg = arg + 1;
			if (stock == 0)
				stock = *arg - 48;
			else
				stock = (stock * 10) + (*arg - 48);
		}
		arg = arg + 1;
		stk = ft_itoa(stock);
		*list  = add_parameter(*list, stk, 3);
		free(stk);
	}
}

void	check_args(char **line, t_par **list)
{
	char 	**args;
	size_t	i;

	i = -1;
	args = ft_splitwhite(*line);
	while (args[++i] != '\0')
	{
		if (args[i][0] == '#')
		{
			line = NULL;
			break;
		}
		check_register(args[i], list);
		check_direct(args[i], list);
	}
	i = -1;
	while (args[++i] != '\0')
		free(args[i]);
}
