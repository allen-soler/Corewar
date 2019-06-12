/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_automata.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 16:45:15 by bghandou          #+#    #+#             */
/*   Updated: 2019/06/12 16:51:27 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

/*
int		init_comm_token(char *line, int state, s_par list)
{
	if (state == 5)
	{
	}
	if (state == 6)
	{
	}
	if (state == 7)
	{
	}
}
*/
int		name_token(char *line, int state, s_par list)
{
	char *repoint;

	repoint = NULL;
	if (state == 1)
	{
	return (0);
	}
	if (state == 2)
	{
	return (0);
	}
	if (state == 3)
	{
	return (0);
	}
/*	if (*(line + 1) != '\0')
		state_0((line + 1), state);*/
	return (0);
}
