/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:09:41 by bghandou          #+#    #+#             */
/*   Updated: 2019/06/12 18:13:54 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

int		null_state(char *line, int state, t_par *list)
{
	if ((line = str_repoint(line, NAME_CMD_STRING)))
	{
		dprintf(1, "LINE : %s\n", line);
		add_parameter(list, NAME_CMD_STRING, 0);
		state += 1;
	}
/*	else if (line = str_reppoint(line, COMMENT_CMD_STRING))
		state = 5;
	else if (line == REG)
	{
		state = 11;
		reg_token(*(line + 1), state, list);
	}*/
	else
		return(0);
	return(1);
}

void	middlefunction(char *line, int state, t_par *list)
{
	if (state == 0)
		null_state(line, state, list);
/*	else if (state >= 1 && state <= 3)
		name_token(line, state, list);
	else if (state >= 5 && state <= 7)
		init_comm_token(line, state, list);
	else if (state == 9)
		intruct_label_token(line, state, list);// LABEL HERE!!! TRACK IT!
	else if (state == 11 && state == 12)
		reg_token(line, state, list);
	else if (state >= 13 && state <= 16)
		dir_label_token(line, state, list);
	else if (state == 17)
		comment_out(line, state, list);*/
}

char	*token_automata(char *line)
{
	// Also type of instructions for memory space!! -> stock tokens raw?
	static int	state;
	t_par		*list;
	
//	const char 	**instructions;//can maybe have this as enum

//	instructions = {{"ld"}, {"st"}, {"live"}, {"add"}, {"sub"}, {"and"}};
//	, {"or"}, {"xor"},
//	"zjmp", "ldi", "sti", "lld", "lldi", "lfork", "fork", "aff"};

	state = 0;
	list = NULL;
	middlefunction(line, state, list);
}

void	ingest_file(char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	line = NULL;
	while (get_next_line(fd, &line))
	{
		token_automata(line);
		free(line);
	}
}

int		main(int ac, char **av)
{
	ingest_file(av[1]);
}
