/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:09:41 by bghandou          #+#    #+#             */
/*   Updated: 2019/06/18 17:34:53 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
//ADD ERROR FUNCTION TO CLEAR TOKEN!
// don't use GNL
int		null_state(char **line, int state) //need array of functions
{
	size_t repoint;

	repoint = 0;
	*line = skip_space(*line);
	if ((repoint = str_repoint(*line, NAME_CMD_STRING)))
	{
		state += 1;
		//test_print(list); //test
	}
	else if ((repoint = str_repoint(*line, COMMENT_CMD_STRING)))
	{
		state = 5;
	}
/*	else if (line == REG)
	{
		state = 11;
		reg_token(*(line + 1), state, list);
	}*/
	else
		return (-1);
	*line = *line + repoint;
	return (state);
}

void	middlefunction(char **line, int state, t_par *list)
{ //can put array of functions here
	if (state == 0)
	{
		dprintf(1, "line before state : %s\n", *line);
		state = null_state(line, state);
	}
	if (state == 1)
		state = name_token(line, state, list);
	else if (state == 5)
		state = init_comm_token(line, state, list);
	else if (state == 9)
		intruct_label_token(line, state, list);// LABEL HERE!!! TRACK IT!
/*	else if (state == 11 && state == 12)
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
	size_t		i;
	char 		**instructions;//can maybe have this as enum

	i = 0;
	state = 0;
	list = NULL;
	instructions = ft_strsplit("ld st live add sub and or xor zjmp ldi sti \
lld lldi lfork fork aff", ' ');

	middlefunction(&line, state, list);
	while (instructions[i] != '\0')
		free(instructions[i++]);
	return(NULL);
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
	(void)ac;
	ingest_file(av[1]);
}
