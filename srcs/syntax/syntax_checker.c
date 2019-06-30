/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 17:43:21 by bghandou          #+#    #+#             */
/*   Updated: 2019/06/30 18:51:47 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

t_par	*fetch_function(t_par *tmp, int class, t_par *head)
{
	//dprintf(1, "VALIDATE--->%s__type:%d\n", tmp->param, tmp->type);
	if (class == 1)
		tmp = class_1(tmp, head);
	else if (class == 2)
		tmp = class_2(tmp, head);
	else if (class == 3)
		tmp = class_3(tmp, head);
	else if (class == 4)
		tmp = class_4(tmp, head);
	else if (class == 5)
		tmp = class_5(tmp, head);
	else if (class == 6)
		tmp = class_6(tmp, head);
	else if (class == 7)
		tmp = class_7(tmp, head);
	else if (class == 8)
		tmp = class_8(tmp, head);
	else if (class == 9)
		tmp = class_9(tmp, head);
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
	test_print(list);
	if (tmp && tmp->type != 6)
		error_custom("Instruction(s) needed.\n", list);
	else
	{
		instruct = instructions_array();
		match_instruction(tmp, instruct, list);
	}
	test_print(tmp);
}
