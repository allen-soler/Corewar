/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 17:12:28 by bghandou          #+#    #+#             */
/*   Updated: 2019/06/30 16:33:02 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//PROBLEM WIIITHHHH HASHTAG AT END
#include "asm.h"
#include "op.h"

int		check_register(char *arg, t_par **list)
{
	size_t	stock;
	char	*stk;

	stock = 0;
	stk = NULL;
	if (*arg == 'r' && (ft_isdigit(*(arg + 1))))
	{
		while (ft_isdigit(*(arg + 1)) && (*(arg + 1)) != '\0')
		{
			arg = arg + 1;
			if (stock == 0)
				stock = *arg - 48;
			else
				stock = (stock * 10) + (*arg - 48);
		}
		if (stock > 99)
			error_custom("Error : register size > 99.\n", *list);
		if (*(arg + 1) != '\0' && *(arg + 1) != ',')
			return (1);
		arg = arg + 1;
		stk = ft_itoa(stock);
		*list  = add_parameter(*list, stk, 1);
		free(stk);
	}
	return (0);
}

int		check_direct(char *arg, t_par **list)
{
	size_t	stock;
	char	*stk;

	stock = 0;
	stk = NULL;
	if (*arg == '%')
	{
		if (*(arg + 1) == ':')
			return (direct_label(list, (arg + 2), 5));
		while (ft_isdigit(*(arg + 1)) && (*(arg + 1)) != '\0')
		{
			arg = arg + 1;
			if (stock == 0)
				stock = *arg - 48;
			else
				stock = (stock * 10) + (*arg - 48);
		}
		if (*(arg + 1) != '\0' && *(arg + 1) != ',')
			return (1);
		arg = arg + 1;
		stk = ft_itoa(stock);
		*list  = add_parameter(*list, stk, 3);
		free(stk);
	}
	return (0);
}

int		check_indirect(char *arg, t_par **list)
{
	size_t	stock;
	char	*stk;

	stock = 0;
	stk = NULL;
	if (ft_isdigit(*arg) || *arg == ':')
	{
		if (*arg == ':')
			return (direct_label(list, (arg + 1), 9));
		while (ft_isdigit(*arg) && *arg != '\0')
		{
			if (stock == 0)
				stock = *arg - 48;
			else
				stock = (stock * 10) + (*arg - 48);
			arg = arg + 1;
		}
		if (*arg != '\0' && *arg != ',')
			return (1);
		arg = arg + 1;
		stk = ft_itoa(stock);
		*list  = add_parameter(*list, stk, 4);
		free(stk);
	}
	return (0);
}

void	check_args(char **line, t_par **list)
{
	char 	**args;
	size_t	i;
	int		err;


	i = -1;
	args = ft_split(*line, " 	,");
	err = 0;
	err += check_comma(*line, list);
	while (args[++i] != '\0')
	{
/*		if (args[i][0] == '#')
		{
			line = NULL;
			break;
		}*/
		err += check_register(args[i], list);
		err += check_direct(args[i], list);
		err += check_indirect(args[i], list);
	}
	i = -1;
	while (args[++i] != '\0')
		free(args[i]);
	if (err > 0)
		error_function(NULL, list);
}
