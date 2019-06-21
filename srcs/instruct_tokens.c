/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruct_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 20:56:35 by bghandou          #+#    #+#             */
/*   Updated: 2019/06/21 16:20:22 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

char	**instructions_array(void)
{
	char 		**instructions;//can maybe have this as enum

	instructions = ft_strsplit("ldi sti st live add sub and or xor zjmp ld \
 lldi lld lfork fork aff", ' ');
	return (instructions);
}

int		search_valid_inst(char **line, t_par **list) //need something else validate token!!!!
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
				*list = add_parameter(*list, inst[i++], 6);
			else if (*(*line + len) == ':')
			{
				*list = add_parameter(*list, inst[i++], 7);
				len++;
			}
			free_2d(inst);
			return (len);
		}
		else
		 i++;
	}
	free_2d(inst);
	return (0);
}
