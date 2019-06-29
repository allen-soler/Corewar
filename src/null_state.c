/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:09:41 by bghandou          #+#    #+#             */
/*   Updated: 2019/06/29 17:43:05 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int		null_state(char **line, int state, t_par **list) //need array of functions
{
	size_t repoint;

	repoint = 0;
	*line = skip_space(*line);
	if ((repoint = str_repoint(*line, NAME_CMD_STRING)))
		state += 1;
	else if ((repoint = str_repoint(*line, COMMENT_CMD_STRING)))
		state = 5;
	else if ((repoint = set_label(line, list)))
	{
		state = 20;
		*line = *line + repoint;
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

void	middlefunction(char **line, int state, t_par **list)
{ //can put array of functions here
	//	dprintf(1, "__________\n");
	//	test_print(*list);
	//	dprintf(1, "__________\n");
	if (state == 0)
	{
		//		dprintf(1, "line before state : %s\n", *line);
		state = null_state(line, state, list);
	}
	if (state == 1)
		state = name_token(line, state, list);
	else if (state == 5)
		state = init_comm_token(line, state, list);
	else if (state == 20)
		check_args(line, list);
	if (state < 0)
		error_function(*line, list);
}

void	token_automata(char *line, t_par **list)
{
	// Also type of instructions for memory space!! -> stock tokens raw?
	static int	state;
	size_t		i;
	char 		**instructions;//can maybe have this as enum

	i = 0;
	state = 0;
	instructions = ft_strsplit("ld st live add sub and or xor zjmp ldi sti \
			lld lldi lfork fork aff", ' ');

	middlefunction(&line, state, list);
	while (instructions[i] != '\0')
		free(instructions[i++]);
}

void	ingest_file(char *line, t_par **list)
{
	int		i;
	char	**tab;
	t_par	*tmp;

	i = 0;
	tmp = *list;
	tab = ft_strsplit(line, '\n');
	while (tab[i])
	{
		token_automata(tab[i], &tmp);
		i++;
	}
	*list = tmp;
}
