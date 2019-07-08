/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 17:12:28 by bghandou          #+#    #+#             */
/*   Updated: 2019/07/08 19:33:13 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

static intmax_t	handle_number(char *arg, intmax_t stock, int neg, int row)
{
	if (neg == 1 && ft_isdigit(*arg))
		stock = (stock * 10) - (*arg - 48);
	else if (neg == 0 && ft_isdigit(*arg))
		stock = (stock * 10) + (*arg - 48);
	else
		error_row("Invalid argument format.", row);
	if (stock > 4294967295 || stock < -4294967296)
		error_row("Out of bounds argument value. Needs to be \
> -4294967297 or < 4294967296.\n", row);
	return (stock);
}

int				check_register(char *arg, t_par **list, int row)
{
	size_t	stock;

	stock = 0;
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
			error_row("Register size > 99.", row);
		if (*(arg + 1) != '\0' && *(arg + 1) != ',')
			error_row("Invalid argument.", row);
		arg = arg + 1;
		*list = add_parameter(*list, ft_itoa(stock), 1);
	}
	return (0);
}

int				check_direct(char *arg, t_par **list, int row)
{
	intmax_t	stock;
	int			neg;

	stock = 0;
	neg = 0;
	if (*arg == '%')
	{
		if (*(arg + 1) == ':')
			return (direct_label(list, (arg + 2), 5));
		else if (*(arg + 1) == '-')
		{
			neg = 1;
			arg = arg + 1;
		}
		while (ft_isdigit(*(arg + 1)) && (*(arg + 1)) != '\0')
		{
			arg = arg + 1;
			stock = handle_number(arg, stock, neg, row);
		}
		if (*(arg + 1) != '\0' && *(arg + 1) != ',')
			error_row("Invalid argument.", row);
		arg = arg + 1;
		*list = add_parameter(*list, ft_itoa(stock), 3);
	}
	return (0);
}

int				check_indirect(char *arg, t_par **list, int row)
{
	intmax_t	stock;
	int			neg;

	stock = 0;
	neg = 0;
	if (*arg == '-' || ft_isdigit(*arg) || *arg == ':')
	{
		if (*arg == ':')
			return (direct_label(list, (arg + 1), 9));
		else if (*arg == '-')
		{
			neg = 1;
			arg = arg + 1;
		}
		while (ft_isdigit(*arg) && *arg != '\0')
		{
			stock = handle_number(arg, stock, neg, row);
			arg = arg + 1;
		}
		if (*arg != '\0' && *arg != ',')
			error_row("Invalid argument.", row);
		arg = arg + 1;
		*list = add_parameter(*list, ft_itoa(stock), 4);
	}
	return (0);
}

void			check_args(char **line, t_par **list, int row)
{
	char	**args;
	size_t	i;
	int		err;

	i = -1;
	args = ft_split(*line, " 	,");
	err = 0;
	err += check_comma(*line, row);
	if (err > 0)
		error_row("Invalid use of commas for arguments.", row);
	while (args[++i] != '\0')
	{
		err += check_register(args[i], list, row);
		err += check_direct(args[i], list, row);
		err += check_indirect(args[i], list, row);
	}
	if (i > 3)
		error_row("Can't have more than 3 arguments in an instruction.", row);
	i = -1;
	while (args[++i] != '\0')
		free(args[i]);
	if (err > 0)
		error_function(NULL, list);
}
