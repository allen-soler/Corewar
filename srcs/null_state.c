/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:09:41 by bghandou          #+#    #+#             */
/*   Updated: 2019/07/09 14:06:36 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

int		null_state(char **line, int state, t_par **list, int row)
{
	size_t repoint;

	repoint = 0;
	*line = skip_space(*line);
	if ((repoint = str_repoint(*line, ".name")) || (state > 1 && state >= 3))
		state += 1;
	else if ((repoint = str_repoint(*line, COMMENT_CMD_STRING))
		|| (state > 5 && state <= 7))
		state = 5;
	else if ((repoint = set_label(line, list, row)))
	{
		state = 20;
		repoint = search_valid_inst(line, list, row);
	}
	else if ((repoint = search_valid_inst(line, list, row)))
		state = 20;
	else if (ft_strlen(*line) == 0)
		return (0);
	else
	{
		error_state(state, row);
		return (-1);
	}
	*line = *line + repoint;
	return (state);
}

int		middlefunction(char **line, int state, t_par **list, int row)
{
	*line = skip_space(*line);
	if (!((state > 1 && state < 3) || (state > 5 && state < 7)))
		*line = ignore_hash_comment(*line);
	if (state == 0)
		state = null_state(line, state, list, row);
	if (state >= 1 && state <= 3)
		state = name_token(line, state, list, row);
	else if (state >= 5 && state <= 7)
		state = init_comm_token(line, state, list, row);
	else if (state == 20)
		check_args(line, list, row);
	if (state < 0)
		error_function(NULL, list);
	else if ((state > 1 && state < 3) || (state > 5 && state < 7))
		return (state);
	else
		state = 0;
	return (state);
}

int		token_automata(char *line, t_par **list, int state, int row)
{
	size_t		i;
	char		**instructions;

	i = 0;
	instructions = ft_strsplit("ld st live add sub and or xor zjmp ldi sti \
lld lldi lfork fork aff", ' ');
	state = middlefunction(&line, state, list, row);
	while (instructions[i] != '\0')
		free(instructions[i++]);
	return (state);
}

t_par	*ingest_file(char *file, int row)
{
	int			fd;
	char		*line;
	t_par		*list;
	static int	state;

	fd = open(file, O_RDONLY);
	line = NULL;
	list = NULL;
	state = 0;
	while (get_next_line(fd, &line) > 0)
	{
		state = token_automata(line, &list, state, row);
		free(line);
		row++;
	}
	return (list);
}

int		main(int ac, char **av)
{
	t_par		*list;
	static int	row;

	list = NULL;
	row = 1;
	if (ac == 2)//add ft_endswith(av[1], ".s")
		list = ingest_file(av[1], row);
	else
		error_custom("Choose one valid '.s' file to compile.\n", NULL);
	check_syntax(list); // add row parameter to syntax
	test_print(list);
}
