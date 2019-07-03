/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:09:41 by bghandou          #+#    #+#             */
/*   Updated: 2019/07/03 16:22:46 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

int		null_state(char **line, int state, t_par **list) //need array of functions
{
	size_t repoint;

	repoint = 0;
	*line = skip_space(*line);
	if ((repoint = str_repoint(*line, NAME_CMD_STRING))
		|| (state > 1 && state >= 3))
		state += 1;
	else if ((repoint = str_repoint(*line, COMMENT_CMD_STRING))
		|| (state > 5 && state <= 7))
		state = 5;
	else if ((repoint = set_label(line, list)))
	{
		state = 20;
		repoint = search_valid_inst(line, list);
	}
	else if ((repoint = search_valid_inst(line, list)))
		state = 20;	
	else if (ft_strlen(*line) == 0)
		return (0);
	else
		return (-1);
	*line = *line + repoint;
	return (state);
}

int		middlefunction(char **line, int state, t_par **list)
{ //can put array of functions here
//	dprintf(1, "__________\n");
//	test_print(*list);
//	dprintf(1, "__________\n");
	*line = skip_space(*line);
	*line = ignore_hash_comment(*line);
		dprintf(1, "line before state : %s\n", *line);
	if (state == 0)
		state = null_state(line, state, list);
	if (state >= 1 && state <= 3)
		state = name_token(line, state, list);
	else if (state >= 5 && state <= 7)
		state = init_comm_token(line, state, list);
	else if (state == 20)
		check_args(line, list);
	if (state < 0)
		error_function(NULL, list);
	else if ((state > 1 && state < 3) || (state > 5 && state < 7))
		return (state);
	else
		state = 0;
	return(state);
}

int		token_automata(char *line, t_par **list, int state)
{
	size_t		i;
//	static int	state;
	char 		**instructions;//can maybe have this as enum

	i = 0;
//	state = 0;
	instructions = ft_strsplit("ld st live add sub and or xor zjmp ldi sti \
lld lldi lfork fork aff", ' ');

	state = middlefunction(&line, state, list);
	while (instructions[i] != '\0')
		free(instructions[i++]);
	return (state);
}

t_par	*ingest_file(char *file)
{
	int		fd;
	char	*line;
	t_par	*list;
	static int	state; //added this after

	fd = open(file, O_RDONLY);
	line = NULL;
	list = NULL;
	state = 0;
	while (get_next_line(fd, &line) > 0)
	{
		state = token_automata(line, &list, state);
		free(line);
	}
	return (list);
}

int		main(int ac, char **av)
{
	t_par	*list;

	(void)ac;
	list = ingest_file(av[1]);
	check_syntax(list);
	test_print(list);
}