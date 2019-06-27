/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 17:43:21 by bghandou          #+#    #+#             */
/*   Updated: 2019/06/27 20:02:42 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

void	fetch_function(t_par *tmp, int class, t_par *head)
{
	while (tmp)
	{
		if (class == 1)
			tmp = live_function(tmp, head);
		else if (class == 7)
			tmp = class_7(tmp, head);
	/*	else if (class == 2)
		else if (class == 3)
		else if (class == 4)
		else if (class == 5)
		else if (class == 6)
		else if (class == 7)
		else if (class == 8)
		else if (class == 9)*/
	}
}

void	match_instruction(t_par *tmp, char **instructions, t_par *head)
{
	size_t	i;
	int		class;

	i = 0;
	class = 0;
	while (ft_strcmp(instructions[i], tmp->param) != 0)
		i++;
	class = check_class(instruct);
	if (ft_strcmp(instructions[i], tmp->param) == 0)
		fetch_function(tmp, class, head);
}

void	check_syntax(t_par *list)
{
	char	**instruct;
	t_par	*tmp;

	tmp = next_inst(list);
	if (tmp && tmp->type != 6)
		error_custom("Instruction(s) needed.\n", list);
	else
	{
		instruct = instructions_array();
		match_instruction(tmp, instructi, head);
	}
	test_print(tmp);
}
