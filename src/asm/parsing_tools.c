/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 23:12:55 by jallen            #+#    #+#             */
/*   Updated: 2019/07/12 16:17:49 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

char	*n_string(char *src)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	dest = NULL;
	while (src[i])
	{
		if (src[i] == '"')
		{
			j = i + 1;
			while (src[j])
			{
				if (src[j] == '"')
					break ;
				j++;
			}
			dest = ft_strndup(&src[i + 1], j - i - 1);
			return (dest);
		}
		i++;
	}
	return (NULL);
}

char	*find_index(t_par *lst, char *src)
{
	int		i;
	char	*dest;
	int		cnt;

	i = 0;
	cnt = 0;
	while (src[i])
	{
		if (src[i] == '\n')
			cnt++;
		if (cnt == lst->row - 1)
		{
			if (src[i] == '\n' && src[i + 1] != '\0')
				i++;
			dest = n_string(&src[i]);
			return (dest);
			break ;
		}
		i++;
	}
	return (NULL);
}

int		counting_label(t_par *lst, t_inst *inst)
{
	int		i;
	t_par	*tmp;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		if (tmp->type == 6)
			i = g_op_tab[nb_op(tmp->param)].encoding_byte > 0 ? i + 2 : i + 1;
		else if (tmp->type == 1)
			i += 1;
		else if (tmp->type == 2 || tmp->type == 15 ||
				tmp->type == 4 || tmp->type == 9)
			i += 2;
		else if (tmp->type == 3 || tmp->type == 5)
			i += 4;
		inst->param_steps += 1;
		tmp = tmp->next;
		if (tmp)
			if (tmp->type == 6)
				break ;
	}
	return (i);
}
