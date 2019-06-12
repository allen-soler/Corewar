/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_automata.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:09:41 by bghandou          #+#    #+#             */
/*   Updated: 2019/06/12 15:29:46 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
/*
int		init_comm_token(char *line, int state, size_t count)
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
int		name_token(char *line, int state, size_t count)
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

int		null_state(char *line, int state, size_count)
{
}

void	middlefunction(char *line, int state, size_t count)
{
	if (state == 0)
		null_state(line, state, count);
	else if (state >= 1 && state <= 3)
		name_token(line, state, count);
	else if (state >= 5 && state <= 7)
		init_comm_token(line, state, count);
	else if (state == 9)
		intruct_label_token(line, state, count);// LABEL HERE!!! TRACK IT!
	else if (state == 11 && state == 12)
		reg_token(line, state, count);
	else if (state >= 13 && state <= 16)
		dir_label_token(line, state, count);
	else if (state == 17)
		comment_out(line, state, count);
}

char	*token_automata(char *line)
{
	size_t		i;
	size_t		count; // /!\ need to count the number of tokens!! /!\ ->ignore name and comment, get type!!
	// Also type of instructions for memory space!! -> stock tokens raw?
	static int	state;
	
	const char 	**instructions;//can maybe have this as enum

	instructions = {{"ld"}, {"st"}, {"live"}, {"add"}, {"sub"}, {"and"}};
//	, {"or"}, {"xor"},
//	"zjmp", "ldi", "sti", "lld", "lldi", "lfork", "fork", "aff"};

	state = 0;
	i = 0;
	count = 0;
	name_token(line, state);
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
