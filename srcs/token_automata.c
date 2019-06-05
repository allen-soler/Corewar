/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_automata.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:09:41 by bghandou          #+#    #+#             */
/*   Updated: 2019/06/05 09:44:57 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

#include <stdio.h>

int		state_0(char *line, int state) //perhaps instead build state 0 - 6 for instance OR build one function per type of token (except instructions, something special)
{
	char *repoint;

	repoint = NULL:
	dprintf(1, "%s\n", line);
	if ((repoint = str_repoint(line, NAME_CMD_STRING)))
	{
		if (repoint)
			line = repoint;
		state += 1;
	}
	else if (str_repoint(line, COMMENT_CMD_STRING)) //test out redirection
	{
		state += 5;
	}
/*	else if (*line == ' ' || *line == '\t')
	{
		state_0((line + 1), state);
	}*/
	if (*(line + 1) != '\0')
		state_0((line + 1), state);
	return (0);
}

char	*token_automata(char *line)
{
	size_t		i;
	size_t		count;
	static int	state;
	
//	const char 	**instructions;

	//instructions = {"ld", "st", "live", "add", "sub", "and", "or", "xor",\
	"zjmp", "ldi", "sti", "lld", "lldi", "lfork", "fork", "aff"};

	state = 0;
	i = 0;
	count = 0;
	state_0(line, state);
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
