/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_automata.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 16:45:15 by bghandou          #+#    #+#             */
/*   Updated: 2019/06/14 17:15:49 by bghandou         ###   ########.fr       */
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
void	name_token(char **line, int state, s_par list)
{
	if (state == 1)
	{
		if (*line == '"')
			state += 1;
		*line = *(line + 1);
	}
	if (state == 2)
	{
		if (*line == '"')
			state += 1;
		*line = *(line + 1);
	}
	if (state == 3)
	{
		while (*line == SPACE);
			*line = *(line + 1);
		if (*line == NEWLINE)
			list = add_parameter(list, NAME_CMD_STRING);
	}
	else //test
		dprintf(1, "ERROR!\n");
	middlefunction(&line, state, list);
}
