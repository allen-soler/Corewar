/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 17:43:21 by bghandou          #+#    #+#             */
/*   Updated: 2019/07/01 12:19:09 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

t_par	*fetch_function(t_par *tmp, int class, t_par *head)
{
	//dprintf(1, "VALIDATE--->%s__type:%d\n", tmp->param, tmp->type);
	t_par	*(*class_arr[9])(t_par*, t_par*);

	class_arr[0] = class_1;
	class_arr[1] = class_2;
	class_arr[2] = class_3;
	class_arr[3] = class_4;
	class_arr[4] = class_5;
	class_arr[5] = class_6;
	class_arr[6] = class_7;
	class_arr[7] = class_8;
	class_arr[8] = class_9;
	tmp = class_arr[class - 1](tmp, head);
	return (tmp);	
}

void	match_instruction(t_par *tmp, char **instructions, t_par *head)
{
	size_t	i;
	int		class;

	while (tmp)
	{
		i = 0;
		class = 0;
		while (ft_strcmp(instructions[i], tmp->param) != 0)
			i++;
		class = check_class(i);
		if (ft_strcmp(instructions[i], tmp->param) == 0)
			tmp = fetch_function(tmp, class, head);
		tmp = next_inst(tmp);
	}
}

void	check_syntax(t_par *list)
{
	char	**instruct;
	t_par	*tmp;

	tmp = NULL;
	match_labels(tmp, list);
	tmp = next_inst(list);
	if (tmp && tmp->type != 6)
		error_custom("Instruction(s) needed.\n", list);
	else
	{
		instruct = instructions_array();
		match_instruction(tmp, instruct, list);
	}
}
