/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_automata.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 16:45:15 by bghandou          #+#    #+#             */
/*   Updated: 2019/06/21 16:26:38 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

int		init_comm_token(char **line, int state, t_par **list)
{
	while (**line && (state >= 5 && state <= 7))
	{
		travel_states(line, state);
		if ((state == 5 || state == 6) && **line == '"')
		{
			state += 1;
			*line = *line + 1;
		}
		if (state == 7 && **line == END_LINE)
		{
			if (**line == END_LINE)
			{
				*list = add_parameter(*list, COMMENT_CMD_STRING, 0);
				break ;
			}
		}
	}
	return (state);
}

int		name_token(char **line, int state, t_par **list)
{
	while (**line && (state >= 1 && state <= 3))
	{
		travel_states(line, state);
		if ((state == 1 || state == 2) && **line == '"')
		{
			state += 1;
			*line = *line + 1;
		}
		if (state == 3 && **line == END_LINE)
		{
			if (**line == END_LINE)
			{
				*list = add_parameter(*list, NAME_CMD_STRING, 0);
				break ;
			}
		}
	}
	return (state);
}
