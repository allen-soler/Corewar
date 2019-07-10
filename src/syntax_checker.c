/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 17:43:21 by bghandou          #+#    #+#             */
/*   Updated: 2019/07/10 17:38:55 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

t_par	*fetch_function(t_par *tmp, int group)
{
	t_par	*(*class_arr[9])(t_par*);

	class_arr[0] = class_1;
	class_arr[1] = class_2;
	class_arr[2] = class_3;
	class_arr[3] = class_4;
	class_arr[4] = class_5;
	class_arr[5] = class_6;
	class_arr[6] = class_7;
	class_arr[7] = class_8;
	class_arr[8] = class_9;
	if (group > 0)
		tmp = class_arr[group - 1](tmp);
	else if (tmp->type == 7)
		tmp = tmp->next;
	return (tmp);
}

void	match_instruction(t_par *tmp, char **instructions)
{
	size_t	i;
	int		group;

	group = 0;
	while (tmp)
	{
		i = 0;
		group = 0;
		while (ft_strcmp(instructions[i], tmp->param) != 0)
			i++;
		group = check_class(i);
		if (ft_strcmp(instructions[i], tmp->param) == 0)
			tmp = fetch_function(tmp, group);
		tmp = next_inst(tmp);
	}
}

void	check_syntax(t_par *list)
{
	char	**instruct;
	t_par	*tmp;

	tmp = NULL;
	match_labels(tmp, list);
	if (!list)
		error_custom("No valid tokens found.\n", list);
	else if (!(list->next && !ft_strcmp(list->param, ".name")
		&& !ft_strcmp(list->next->param, ".comment")
		&& (list->next->next == NULL || list->next->next->type != 0)))
		error_custom("Invalid header.\n", list);
	tmp = next_inst(list);
	if (tmp && tmp->type != 6)
		error_custom("Instruction(s) needed.\n", list);
	else
	{
		instruct = instructions_array();
		match_instruction(tmp, instruct);
		ft_free_tab(instruct);
	}
}
