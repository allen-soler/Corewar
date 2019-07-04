/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 17:13:41 by bghandou          #+#    #+#             */
/*   Updated: 2019/07/04 14:32:42 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void	error_custom(char *message, t_par *list)
{
	t_par *tmp;

	tmp = NULL;
	while (list)
	{
		tmp = list;
		list = (list)->next;
		ft_strdel(&(tmp->param));
		free(tmp);
		tmp = NULL;
	}
	ft_putstr(message);
	exit(EXIT_FAILURE);
}

void	error_function(char *string, t_par **list)
{
	t_par *tmp;

	tmp = NULL;
	if (string)
	{
		free(string);
		string = NULL;
	}
	while (*list)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
		tmp = NULL;
	}
	ft_putstr("File structure ERROR\n");
	exit(EXIT_FAILURE);
}
