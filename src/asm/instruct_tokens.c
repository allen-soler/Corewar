/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruct_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 20:56:35 by bghandou          #+#    #+#             */
/*   Updated: 2019/07/12 16:19:03 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

char	**instructions_array(void)
{
	char	**instructions;

	instructions = ft_strsplit("ldi sti st live add sub and or xor zjmp ld \
lldi lld lfork fork aff", ' ');
	return (instructions);
}

int		search_valid_inst(char **line, t_par **list, int row)
{
	size_t	i;
	size_t	len;
	char	**inst;

	i = 0;
	len = 0;
	inst = instructions_array();
	while (inst[i] != '\0')
	{
		if ((len = str_repoint(*line, inst[i])))
		{
			if (*(*line + len) == SPACE || *(*line + len) == '\t')
				*list = add_parameter(*list, inst[i++], 6, row);
			else
				error_row("Lexical.", row);
			ft_free_tab(inst);
			return (len);
		}
		else
			i++;
	}
	ft_free_tab(inst);
	return (0);
}
